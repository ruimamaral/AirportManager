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

int invalid_date(date dt1, date dt2) {
	if (dt1.y >= dt2.y && dt1.m >= dt2.m && dt1.d >)
}
