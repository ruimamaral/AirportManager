#include <stdio.h>

typedef struct {
	char id[4];
	char country[31];
	char city[51];
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
	char code[7];
	airport origin;
	airport destination;
	timestamp dep_time;
	date dep_date;
	int capacity;
} flight;
