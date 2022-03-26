#include <stdio.h>
#include <projeto1.h>
#include <string.h>

int main(){
	while (command_listener());
	return 0;
}

int command_listener() {
	char command = getchar();
	getchar(); /* remove whitespace chararcter */
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
		printf("invalid airport ID");
	}
	else if (global_airport_amount >= MAX_AP)) {
		printf("too many airports");
	}
	else if (duplicate_airport(id)) {
		printf("duplicate airport");
	}
	else add_airport(id, country, city);
}
