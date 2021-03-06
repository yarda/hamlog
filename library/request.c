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

#include "request.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>


HAMRequest *ham_request_new(const char *uri, const char *method, const char *content, const char *content_type) {
	HAMRequest *request = malloc(sizeof(HAMRequest));
	if (request == NULL)
		return NULL;

	request->method = strdup(method);
	request->uri = strdup(uri);
	request->content = content ? strdup(content) : NULL;
	request->content_type = content ? strdup(content_type) : NULL;
	request->headers = NULL;
	request->headers_count = 0;

	// TODO: content/content_type
	if (request->method == NULL || request->uri == NULL) {
		free(request->method);
		free(request->uri);
		free(request);
		return NULL;
	}

	return request;
}

void ham_request_destroy(HAMRequest *request) {
	int i;
	if (request == NULL)
		return;

	free(request->method);
	free(request->uri);
	free(request->content);
	free(request->content_type);
	for (i = 0; i < request->headers_count; i++) {
		free(request->headers[i]->name);
		free(request->headers[i]->value);
	}
	free(request->headers);

	free(request);
}

void ham_request_dump(HAMRequest *request) {
	char *data = ham_request_get_data(request);
	printf("%s\n", data);
	free(data);
}

char *ham_request_get_data(HAMRequest *request) {
	int i;
	int size = strlen(request->method) + strlen(request->uri) + 14 + 1; // 1 space + " HTTP/1/1\r\n\0"

	for (i = 0; i < request->headers_count; i++) {
		size += strlen(request->headers[i]->name) + strlen(request->headers[i]->value) + 2 + 2; // ": " + "\r\n"
	}

	if (request->content) {
		size += strlen(request->content);
		size += strlen("Content-Length: ") + 5;
		size += 6;
	}

	size += 2; // "\r\n"

	char *data = malloc(sizeof(char) * size);
	int end = sprintf(data, "%s %s HTTP/1.1\r\n", request->method, request->uri);

	char *ptr = data;
	ptr += end;
	for (i = 0; i < request->headers_count; i++) {
		end = sprintf(ptr, "%s: %s\r\n", request->headers[i]->name, request->headers[i]->value);
		ptr += end;
	}

	if (request->content) {
		end = sprintf(ptr, "Content-Length: %d\r\n\r\n%s", (int) strlen(request->content), request->content);
		ptr += end;
	}

	end = sprintf(ptr, "\r\n");

	return data;
}

void ham_request_set_content(HAMRequest *request, const char *content) {
	if (request->content) {
		free(request->content);
	}
	request->content = strdup(content);
}

void ham_request_add_header(HAMRequest *request, const char *name, const char *value) {
	request->headers_count++;
	request->headers = realloc(request->headers, sizeof(HAMRequestHeader*) * request->headers_count);

	if (request->headers == NULL) {
		request->headers_count = 0;
		return;
	}

	// TODO: check allocation
	HAMRequestHeader *header = malloc(sizeof(HAMRequestHeader));
	header->name = strdup(name);
	header->value = strdup(value);
	request->headers[request->headers_count - 1] = header;
}

