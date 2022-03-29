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
			return 1;
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
			return 1;
	}
	return 1;
}

void exec_a() {
	char id[AP_ID_LENGTH], country[AP_COUNTRY_LENGTH], city[AP_CITY_LENGTH];
	scanf("%s %s %[^\n]", id, country, city);
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
				printf("%s: no such airport ID\n", id);	
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
	timestamp dep_dt;
	if (c == ' ') { /* checks if there are more arguments */
		scanf("%s %s %s %d-%d-%d %d:%d %d:%d %d",
			new_f.code, new_f.origin, new_f.destin, &dep_dt.y,
			&dep_dt.mth, &dep_dt.d, &dep_dt.h, &dep_dt.min,
			&new_f.dura.h, &new_f.dura.min, &new_f.cap);

		if (invalid_flt_agrs(new_f, dep_dt)) {
			return;
		} else {
			add_flight(new_f, dep_dt);
		}
	} else {
		list_flights(global_flight_list);
	}
}

void exec_p() {
	char id[AP_ID_LENGTH];
	scanf("%s", id);
	get_flts_leaving(id);
	list_flights(SORTED);
}

void exec_c() {
	char id[AP_ID_LENGTH];
	scanf("%s", id);
	get_flts_arriving(id);
	list_flights(SORTED);
}

void exec_t() {
	timestamp new_date;
	scanf("%d-%d-%d", new_date.d, new_date.mon, new_date.y);
	if (!invalid_date (new_date)) {
		global_date = new_date;
	}
	printf("invalid date\n");
	return;
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

