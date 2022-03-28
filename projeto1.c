#include <stdio.h>
#include "projeto1.h"
#include <string.h>

int aps_sorted;

int main(){
	while (command_listener()) {
	}
	return 0;
}

int command_listener() {
	char command = getchar();
	switch (command) {
		case 'q':
			return 0;
		case 'a':
			exec_a();
			return 1;
		case 'l':
			exec_l();
			return 1; /*
		case 'v':
			exec_v();
			return 1;
		case 'p':
			exec_p();
			return 1;
		case 'c':
			exec_c();
			return 1;
		case 't':
			exec_t();
			return 1; */
	}
	return 1;
}

void exec_a() {
	char id[AP_ID_LENGTH], country[AP_COUNTRY_LENGTH], city[AP_CITY_LENGTH];
	scanf("%s%s%[^\n]", id, country, city);
	if (!isupper_str(id)) {
		printf("invalid airport ID\n");
	} else if (global_airport_amount >= MAX_AP) {
		printf("too many airports\n");
	} else if (is_airport(id)) {
		printf("duplicate airport\n");
	} else {
		add_airport(id, country, city);
		printf("airport %s\n", id);
		aps_sorted = FALSE;
	}
}

void exec_l() {
	char c = getchar(), id[AP_ID_LENGTH];
	int i;
	if (c == ' ') {
		while (c != '\n' && c != EOF) {
			fgets(id, AP_ID_LENGTH, stdin);
			if (!is_airport(id)) {
				printf("<IDAeroporto>: no such airport ID\n");	
			} else {
				print_ap_info(find_airport(id));
			}
			c = getchar();
		}
	} else {
		if (!aps_sorted) {   /* checks if airport array is already sorted */
			sort_airports();
			aps_sorted = TRUE;
		}
		for (i = 0; i < global_airport_amount; i++) {
			print_ap_info(global_airport_list[i]);
		}
	}
}

void exec_v() {
	char c = getchar();
	flight new_f;
	if (c == ' ') { /* checks if there are more arguments */
		scanf("%s %s %s %d-%d-%d %d:%d %d:%d %d",
			new_f.code, new_f.origin, new_f.destin,
			&new_f.dep_ts.d, &new_f.dep_ts.mth, &new_f.dep_ts.y,
			&new_f.dep_ts.h, &new_f.dep_ts.min,
			&new_f.dura.h, &new_f.dura.min,
			&new_f.cap);

		if (invalid_flt_code(code)) {
			printf("invalid flight code\n");
		} else if (is_flight(new_f.code, new_f.dep_date)) {
			printf("flight already exists\n");
		} else if (!is_airport(new_f.origin) || !is_airport(new_f.destination)) {
			printf("<IDAeroporto>: no such airport ID\n");
		} else if (global_flight_amount >= MAX_FLT) {
			printf("too many flights\n");
		} else if (invalid_date(global_date, new_f.dep_date)) {
			printf("invalid date\n");
		} else if (new_f.dura.h > MAX_FLT_DURATION) {
			printf("invalid duration\n");
		} else if (new_f.cap > MAX_CAP || new_f.cap < MIN_CAP) {
			printf("invalid capacity\n");
		} else {
			global_flt_list[global_flight_amount++] = new_f;
		}
	} else {
		list_flights(UNSORTED);
	}
}

int isupper_str(char str[]) {
	char c;
	int i, len = strlen(str);
	for (i = 0; i < len; i++) {
		c = str[i];
		if (c < 'A' || c > 'Z') {
	  		return FALSE;
		}
	}
	return TRUE;
}
