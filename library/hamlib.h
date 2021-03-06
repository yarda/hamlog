/*
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

#ifndef _HAMLOG_HAMLIB_H
#define _HAMLOG_HAMLIB_H

#include "connection.h"
#include "parser.h"
#include "reply.h"
#include "request.h"
#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file hamlib.h Hamlib API
 * @ingroup core
 * @details DXCC API provides a way to get DXCC related 
 * informations about operator
 */

void ham_hamlib_set_frequency(HAMConnection *connection, const char *frequency, HAMFetchHandler handler, void *ui_data);

void ham_hamlib_fetch_frequency(HAMConnection *connection, HAMFetchHandler handler, void *ui_data);

void ham_hamlib_register_signals();

#ifdef __cplusplus
}
#endif

#endif
