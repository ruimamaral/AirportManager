/*
 * flights.c
 *
 * Rui Amaral - ist1103155
 *
 * File containing everything used in order to manage and 
 * keep track of flights.
 *
 */

#include "projeto1.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Tracks the global amount of flights */
/*int global_flight_amount = 0;*/

/* Tracks the amount of flights that were sorted */
/*int global_srtd_flt_amount = 0;*/

/* Array containing every flight */
/*flight global_flt_list[MAX_FLT];*/


/* 
 * Auxiliary array of flights that stores flights departing/arriving
 * to a given airport as part of the execution of 'c' and 'p' commands.
 */
/*flight *global_srtd_flt_arr[MAX_FLT];*/

/*
 * Adds a flight to the global array of flights.
 */
void add_flight(info *global_info, flight *flt) {
	global_info->flt_amount++;
	insert_ht(flt, global_info->flt_ht, get_key_flt);
}

/*
 * Checks if the program should add a given flight to the system.
 * Returns 0 if all requirements for the addition of the flight
 * are met. Returns 0 otherwise, and prints out error messages
 * notifying the user of the error.
 */
int invalid_flt_args(flight *new_f) {
	if (invalid_flt_code(new_f->code)) {
		printf("invalid flight code\n");
	} else if (get_from_ht(new_f)) {
		printf("flight already exists\n");
	} else if (!is_airport(new_f->origin)) {
		printf("%s: no such airport ID\n", new_f->origin);
	} else if (!is_airport(new_f->destin)) {
		printf("%s: no such airport ID\n", new_f->destin);
	} else if (global_flight_amount >= MAX_FLT) {
		printf("too many flights\n");
	} else if (invalid_date(new_f->date)) {
		printf("invalid date\n");
	} else if (invalid_duration(new_f->dura.h, new_f->dura.min)) {
		printf("invalid duration\n");
	} else if (new_f->cap < MIN_CAP) {
		printf("invalid capacity\n");
	} else {
		return FALSE;
	} 
	return TRUE;
}
 
/*
 * Receives a flight code from a new flight and returns 1
 * if there is an already existing flight in the system
 * with that code, on the same day as the new flight.
 * Returns 0 otherwise.
 */
/*flight *get_flight(char str[], timestamp dt) {
	int i;
	flight flt, *ptr = NULL;

	for (i = 0; i < global_flight_amount; i++) {
		flt = global_flt_list[i];
		if (!strcmp(flt.code, str) && same_day(flt.date, dt)) {
			ptr = &flt;
		}
	}
	return ptr;
}*/

/*
 * Prints out relevant info for every flight currently in the
 * flight hashtable.
 */
void list_flights(info *global_info) {
	int i;
	flight *flt;
	hashtable *flt_ht = global_info->flt_ht;

	for (i = 0; i < flt_ht->size; i++) {
		if (!(flt = flt_ht->array[i])) {
			continue;
		}
		printf("%s %s %s %02d-%02d-%d %02d:%02d\n",
			flt->code, flt->origin, flt->destin, flt->date.d,
			flt->date.mth, flt->date.y, flt->date.h, flt->date.min);
	}
}

/*
 * Prints out info for every flight in the auxiliary flight array,
 * excluding the airport of origin.
 */
void list_departing_flights(info *global_info) {
	int i;
	flight *flt;

	for (i = 0; i < global_srtd_flt_amount; i++) {
		flt = global_srtd_flt_arr[i];
		printf("%s %s %02d-%02d-%d %02d:%02d\n",
			flt->code, flt->destin, flt->date.d, flt->date.mth,
		 	flt->date.y, flt->date.h, flt->date.min);
	}
}

/*
 * Prints out info for every flight in the auxiliary flight array,
 * excluding the airport from where they departed.
 */
