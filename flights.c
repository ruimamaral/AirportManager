#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "projeto1.h"

int global_flight_amount = 0;
flight global_flt_list[MAX_FLT];
flight global_sorted_flt_list[MAX_FLT];


  
int is_flight(char str[]) {
	int i;
	for (i = 0; i < global_flight_amount; i++) {
		if (!strcmp(global_flt_list[i].code, str)) {
			return TRUE;
		}
	}
	return FALSE;
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

int set_unix_time(timestamp ts) {
	int yr = ts.y, mth = ts.mth, days = ts.d, hrs = ts.h, mins = ts.min;
	int min_sum = yr * MINS_IN_YEAR + get_month_mins(mth - 1);
	min_sum += days * MINS_IN_DAY + hrs * 60 + mins;
	return min_sum;
}

int get_month_mins(int month) {
	int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int i, min_sum = 0;
	for (i = 0; i < month; i++) {
		min_sum += days_in_month[i] * MINS_IN_DAY;
	}
	return min_sum;
}
