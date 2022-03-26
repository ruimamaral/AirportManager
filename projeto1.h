#include <stdio.h>

#define AP_ID_LENGHT 4
#define AP_COUNTRY_LENGHT 51
#define AP_CITY_LENGHT 31
#define FLIGHT_CODE_LENGTH 7
#define MAX_AP 40
typedef struct {
	char id[AP_ID_LENGHT];
	char country[AP_COUNTRY_LENGHT];
	char city[AP_CITY_LENGHT];
} airport;

typedef struct {
	int hours;
	int minutes;
	int seconds;
} timestamp;

typedef struct {
	int day;
	int month;
	int year;
} date;

typedef struct {
	char code[FLIGHT_CODE_LENGTH];
	airport origin;
	airport destination;
	timestamp dep_time;
	date dep_date;
	int capacity;
} flight;