void list_arriving_flights(info *global_info) {
	int i;
	flight *flt;

	for (i = 0; i < global_srtd_flt_amount; i++) {
		flt = global_srtd_flt_arr[i];
		printf("%s %s %02d-%02d-%d %02d:%02d\n",
			flt->code, flt->origin, flt->date.d, flt->date.mth,
		 	flt->date.y, flt->date.h, flt->date.min);
	}
}

/*
 * Returns 1 if the flight code received is not valid.
 * Returns 0 otherwise.
 */
int invalid_flt_code(char cd[]) {
	int i;

	if (!isupper(cd[0]) || !isupper(cd[1]) || cd[2] > '9' || cd[2] < '1') {
		return TRUE;
	}
	for (i = N_LETTERS_IN_CODE; cd[i]; ++i) {
		if (!isdigit(cd[i])) {
			return TRUE;
		}
	}
	return FALSE;
}

/*
 * Returns 1 if the duration entered exceeds the maximum
 * duration allowed and 0 if it doesn't.
 */
int invalid_duration(int hours, int mins) {
	int max_d = MAX_FLT_DURATION;

	return (hours > max_d || (hours == max_d && mins));
}

/*
 * Fills up auxiliary array of flights with every flight departing
 * from the airport represented by the id received.
 */
void get_flts_departing(char id[], info *global_info) {
	int i;
	flight *flt;
	hashtable *flt_ht = global_info->flt_ht;
	flight **srtd_flt_array = global_info->srtd_flt_array;

	global_srtd_flt_amount = 0; /* resets counter */

	for (i = 0; i < flt_ht->size; i++) {
		flt = flt_ht->array[i];
		if (flt && !strcmp(flt->origin, id)) {
			srtd_flt_array[global_info->srtd_flt_amount++] = flt;
		}
	}
}


/*
 * Fills up auxiliary array of flights with every flight arriving at
 * the airport represented by the id received.
 */
void get_flts_arriving(char id[], info *global_info) {
	int i;
	flight *flt;
	hashtable *flt_ht = global_info->flt_ht;
	flight **srtd_flt_array = global_info->srtd_flt_array;

	global_info->srtd_flt_amount = 0; /* resets counter */

	for (i = 0; i < flt_ht->size; i++) {
		flt = flt_ht->array[i];
		if (flt && !strcmp(flight->destin, id)) {
			/* changes flight date to its arrival date
			 *  in preparation for the sorting*/
			flt->date = get_date_arrival(flt);
			srtd_flt_array[global_info->srtd_flt_amount++] = flt;
		}
	}
}

/*
 * Receives the date of departure and duration of a flight and returns
 * a timestamp of the time of arrival.
 */
timestamp get_date_arrival(flight *flt) {
	int unix1, unix2;

	unix1 = get_unix_time(flt->date);
	unix2 = flt->dura.h * 60 + flt->dura.min;
	return unix_to_regular(unix1 + unix2);
}

/*
 * Sorts auxiliary array of flights from oldest to most recent.
 * Insertion sort.
 */
void sort_flights(info *global_info) {
	timestamp d;
	flight *temp;
	int i, j, flt_amount = global_info->srtd_flt_amount;
	flight **flt_array = global_info->srtd_flt_array;

	for (i = 1; i < flt_amount; i++) {
		d = flt_array[i]->date;
		j = i;
		temp = flt_array[i];
		while (j > 0 && datecmp(d, flt_array[j - 1]->date) < 0) {
			flt_array[j] = flt_array[j - 1];
			j--;
		}
		flt_array[j] = temp; 
	}
}

char *get_key_flt(void *ptr) {
	flight *flt = (flight*) ptr;
	int key_len = FLIGHT_CODE_LENGTH + 9;
	timestamp dt = flt->date;
	char *key = (char*) my_alloc(key_len);

	/* creates a key based on the flight code and date */
	snprintf(key, key_len, "%s%02d%02d%04d", code, dt.d, dt.m, dt.y);
	return key;
}
