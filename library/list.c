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

#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

HAMList *ham_list_new() {
	HAMList *list = malloc(sizeof(HAMList));
	if (list == NULL)
		return NULL;

	list->first = NULL;
	list->last = NULL;
	list->free_func = NULL;
	return list;
}

void ham_list_destroy(HAMList *list) {
	if (list == NULL)
		return;

	HAMListItem *ptr = list->first;
	HAMListItem *ptr2;

	while (ptr) {
		ptr2 = ptr->rptr;
		if (list->free_func) {
			list->free_func(ptr->data);
		}
		free(ptr);
		ptr = ptr2;
	}

	free(list);
}

void ham_list_set_free_func(HAMList *list, HAMListItemDataFree func) {
	list->free_func = func;
}

void ham_list_insert_first(HAMList *list, void *data) {
	HAMListItem *ptr;
	if ((ptr = malloc(sizeof(HAMListItem))) == NULL) {
		return;
	}

	ptr->data = data;
	ptr->lptr = NULL;
	ptr->rptr = list->first;
	
	if (list->first != NULL) {
		list->first->lptr = ptr;
	}
	else {
		list->last = ptr;
	}
	list->first = ptr;
}

void ham_list_insert_last(HAMList *list, void *data) {
	HAMListItem *ptr;
	if ((ptr = malloc(sizeof(HAMListItem))) == NULL) {
		return;
	}

	ptr->data = data;
	ptr->lptr = list->last;
	ptr->rptr = NULL;
	
	if (list->last != NULL) {
		list->last->rptr = ptr;
	}
	else {
		list->first = ptr;
	}
	list->last = ptr;
}

void ham_list_remove(HAMList *list, void *data) {
	HAMListItem *act = list->first;
	while(act) {
		if (act->data == data) {
			break;
		}
		act = act->rptr;
	}

	if (act == NULL)
		return;

	if (list->first == act) {
		list->first = act->rptr;
	}
	else {
		act->lptr->rptr = act->rptr;
	}

	if (list->last == act) {
		list->last = act->lptr;
	}
	else {
		act->rptr->lptr = act->lptr;
	}
	free(act);
}

void *ham_list_pop_first(HAMList *list) {
	if (list->first == NULL)
		return NULL;
	void *data = list->first->data;
	ham_list_remove(list, data);
	return data;
}

void *ham_list_get_first(HAMList *list) {
	if (list->first == NULL)
		return NULL;
	return list->first->data;
}

void *ham_list_get_last(HAMList *list) {
	if (list->last == NULL)
		return NULL;
	return list->last->data;
}

HAMListItem *ham_list_get_first_item(HAMList *list) {
	return list->first;
}

HAMListItem *ham_list_get_next_item(HAMListItem *item) {
	return item->rptr;
}

void *ham_list_item_get_data(HAMListItem *item) {
	return item->data;
}
