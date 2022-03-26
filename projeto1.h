#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define AP_ID_LENGTH 4
#define AP_COUNTRY_LENGTH 51
#define AP_CITY_LENGTH 31
#define FLIGHT_CODE_LENGTH 7
#define MAX_AP 40
#define AIRPORTS 1
#define FLIGHTS 0

typedef struct {
	char id[AP_ID_LENGTH];
	char country[AP_COUNTRY_LENGTH];
	char city[AP_CITY_LENGTH];
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

extern int global_airport_amount;
extern airport global_airport_list[];
extern char global_ap_id_list[][AP_ID_LENGTH];

/* PROTOTYPES */


void add_airport(char[], char[], char[]);
airport find_airport(char[]);
void print_ap_info(airport);
void sort_airports();
int is_upper(char[]);
int is_airport(char[]);
void exec_l();
void exec_a();
int command_listener();
