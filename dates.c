#include <stdio.h>
#include <string.h>
#include "projeto1.h"

int global_date = get_unix_time(timestamp = {2022, 1, 1, 0, 0});

int get_unix_time(timestamp ts) {
	int yr = ts.y, mth = ts.mth, days = ts.d, hrs = ts.h, mins = ts.min;
	int min_sum = yr * MINS_IN_YEAR + get_month_mins(mth - 1);
	min_sum += days * MINS_IN_DAY + hrs * 60 + mins;
	return min_sum;
}

int get_month_mins(int month) {
	int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int i, min_sum = 0;
	for (i = 0; i < month; i++) {
		min_sum += days_in_month[i] * MINS_IN_DAY;
	}
	return min_sum;
}

timestamp unix_to_regular(int min_sum) {
	timestamp ts;
	int mth, mth_mins;
	ts.y = min_sum / (MINS_IN_YEAR);
	min_sum -= ts.y * MINS_IN_YEAR;
	mth_mins = get_month_mins(1);
	for (mth = 1; min_sum - mth_mins >= 0; mth_mins = get_month_mins(++mth)) {}
	min_sum -= get_month_mins(mth - 1);
	ts.mth = mth;
	ts.d = min_sum / MINS_IN_DAY + 1;
	min_sum -= (day - 1) * MINS_IN_DAY;
	ts.h = min_sum / 60;
	ts.min = min_sum % 60;
	return ts;
}

int invalid_date(timestamp ts) {
	int unix1, unix2;
	unix1 = get_unix_time(ts);
	unix2 = get_unix_time(global_date);
	is_past = datecmp(ts, global_date) < 0;
	return (is_past || unix1 - unix2 > MINS_IN_YEAR);
}


