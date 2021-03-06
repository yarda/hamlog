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

#pragma once

#include <boost/asio.hpp>
#include <string>
#include "sessionmanager.h"
#include "session.h"

namespace HamLog {

class Config;

class Server {
	public:
		Server(Config *config, const std::string& address, int port);
		
		void start();

		void stop();

		boost::asio::io_service &getIOService() {
			return m_ioService;
		}

		Config *getConfig() {
			return m_config;
		}

	private:
		void handleAccept(const boost::system::error_code &e);

		void handleStop();

		boost::asio::io_service m_ioService;
		boost::asio::ip::tcp::acceptor m_acceptor;
		SessionManager m_sessionManager;
		Session::ref m_session;
		Config *m_config;
};

}
