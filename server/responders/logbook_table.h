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

#define CREATE_LOGBOOK_TABLE() {\
	std::list<StorageBackend::Column> columns;\
	\
	columns.push_back(StorageBackend::Column("id", StorageBackend::Column::Integer, -1, true, true));\
	columns.push_back(StorageBackend::Column("user_id", StorageBackend::Column::Integer, -1, true));\
	columns.push_back(StorageBackend::Column("qsodate", StorageBackend::Column::Datetime, -1, false));\
	columns.push_back(StorageBackend::Column("time_on", StorageBackend::Column::String, 20, false));\
	columns.push_back(StorageBackend::Column("callsign", StorageBackend::Column::String, 20, false));\
	columns.push_back(StorageBackend::Column("freq", StorageBackend::Column::Real, -1, false));\
	columns.push_back(StorageBackend::Column("mode", StorageBackend::Column::String, 60, false));\
	columns.push_back(StorageBackend::Column("qth", StorageBackend::Column::String, 60, false));\
	columns.push_back(StorageBackend::Column("name", StorageBackend::Column::String, 50, false));\
	columns.push_back(StorageBackend::Column("loc", StorageBackend::Column::String, 10, false));\
	columns.push_back(StorageBackend::Column("latitude", StorageBackend::Column::String, 10, false));\
	columns.push_back(StorageBackend::Column("longitude", StorageBackend::Column::String, 10, false));\
	columns.push_back(StorageBackend::Column("county", StorageBackend::Column::String, 50, false));\
	columns.push_back(StorageBackend::Column("continent", StorageBackend::Column::String, 3, false));\
	columns.push_back(StorageBackend::Column("itu", StorageBackend::Column::Integer, -1, false));\
	columns.push_back(StorageBackend::Column("cq", StorageBackend::Column::Integer, -1, false));\
	columns.push_back(StorageBackend::Column("rst_rx", StorageBackend::Column::String, -1, false));\
	columns.push_back(StorageBackend::Column("rst_tx", StorageBackend::Column::String, -1, false));\
	columns.push_back(StorageBackend::Column("qsl", StorageBackend::Column::Integer, -1, false));\
	columns.push_back(StorageBackend::Column("qsl_sent", StorageBackend::Column::Datetime, -1, false));\
	columns.push_back(StorageBackend::Column("qsl_received", StorageBackend::Column::Datetime, -1, false));\
	columns.push_back(StorageBackend::Column("qsl_via", StorageBackend::Column::String, -1, false));\
	columns.push_back(StorageBackend::Column("comments", StorageBackend::Column::String, 4096, false));\
	\
	StorageBackend::getInstance()->createTable("logbook", columns);\
	}

