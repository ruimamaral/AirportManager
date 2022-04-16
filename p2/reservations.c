#include "projeto1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int add_reservation(info *global_info, char flt_code[], int d,
					int m, int y, char temp_res_code[], int pass_n) {
	int len;
	timestamp date = {y, m, d, 0, 0};
	reservation *res;
	char *final_res_code;

	if ((len = check_res_code(temp_res_code)) == -1 || len < 10) {
		return -1;
	} else if (!get_flight(flt_code, date)) {
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
	final_res_code = (char*) my_alloc(len + 1);
	strcpy(final_res_code, temp_res_code); /*ver se vem com o \0 */
	res = create_res(final_res_code, flt_code, pass_n);
	res_to_hashtable(global_info->hashtable, res);
	return 0;
}

int list_reservations(char flt_code[], int d, int m, int y) {
	/* maybe utilizar capacidade do voo para ver se as reservas ja foram
	 * todas encontradas (maybe por pointer para voo em cada reserva para n ter de procurar o voo) */
	timestamp date = {y, m, d, 0, 0};
	int res_n;
	reservation **res_array;

	if (!get_flight(flt_code)) {
		return -2;
	} else if (invalid_date(date)) {
		return -5;
	}
	res_n = get_flight(flt_code)->res_n;
	res_array = (reservation**) my_alloc(sizeof(reservation*) * res_n);
	quicksort();
	for (i = 0; i < res_n; i++) {
		printf("%s %d\n", res_array[i]->code, res_array[i]->pass_n);
	}

	free(res_array);
	return 0;
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

hashtable *init_ht(int size_n) {
	hashtable *hashtable = (hashtable*) my_alloc(sizeof(hashtable));
	long size = get_size(size_n);

	hashtable->size = size;
	hashtable->size_n = size_n;
	hashtable->array = (void**) my_alloc(sizeof(void*) * size);
	hashtable->amount = 0;

	for (i = 0; i < size; i++) {
		hashtable->table[i] = NULL;
	}
	return hashtable;
}

long hash_str1(char *code, int length, long size) {
	long hash = 0;
	int max_index = length - 1;
	for (i = 1; i < 10; i++) {
		hash = hash*23 + code[max_index - max_index/i];
	}
	return hash % size;
}

long hash_str2(char *code, int length, long size) {
	long hash = 0;
	int max_index = length - 1;
	for (i = 1; i < 8; i++) {
		hash = hash*31 + code[max_index * (1 - 0.083 * i)];
	}
	return hash % size;
}

long get_size(int size_n, int size) {
	int n;
	long sum;

	static const int size_array[] = {
		6151, 12289, 24593, 49157, 98317, 196613, 393241,
		786433, 1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189, 805306457, 1610612741
	};
	if (size_n > 18) {
		return 2 * size + 1;
	}
	return size_array[i];
}

char *get_key_res(void *ptr) {
	reservation *res = (reservation*) ptr;
	return res->code;
}

void insert_ht(void *ptr, hashtable *ht, char* get_key(void*)) { /* maybe this brokey */
	char *key = get_key(ptr);
	long i = hash_str1(key);
	long k = hash_str2(key);

	while(ht->array[i]) {
		i = (i + k) % ht->size;
	}
	ht->array[i] = ptr;

	if (++ht->amount > ht->size / 2) {
		expand_ht(ht, get_key);
	}
}

void expand_ht(hashtable *ht, char* get_key(void*)) {
	long old_size = ht->size, new_size = get_size(++ht->size_n, ht->size);
	void **new_array = (void**) my_alloc((void*) * new_size);
	void **old_array = ht->array;
	long i;

	for (i = 0; i < size; i++) {
		new_array[i] = NULL;
	}

	ht->array = new_array;
	ht->size = new_size;

	for (i = 0; i < old_size; i++) {
		if (old_array[i]) {
			insert_ht(old_array[i], ht, get_key_res); /* ver se funciona a passagem de funcao */
		}
	free(old_array);
}

int remove_from_ht(char *key, hashtable *ht, char* get_key(void*)) {
	long i = hash_str1(key);
	long k = hash_str2(key);
	void *temp;

	while(strcmp(get_key(ht->array[i]), key) && ht->array[i]) {
		i = (i + k) % ht->size;
	}
	if(!ht->array[i]) {
		return FALSE;
	}
	ht->array[i] = NULL;
	--ht->amount;

	for(i = (i + k) % ht->size; ht->array[i]; i = (i + k) % ht->size) {
		temp = ht->array[i];
		ht->array[i] = NULL;
		--ht->amount;
		insert_ht(temp, ht, get_key);
		i = (i + k) % ht->size;
	}
	return TRUE;
}

void *get_from_ht(char *key, hashtable *ht, char* get_key(void*)) {
	long i = hash_str1(key);
	long k = hash_str2(key);

	while(strcmp(get_key(ht->array[i]), key) && ht->array[i]) {
		i = (i + k) % ht->size;
	}
	return ht->array[i];
}
