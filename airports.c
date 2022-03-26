#include <stdio.h>
#include <projeto.h>

int global_airport_amount = 0;
airport *airport_list[MAX_AP];

void add_airport(char id[], char country[], char city[]) {
	airport new_airport, *airport_pointer;
	airport_pointer = &new_airport;
	new_airport.id = id;
	new_airport.country = country;
	new_airport.city = city;
	airport_list[global_airport_amount] = airport_pointer;
	global_airport_amount++;
}
