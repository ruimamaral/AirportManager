/*
 * reservations.c
 *
 * Rui Amaral - ist103155
 *
 * File containing functions used to manage flight reservations.
 *
 */

#include "projeto1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * Function that adds a reservation to the system, checks arguments.
 */
int add_reservation(info *global_info, char flt_code[], int d,
					int m, int y, char buff[], int pass_n) {
	hashtable *flt_ht = global_info->flt_ht, *res_ht = global_info->res_ht;
	void *ts = global_info->ts;
	int len = check_res_code(buff);
	timestamp date = create_date(y, m, d, 0, 0);
	char *final_res_code, *key = make_flt_key(flt_code, date);
	flight *flt = (flight*) get_from_ht(key, flt_ht, ts, get_key_flt);

	free(key);
	if (len == -1 || len < 10) {
		return -1;
	} else if (!flt) {
		return -2;
	} else if (get_from_ht(buff, res_ht, ts, get_key_res)) {
		return -3;
	} else if (flt->pass_n + pass_n > flt->cap) {
		return -4;
	} else if (invalid_date(date)) {
		return -5;
	} else if (pass_n < 1) {
		return -6;
	}
	final_res_code = (char*) my_alloc(len + 1);
	strcpy(final_res_code, buff);
	store_res(global_info, create_res(final_res_code, flt, pass_n), flt);
	return 0;
}

/*
 * Stores new reservation on the different data structures.
 */
void store_res(info *global_info, reservation *res, flight *flt) {
	int i = get_res_index(flt->res_array, res, flt->res_n);

	insert_ht(res, global_info->res_ht, global_info->ts, get_key_res);
	/* inserts pointers to reservations in the reservation pointer
	 * array of its corresponding flight, sorted by the reservations'
	 * code. */
	add_res_array(flt->res_array, i, res, flt->res_n++);
	flt->pass_n += res->pass_n;
}

/*
 * Lists all reservations to a given flight if the flight exists.
 */
int list_reservations(info *global_info, char flt_code[], int d, int m, int y) {
	hashtable *flt_ht = global_info->flt_ht;
	timestamp date = create_date(y, m, d, 0, 0);
	int res_n, i;
	reservation **res_array;
	char *key = make_flt_key(flt_code, date);
	flight *flt = get_from_ht(key, flt_ht, global_info->ts, get_key_flt);

	free(key);

	if (!(flt)) {
		return -2;
	} else if (invalid_date(date)) {
		return -5;
	}
	res_n = flt->res_n;
	res_array = flt->res_array;

	for (i = 0; i < res_n; i++) {
		printf("%s %d\n", res_array[i]->code, res_array[i]->pass_n);
	}
	return 0;
}

/*
 * Creates a reservation type item.
 */
reservation *create_res(char code[], flight *flt, int pass_n) {
	reservation *res = my_alloc(sizeof(reservation));

	res->code = code;
	res->flt = flt;
	res->pass_n = pass_n;
	return res;
}

/*
 * Prints out error messages for the 'r' and 'e' commands.
 */
void print_res_error(int error, char flt[], char res[]) {
	if (error ==  -1) {
		printf("invalid reservation code\n");
	} else if (error == -2) {
		printf("%s: flight does not exist\n", flt);
	} else if (error == -3) {
		printf("%s: flight reservation already used\n", res);
	} else if (error == -4) {
		printf("too many reservations\n");
	} else if (error == -5) {
		printf("invalid date\n");
	} else if (error == -6) {
		printf("invalid passenger number\n");
	}
}

/*
 * Checks if given reservstion code is valid, returning -1 if so.
 * Returns the received string length otherwise.
 */
int check_res_code(char code[]) {
	int i = 0;
	char c;

	for (c = code[i]; c; c = code[++i]) {
		if (!((isupper(c) || isdigit(c)))) {
			return -1;
		}
	}
	return i;
}

/*
 * Removes a reservation from the system.
 */
int remove_reservation(info *global_info, char code[]) {
	hashtable *res_ht = global_info->res_ht;
	void *ts = global_info->ts;
	reservation *res;
	flight *flt;
	int res_index;

	res = (reservation*) get_from_ht(code, res_ht, ts, get_key_res);
	if (res) {
		flt = res->flt;
		remove_from_ht(res, res_ht, global_info->ts, get_key_res);

		res_index = get_res_index(flt->res_array, res, flt->res_n);

		rem_res_array(flt->res_array, res_index, flt->res_n--);
		flt->pass_n -= res->pass_n;

		free(res->code);
		free(res);
		return TRUE;
	}
	return FALSE;
}

/*
 * Receives a pointer to a reservation and returns its key
 * for the hashtable.
 */
char *get_key_res(void *ptr) {
	reservation *res = (reservation*) ptr;
	char *key = (char*) my_alloc(strlen(res->code) + 1);
	strcpy(key, res->code);
	return key;
}

/*
 * Returns an int that corresponds to the index where a given
 * reservation is located inside a given array of reservation
 * pointers. Returns the index where it should be at if the
 * reservation isnt found in the array. (binary search)
 */
int get_res_index(reservation **res_array, reservation *res, int count) {
	int upper = count - 1;
	int lower = 0;
	int i = 0, result;

	while (upper >= lower) {
		i = (upper + lower) / 2;
		result = strcmp(res->code, res_array[i]->code);
		if (result > 0) {
			lower = ++i;
		} else if (result < 0) {
			upper = i - 1;
		} else {
			return i; /* element found */
		}
	}
	return i;
}

/*
 * Deletes a pointer at a given index from a reservation pointer array.
 */
void rem_res_array(reservation **array, int index, int count) {
	while (index < count - 1) {
		array[index] = array[index + 1];
		index++;
	}
}

/*
 * Inserts a pointer to a reservation at a given index in
 * a reservation pointer array.
 */
void add_res_array(reservation **array, int i, reservation *ptr, int count) {
	while (count > i) {
		array[count] = array[count - 1];
		count--;
	}
	array[i] = ptr;
}
