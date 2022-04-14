/*
 * projeto1.h
 *
 * Rui Amaral - ist1103155
 *
 * Header file for the program.
 *
 */

#define TRUE 1
#define FALSE 0
#define AP_ID_LENGTH 4
#define AP_COUNTRY_LENGTH 31
#define AP_CITY_LENGTH 51
#define FLIGHT_CODE_LENGTH 7
#define MAX_AP 40
#define MAX_FLT 30000
#define MAX_FLT_DURATION 12
#define MAX_CAP 100
#define MIN_CAP 10
#define MINS_IN_YEAR 525600
#define MINS_IN_DAY 1440
#define MAX_CMD_LEN 65536

typedef struct {
	char id[AP_ID_LENGTH];
	char country[AP_COUNTRY_LENGTH];
	char city[AP_CITY_LENGTH];
} airport;

typedef struct {
	int y;
	int mth;
	int d;
	int h;
	int min;
} timestamp;

typedef struct {
	char code[FLIGHT_CODE_LENGTH];
	char origin[AP_ID_LENGTH];
	char destin[AP_ID_LENGTH];
	timestamp dep_date;
	timestamp dura;
	int cap;
	int pass_n;
} flight;

typedef struct flt_node {
	struct flt_node *next;
	flight flt;
} flt_node;

typedef struct node *flt_ln;

typedef struct {
	char *code;
	char flt[FLIGHT_CODE_LENGTH];
	int pass_n;
} reservation;

typedef struct {
	int res_amount;
} info;

extern timestamp global_date;


/* PROTOTYPES */

/* projeto1.c */

int command_listener(char);
void exec_add_airport();
void exec_list_airports();
void exec_add_flight();
void exec_list_departing_flts();
void exec_list_arriving_flts();
void exec_set_time();
int isupper_str(char[]);

/* airports.c */

void add_airport(char[], char[], char[]);
int invalid_ap_args(char[]);
airport find_airport(char[]);
void print_ap_info(airport);
void list_airports();
int is_airport(char[]);
void sort_airports();

/* flights.c */

int invalid_flt_args(flight, timestamp);
void add_flight(flight, timestamp);
flight *get_flight(char[], timestamp);
void list_flights();
void list_departing_flights();
void list_arriving_flights();
int invalid_flt_code(char[]);
int invalid_duration(int, int);
int get_flts_departing(char[]);
void get_flts_arriving(char[]);
timestamp get_date_arrival(flight);
void sort_flights();

/* dates.c */

int get_unix_time(timestamp);
int get_month_mins(int);
timestamp unix_to_regular(int);
int invalid_date(timestamp);
int same_day(timestamp, timestamp);
int datecmp(timestamp, timestamp);
