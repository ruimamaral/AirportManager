#include "projeto1.h"
#include <stdlib.h>
#include <stdio.h>

void add_reservation() {

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
