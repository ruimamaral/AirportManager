#include <stdio.h>
#include <projeto1.h>
#include <string.h>

int main(){
	while (command_listener());
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
}

int global_airport_amount;
void exec_a() {
	char id[AP_ID_LENGHT], country[AP_COUNTRY_LENGHT], city[AP_CITY_LENGHT];
	scanf("%s%s%[^\n]", id, country, city);
	if (not_caps(id)) {
		printf("invalid airport ID\n");
	}
	else if (global_airport_amount >= MAX_AP) {
		printf("too many airports\n");
	}
	else if (is_duplicate(id, AIRPORTS)) {
		printf("duplicate airport\n");
	}
	else add_airport(id, country, city);
	printf("airport %s\n", id);
}

void exec_l() {
	char c = getchar(), id[AP_ID_LENGHT];
	int n_f;
	if (c == ' ') {
		for (scanf("%3s", id); c != '\n' && c != EOF; c = getchar()) {
			if (!is_duplicate(id, AIRPORTS)) {
				printf("<IDAeroporto>: no such airport ID\n");
				return;
			}
			print_ap_info(find_airport(id));
		}
	}
	else {
		sort_airports()
	}
}

void is_duplicate(char str[], int mode) {
	int i;
	if (mode == AIRPORTS) {
		list = global_ap_id_list;
		max = global_airport_amount;
	}
	else {
		list = global_flt_code_list;
		max = global_flight_amount
	}	
	for (i = 0; i < max; i++) {
		if (!strcmp(list[i], str)) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
}
