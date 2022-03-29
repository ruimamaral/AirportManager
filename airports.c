#include <stdio.h>
#include <string.h>
#include "projeto1.h"

int global_airport_amount = 0;
airport global_airport_list[MAX_AP];

/*maybe mudar e meter tudo como os flights */
void add_airport(char id[], char country[], char city[]) {
	airport new_airport;
	strcpy(new_airport.id, id);
	strcpy(new_airport.country, country);
	strcpy(new_airport.city, city);

	global_airport_list[global_airport_amount++] = new_airport;
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
	int n_f = 69;/*get_n_flights(ap.id);*/
	printf("%s %s %s %d\n", ap.id, ap.city, ap.country, n_f);
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

/* ver a soma da data para dar sort nos voos*/
/*
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
*/
