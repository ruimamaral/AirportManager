/*
 * airports.c
 *
 * Rui Amaral - ist1103155
 *
 * File containing everything used in order to manage airports.
 * 
 */

#include "projeto1.h"
#include <stdio.h>
#include <string.h>

/* Tracks the global amount of airports */
int global_airport_amount = 0;

/* Array that stores all the airports in the system */
airport global_airport_list[MAX_AP];


/*
 * Adds an aiport to the global array.
 */
void add_airport(char id[], char country[], char city[]) {
	airport new_airport;

	strcpy(new_airport.id, id);
	strcpy(new_airport.country, country);
	strcpy(new_airport.city, city);

	global_airport_list[global_airport_amount++] = new_airport;
}

/*
 * Checks if the system should add a new airport.
 * Returns 1 if it meets all the requirements and 0 if otherwise.
 */
int invalid_ap_args(char id[]) {
	if (!isupper_str(id)) {
		printf("invalid airport ID\n");
	} else if (global_airport_amount >= MAX_AP) {
		printf("too many airports\n");
	} else if (is_airport(id)) {
		printf("duplicate airport\n");
	} else {
		return FALSE;
	}
	return TRUE;
}

/*
 * Receives an airport id, finds that airport in the array
 * and returns it.
 */
airport find_airport(char id[]) {
	int i;
	airport ap;

	for (i = 0; i < global_airport_amount; i++) {
		ap = global_airport_list[i];
		if (!strcmp(ap.id, id)) {
			break;
		}
	}
	return ap;
}

/*
 * Receives an airport id and prints relevant info about
 * that specific airport.
 */
void print_ap_info(info *global_info, airport ap) {
	int n_f;
	get_flts_departing(global_info, ap.id);
	n_f = global_info->srtd_flt_amount;
	printf("%s %s %s %d\n", ap.id, ap.city, ap.country, n_f);
}

/*
 * Prints relevant info of all the airports currently in the system.
 */
void list_airports(info *global_info) {
	int i;
	for (i = 0; i < global_airport_amount; i++) {
		print_ap_info(global_info, global_airport_list[i]);
	}
}

/*
 * Receives an aiport id and returns 1 if there currently is
 * an airport with that id in the system. Returns 0 otherwise.
 */
int is_airport(char str[]) {
	int i;

	for (i = 0; i < global_airport_amount; i++) {
		if (!strcmp(global_airport_list[i].id, str)) {
			return TRUE;
		}
	}
	return FALSE;
}

/*
 * Sorts global list of airports by their id, in alphabetical order.
 * Insertion sort.
 */
void sort_airports() {
	char id1[AP_ID_LENGTH];
	airport temp;
	int i, j;

	for (i = 1; i < global_airport_amount; i++) {
		strcpy(id1, global_airport_list[i].id);
		j = i;
		temp = global_airport_list[i];
		while (j > 0 && strcmp(id1, global_airport_list[j - 1].id) < 0) {
			global_airport_list[j] = global_airport_list[j - 1];
			j--;
		}
		global_airport_list[j] = temp; 
	}
}

