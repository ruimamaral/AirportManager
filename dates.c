/*
 * dates.c
 *
 * Rui Amaral - ist1103155
 *
 * File containing functions that are used to manage the time system.
 *
 */

#include "projeto1.h"
#include <stdio.h>
#include <string.h>

/* Universal system date */
timestamp global_date = {2022, 1, 1, 0, 0};


/*
 * Turns a date in a timestamp format into a unix-like format.
 * Returns an integer corresponding to the minute sum.
 */
int get_unix_time(timestamp ts) {
	int yr = ts.y, mth = ts.mth, days = ts.d, hrs = ts.h, mins = ts.min;
	int min_sum = yr * MINS_IN_YEAR + get_month_mins(mth - 1);

	min_sum += (days - 1) * MINS_IN_DAY + hrs * 60 + mins;
	return min_sum;
}

/*
 * Returns the sum of the minutes of the months since the start of the
 * year until the month corresponding to the integer received.
 */
int get_month_mins(int month) {
	/* Array containing the amout of days per
	 * month from january to december */
	static const int days_in_month[] = {
		31, 28, 31, 30,
		31, 30, 31, 31,
		30, 31, 30, 31
	};
	int i, min_sum = 0;

	for (i = 0; i < month; i++) {
		min_sum += days_in_month[i] * MINS_IN_DAY;
	}
	return min_sum;
}

/*
 * Converts a minute sum into a regular date, returning it as
 * a timestamp.
 */
timestamp unix_to_regular(int min_sum) {
	timestamp ts;
	int mth, mth_mins;

	ts.y = min_sum / (MINS_IN_YEAR);
	min_sum -= ts.y * MINS_IN_YEAR;

	mth_mins = get_month_mins(1);
	/* Gets the month number */
	for (mth = 1; min_sum - mth_mins >= 0; mth_mins = get_month_mins(++mth)) {}

	min_sum -= get_month_mins(mth - 1);
	ts.mth = mth;

	ts.d = min_sum / MINS_IN_DAY + 1;
	min_sum -= (ts.d - 1) * MINS_IN_DAY;

	ts.h = min_sum / 60;

	ts.min = min_sum % 60;
	return ts;
}

/*
 * Checks if the date received is invalid.
 * Returns 1 if so, 0 otherwise.
 */
int invalid_date(timestamp ts) {
	timestamp gl_date_plus_1year = global_date;
	int is_past = datecmp(ts, global_date) < 0;
	
	/* Gets date on the very end of the current day on the following
	 * year so that only dates more than a year apart and on different
	 * days are flagged as invalid */
	gl_date_plus_1year.y += 1;
	gl_date_plus_1year.h = 23;
	gl_date_plus_1year.min = 59;

	return (is_past || datecmp(ts, gl_date_plus_1year) > 0);
}

/*
 * Checks whether the dates received share the same day, month and year.
 * Returns 1 if so, 0 otherwise.
 */
int same_day(timestamp ts1, timestamp ts2) {
	return (ts1.y == ts2.y && ts1.mth == ts2.mth && ts1.d == ts2.d);
}

/*
 * Compares two dates, returning < 0 if the first date is before
 * the second, < 0 if the first date is after the second one,
 * and 0 if they are equal.
 */
int datecmp(timestamp date1, timestamp date2) {
	int unix1, unix2;

	unix1 = get_unix_time(date1);
	unix2 = get_unix_time(date2);

	if (unix1 > unix2) {
		return 1;
	} else if (unix1 == unix2) {
		return 0;
	} else {
		return -1;
	}
}

