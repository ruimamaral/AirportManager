#include <stdio.h>
#include <string.h>
#include "projeto1.h"

int global_airport_amount = 0;
airport global_airport_list[MAX_AP];

void add_airport(char id[], char country[], char city[]) {
	airport new_airport;

	strcpy(new_airport.id, id);
	strcpy(new_airport.country, country);
	strcpy(new_airport.city, city);

	global_airport_list[global_airport_amount++] = new_airport;
}

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

void print_ap_info(airport ap) {
	int n_f = get_flts_departing(ap.id);
	printf("%s %s %s %d\n", ap.id, ap.city, ap.country, n_f);
}

void list_airports() {
	int i;
	for (i = 0; i < global_airport_amount; i++) {
		print_ap_info(global_airport_list[i]);
	}
}

int is_airport(char str[]) {
	int i;

	for (i = 0; i < global_airport_amount; i++) {
		if (!strcmp(global_airport_list[i].id, str)) {
			return TRUE;
		}
	}
	return FALSE;
}

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

