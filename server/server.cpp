/**
 * Hamlog
 *
 * Copyright (C) 2011, Jan Kaluza <hanzz.k@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 */

#include "server.h"
#include <boost/bind.hpp>
#include <iostream>
#include "log.h"
#include "config.h"

namespace HamLog {

DEFINE_LOGGER(logger, "Server");

Server::Server(Config *config, const std::string &hostname, int port)
	: m_ioService(), m_acceptor(m_ioService), m_session(new Session(m_ioService)), m_config(config) {

// 	boost::asio::ip::tcp::resolver resolver(m_ioService);
// 	boost::asio::ip::tcp::resolver::query query(hostname, port);
// 	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);

	m_acceptor.open(endpoint.protocol());
	m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_acceptor.bind(endpoint);
	m_acceptor.listen();
	m_acceptor.async_accept(m_session->getSocket(), boost::bind(&Server::handleAccept, this, boost::asio::placeholders::error));
}

void Server::start() {
	LOG_INFO(logger, "Starting the server");
	m_ioService.run();
}

void Server::stop() {
	LOG_INFO(logger, "Stopping the server");
	m_ioService.post(boost::bind(&Server::handleStop, this));
}

void Server::handleAccept(const boost::system::error_code& e) {
	if (e) {
		return;
	}

	LOG_INFO(logger, "Accepted new client connection");
	m_sessionManager.start(m_session);

	m_session.reset(new Session(m_ioService));
	m_acceptor.async_accept(m_session->getSocket(), boost::bind(&Server::handleAccept, this, boost::asio::placeholders::error));
}

void Server::handleStop() {
	m_acceptor.close();
}

}
