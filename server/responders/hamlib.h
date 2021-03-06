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

#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/signal.hpp>
#include <boost/tuple/tuple.hpp>
#include <string>
#include "requestresponder.h"
#include "request.h"
#include "reply.h"
#include "storagebackend.h"

namespace HamLog {

class Session;
class Server;

namespace Responder {

class Hamlib : public boost::enable_shared_from_this<Hamlib>, public RequestResponder {
	public:
		typedef boost::shared_ptr<Hamlib> ref;

		Hamlib(Server *server);

		bool handleRequest(Session::ref session, Request::ref request, Reply::ref reply);

	private:
		void sendFrequency(Session::ref session, Request::ref request, Reply::ref reply);
		void setFrequency(Session::ref session, Request::ref request, Reply::ref reply);

		Server *m_server;
};

}
}
