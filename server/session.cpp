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

#include "session.h"
#include <boost/bind.hpp>

namespace HamLog {
	
Session::Session(boost::asio::io_service& ioService)
	: m_socket(ioService) {
}

boost::asio::ip::tcp::socket& Session::getSocket() {
	return m_socket;
}

void Session::start() {
	m_socket.async_read_some(boost::asio::buffer(m_buffer),
							 boost::bind(&Session::handleRead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Session::stop() {
	m_socket.close();
	onStopped();
}

void Session::handleRead(const boost::system::error_code& e, std::size_t bytes) {
	if (e) {
		stop();
		return;
	}

	std::cout << "data received. size = " << bytes << "\n";

	if (true /*&& all_data_received_and_response_is_ready*/) {
		boost::asio::async_write(m_socket, boost::asio::buffer("response\n"),
								 boost::bind(&Session::handleWrite, shared_from_this(), boost::asio::placeholders::error));
    }
	else {
		m_socket.async_read_some(boost::asio::buffer(m_buffer),
								boost::bind(&Session::handleRead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
}

void Session::handleWrite(const boost::system::error_code& e) {
	if (!e) {
		boost::system::error_code ec;
		m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
	}

	if (e != boost::asio::error::operation_aborted) {
		stop();
	}
}

}
