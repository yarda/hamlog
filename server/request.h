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
#include <boost/lexical_cast.hpp>
#include <string>

namespace HamLog {

class Request : public boost::enable_shared_from_this<Request> {
	public:
		typedef boost::shared_ptr<Request> ref;

		typedef struct _Header {
			std::string name;
			std::string value;
		} Header;

		Request();

		void dump();

		bool isFinished() {
			return m_finished;
		}

		const std::string &getURI() {
			return m_uri;
		}

		const std::string &getMethod() {
			return m_method;
		}

		const std::string &getContent() {
			return m_content;
		}

		bool hasHeader(const std::string &name);

		std::string getHeader(const std::string &name);

	private:
		std::string m_method;
		std::string m_uri;
		unsigned int m_majorVersion;
		unsigned int m_minorVersion;
		bool m_finished;
		std::list<Header> m_headers;
		std::string m_content;
		friend class RequestParser;
};

}
