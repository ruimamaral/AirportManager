#include "projeto1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int add_reservation(char flt_code[], int d,
					int m, int y, char temp_res_code[], int pass_n) {
	int len;
	timestamp date = {y, m, d, 0, 0};
	reservation *res;
	char *final_res_code;

	if ((len = check_res_code(temp_res_code)) == -1 || len < 10) {
		return -1;
	} else if (!get_flight(flt_code)) {
		return -2;
	} else if (get_reservation(temp_res_code)) { /*o get reserva retornara um pointer NULL caso
		nao encontre nenhuma reserva tall como o get flight idk if it works */
		return -3;
	} else if (flight->pass_n + pass_n > flight->cap) {
		return -4;
	} else if (invalid_date(date)) {
		return -5;
	} else if (pass_n < 1) {
		return -6;
	}
	final_res_code = my_alloc(len + 1);
	strcpy(final_res_code, temp_res_code); /*ver se vem com o \0 */
	res = create_res(final_res_code, flt_code, pass_n);
	res_to_hashtable(res);
}

reservation *create_res(char code[], char flt[], int pass_n) {
	reservation *res = my_alloc(sizeof(reservation));

	strcpy(reservation->code, final_res_code);
	strcpy(reservation->flt, flt_code);
	reservation->pass_n = n;
	return res;
}
void print_res_error(int error, char flt[], char res[]) {
	if (error =  -1) {
		printf("\n");
	} else if (error = -2) {
		printf("\n");
	} else if (error = -3) {
		printf("\n");
	} else if (error = -4) {
		printf("\n");
	} else if (error = -5) {
		printf("\n");
	} else if (error = -6) {
		printf("\n");
	}
}

int check_res_code(char code[]) {
	int i = 0;

	for (c = code[i] = 0; c; c = code[++i]) {
		if (!((c <= 'Z' && c >= 'A') || (c <= '9' && c >= '0'))) {
			return -1;
		}
	}
	return i;
}
