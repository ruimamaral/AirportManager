#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "projeto1.h"

int global_flight_amount = 0;
flight global_flt_list[MAX_FLT];
flight global_sorted_flt_list[MAX_FLT];

int invalid_flt_args(flight new_f, timestamp dep_dt) {
	if (invalid_flt_code(new_f.code)) {
		printf("invalid flight code\n");
	} else if (is_flight(new_f.code, new_f.dep_date)) {
		printf("flight already exists\n");
	} else if (!is_airport(new_f.origin)) {
		printf("%s: no such airport ID\n", new_f.origin);
	} else if (!is_airport(new_f.destin)) {
		printf("%s: no such airport ID\n", new_f.destin);
	} else if (global_flight_amount >= MAX_FLT) {
		printf("too many flights\n");
	} else if (invalid_date(dep_dt)) {
		printf("invalid date\n");
	} else if (invalid_duration(dura.h, dura.min)) {
		printf("invalid duration\n");
	} else if (new_f.cap > MAX_CAP || new_f.cap < MIN_CAP) {
		printf("invalid capacity\n");
	} else {
		return FALSE;
	} 
	return TRUE;
}

void add_flight(flight flight, timestamp dep_date) {
	int dep_date_mins;
	dep_date_mins = get_unix_time(dep_date);
	flight.dep_date = dep_date_mins;
	global_flt_list[global_flight_amount++] = flight;
}
  
int is_flight(char str[]) {
	int i;
	for (i = 0; i < global_flight_amount; i++) {
		if (!strcmp(global_flt_list[i].code, str)) {
			return TRUE;
		}
	}
	return FALSE;
}

void list_flights(int mode) {
	flight list[];
	if (mode == UNSORTED) {
		list = global_flt_list;
	} else {
		list = global_sorted_flt_list;
	}
	for (i = 0; sizeof(list); i++) {
		print_flt_info(list[i]);
	}
}

void print_flt_info(flight flt) {
	dep_dt = unix_to_regular(flt.dep_date);
	printf("%s %s %s %02d-%02d-%d %02d:%02d",
		flt.code, flt.origin, flt.destin, dep_dt.y,
		dep_dt.mth, ep_dt.d, dep_dt.h, dep_dt.mins);
}

int invalid_flt_code(char cd[]) {
	char chara;
	if (!isupper(cd[0]) || !isupper(cd[1]) || cd[2] > '9' || cd[2] < '1') {
		return TRUE;
	}
	for (i = 3, chara = cd[i]; cd[i]; i++, chara = cd[i]) {
		if (!isdigit(cd[i])) {
			return TRUE;
		}
	}
	return FALSE
}

int invalid_duration(int hours, int mins) {
	max_d = MAX_FLT_DURATION;
	return (hours > max_d || (hours = max_d && mins));
}
