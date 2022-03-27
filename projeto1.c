#include <stdio.h>
#include "projeto1.h"
#include <string.h>

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
	if (!is_upper(id)) {
		printf("invalid airport ID\n");
	}
	else if (global_airport_amount >= MAX_AP) {
		printf("too many airports\n");
	}
	else if (is_airport(id)) {
		printf("duplicate airport\n");
	}
	else {
		add_airport(id, country, city);
		printf("airport %s\n", id);
	}
}

void exec_l() {
	char c = getchar(), id[AP_ID_LENGTH];
	if (c == ' ') {
		while (c != '\n' && c != EOF) {
			fgets(id, AP_ID_LENGTH, stdin);
			if (!is_airport(id)) {
				printf("<IDAeroporto>: no such airport ID\n");	
			}
			else {
				print_ap_info(find_airport(id));
			}
			c = getchar();
		}
	}
	else {
		sort_airports();
	}
}

int is_airport(char str[]) {
	int i;
	for (i = 0; i < global_airport_amount; i++) {
		if (!strcmp(global_ap_id_list[i], str)) {
			return TRUE;
		}
	}
	return FALSE;
}

int is_upper(char str[]) {
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
