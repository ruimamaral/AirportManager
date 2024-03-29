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
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * Adds a flight to the system.
 */
void add_flight(info *global_info, flight *flt) {
	flt->res_array = (reservation**) my_alloc(flt->cap * sizeof(reservation));
	flt->res_n = 0;
	flt->pass_n = 0;

	global_info->flt_array[global_info->flt_ht->amount] = flt;

	insert_ht(flt, global_info->flt_ht, global_info->ts, get_key_flt);
}

/*
 * Checks if the program should add a given flight to the system.
 * Returns 0 if all requirements for the addition of the flight
 * are met. Returns 0 otherwise, and prints out error messages
 * notifying the user of the error.
 */
int invalid_flt_args(info *global_info, flight *new_f) {
	hashtable *flt_ht = global_info->flt_ht;
	char *key = make_flt_key(new_f->code, new_f->date);

	if (invalid_flt_code(new_f->code)) {
		printf("invalid flight code\n");
	} else if (get_from_ht(key, flt_ht, global_info->ts, get_key_flt)) {
		printf("flight already exists\n");
	} else if (!is_airport(new_f->origin)) {
		printf("%s: no such airport ID\n", new_f->origin);
	} else if (!is_airport(new_f->destin)) {
		printf("%s: no such airport ID\n", new_f->destin);
	} else if (flt_ht->amount >= MAX_FLT) {
		printf("too many flights\n");
	} else if (invalid_date(new_f->date)) {
		printf("invalid date\n");
	} else if (invalid_duration(new_f->dura.h, new_f->dura.min)) {
		printf("invalid duration\n");
	} else if (new_f->cap < MIN_CAP) {
		printf("invalid capacity\n");
	} else {
		free(key);
		return FALSE;
	} 
	free(key);
	return TRUE;
}
 
/*
 * Prints out relevant info for every flight currently in the
 * unsorted flight array;
 */
void list_flights(info *global_info) {
	int i;
	flight *flt;

	for (i = 0; i < global_info->flt_ht->amount; i++) {
		if (!(flt = global_info->flt_array[i])) {
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

	for (i = 0; i < global_info->srtd_flt_amount; i++) {
		flt = global_info->srtd_flt_array[i];
		printf("%s %s %02d-%02d-%d %02d:%02d\n",
			flt->code, flt->destin, flt->date.d, flt->date.mth,
		 	flt->date.y, flt->date.h, flt->date.min);
		free(flt);
	}
}

/*
 * Prints out info for every flight in the auxiliary flight array,
 * excluding the airport from where they departed.
 */
void list_arriving_flights(info *global_info) {
	int i;
	flight *flt;

	for (i = 0; i < global_info->srtd_flt_amount; i++) {
		flt = global_info->srtd_flt_array[i];
		printf("%s %s %02d-%02d-%d %02d:%02d\n",
			flt->code, flt->origin, flt->date.d, flt->date.mth,
		 	flt->date.y, flt->date.h, flt->date.min);
		free(flt);
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
void get_flts_departing(info *global_info, char id[]) {
	int i;
	flight *flt1, *flt2;
	flight **srtd_flt_array = global_info->srtd_flt_array;
	int flt_amount = global_info->flt_ht->amount;

	global_info->srtd_flt_amount = 0; /* resets counter */

	for (i = 0; i < flt_amount; i++) {
		flt1 = global_info->flt_array[i];
		if (!strcmp(flt1->origin, id)) {
			flt2 = (flight*) my_alloc(sizeof(flight));
			*flt2 = *flt1;
			srtd_flt_array[global_info->srtd_flt_amount++] = flt2;
		}
	}
}


/*
 * Fills up auxiliary array of flights with every flight arriving at
 * the airport represented by the id received.
 */
void get_flts_arriving(info *global_info, char id[]) {
	int i;
	flight *flt1, *flt2;
	flight **srtd_flt_array = global_info->srtd_flt_array;
	int flt_amount = global_info->flt_ht->amount;

	global_info->srtd_flt_amount = 0; /* resets counter */

	for (i = 0; i < flt_amount; i++) {
		flt1 = global_info->flt_array[i];
		if (!strcmp(flt1->destin, id)) {
			/* changes flight date to its arrival date
			 *  in preparation for the sorting*/
			flt2 = (flight*) my_alloc(sizeof(flight));
			*flt2 = *flt1;
			flt2->date = get_date_arrival(flt2);
			srtd_flt_array[global_info->srtd_flt_amount++] = flt2;
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
	int i, j, srtd_flt_amount = global_info->srtd_flt_amount;
	flight **srtd_flt_array = global_info->srtd_flt_array;

	for (i = 1; i < srtd_flt_amount; i++) {
		d = srtd_flt_array[i]->date;
		j = i;
		temp = srtd_flt_array[i];
		while (j > 0 && datecmp(d, srtd_flt_array[j - 1]->date) < 0) {
			srtd_flt_array[j] = srtd_flt_array[j - 1];
			j--;
		}
		srtd_flt_array[j] = temp; 
	}
}

/*
 * Gets the key corresponding to a given flight to be
 * used in the hashtable.
 */
char *get_key_flt(void *ptr) {
	flight *flt = (flight*) ptr;

	return make_flt_key(flt->code, flt->date);
}

/*
 * Makes and returns a key from a flight code and flight date.
 */
char *make_flt_key(char code[], timestamp date) {
	int key_len = FLIGHT_CODE_LENGTH + 2 + 2 + 4;
	char *key = (char*) my_alloc(key_len);

	sprintf(key, "%s%02d%02d%04d", code, date.d, date.mth, date.y);

	return key;
}

/*
 * Removes a flight from the system.
 */
int remove_flight(info *global_info, char code[]) {
	flight *flt;
	flight **flt_array = global_info->flt_array;
	void *ts = global_info->ts;
	hashtable *flt_ht = global_info->flt_ht;
	hashtable *res_ht = global_info->res_ht;
	int i = 0, j ,success = FALSE;

	for (i = 0; i < flt_ht->amount; i++) {
		flt = flt_array[i];
		if (!strcmp(code, flt->code)) {
			remove_from_ht(flt, flt_ht, ts, get_key_flt);
			for(j = flt->res_n - 1; j >= 0; j--) {
				remove_from_ht(flt->res_array[j], res_ht, ts, get_key_res);
				free(flt->res_array[j]->code);
				free(flt->res_array[j]);
			}
			rem_flt_array(flt_array, i, flt_ht->amount + 1);
			i--;
			free(flt->res_array);
			free(flt);
			success = TRUE;
		}
	}
	return success;
}

/*
 * Removes a flight pointer from the array of flight pointers.
 */
void rem_flt_array(flight **array, int index, int count) {
	while (index < count - 1) {
		array[index] = array[index + 1];
		index++;
	}
}
