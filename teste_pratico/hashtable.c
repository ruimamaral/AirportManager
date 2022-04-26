/*
 * hashtable.c
 *
 * Rui Amaral - ist103155
 *
 * File containing functions used to manage the hashtables
 * used in the program.
 *
 */

#include "projeto1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Creates and initializes a hashtable of pointers with certain size.
 * The hashtable uses double hashing to deal with conflicts.
 */
hashtable *init_ht(int size_n) {
	hashtable *ht;	long size = get_size(size_n, 0);
	int i;

	ht = (hashtable*) my_alloc(sizeof(hashtable));

	ht->size = size;
	ht->size_n = size_n;
	ht->array = (void**) my_alloc(sizeof(void*) * size);
	ht->amount = 0;

	for (i = 0; i < size; i++) {
		ht->array[i] = NULL;
	}
	return ht;
}

/*
 * First hashing function for the hashtable (hashes a string).
 */
long hash_str1(char str[], int length, long size) {
	long hash = 0;
	int i, max_index = length - 1;
	for (i = 1; i < 10; i++) {
		hash = hash*23 + str[max_index - max_index/i];
	}
	return hash % size;
}

/*
 * Second hashing function for the hashtable (hashes a string).
 */
long hash_str2(char str[], int length, long size) {
	long hash = 0;
	int i, max_index = length - 1;
	for (i = 1; i < 8; i++) {
		hash = hash*31 + str[(int) (max_index * (1 - 0.083 * i))];
	}
	return hash % size + 1; /* shouldnt ever be 0 */
}

/*
 * Receives an int and returns a prime number from an array
 * of selected prime numbers to be used as a size for the hashtable.
 * If the hashtable's size is already the largest number available,
 * it returns the current size x 2 + 1.
 */
long get_size(int size_n, int size) {

	static const int size_array[] = {
		24593, 49157, 98317, 196613, 393241, 786433,
		1572869, 3145739, 6291469, 12582917, 25165843, 50331653,
		100663319, 201326611, 402653189, 805306457, 1610612741
	};
	if (size_n > 16) {
		return 2 * size + 1;
	}
	/* sets fixed size for flight array */
	if (size_n < 0) {
		return 45000;
	}
	return size_array[size_n];
}

/*
 * Inserts a given pointer to a given hashtable.
 */
void insert_ht(void *ptr, hashtable *ht, void *ts, char* get_key(void*)) {
	char *key = get_key(ptr);
	int len_key = strlen(key);
	long i = hash_str1(key, len_key, ht->size);
	long k = hash_str2(key, len_key, ht->size);

	while (ht->array[i] && ht->array[i] != ts) {
		i = (i + k) % ht->size;
	}
	ht->array[i] = ptr;

	if (++ht->amount > ht->size * 2 / 3) {
		expand_ht(ht, ts, get_key);
	}
	free(key);
}

/*
 * Doubles (approximately) the given hashtable's size.
 * Re-hashes and re-inserts every item currently in the table.
 */
void expand_ht(hashtable *ht, void *ts, char* get_key(void*)) {
	long old_size = ht->size, new_size = get_size(++ht->size_n, ht->size);
	void **new_array = (void**) my_alloc(sizeof(void*) * new_size);
	void **old_array = ht->array;
	long i;

	for (i = 0; i < new_size; i++) {
		new_array[i] = NULL;
	}

	ht->array = new_array;
	ht->size = new_size;

	for (i = 0; i < old_size; i++) {
		if (old_array[i] && old_array[i] != ts) {
			insert_ht(old_array[i], ht, ts, get_key);
		}
	}
	free(old_array);
}

/*
 * Removes a given pointer from a given hashtable.
 */
void remove_from_ht(void *ptr, hashtable *ht, void *ts, char* get_key(void*)) {
	char *key1 = get_key(ptr), *key2;
	int len_key = strlen(key1);
	long i = hash_str1(key1, len_key, ht->size);
	long k = hash_str2(key1, len_key, ht->size);

	while (TRUE) {
		if (ht->array[i] == ts) {
			i = (i + k) % ht->size;
			continue;
		};
		key2 = get_key(ht->array[i]);
		if (!strcmp(key2, key1)) {
			free(key2);
			break;
		}
		free(key2);
		i = (i + k) % ht->size;
	}
	ht->array[i] = ts;
	--ht->amount;
	free(key1);
}

/*
 * Searches for a given item in the hashtable. Returns a NULL pointer
 * if given key does not correspond to a key from an element currently
 * in the hashtable. Returns a pointer to the element if it is found.
 */
void *get_from_ht(char key1[], hashtable *ht, void *ts, char* get_key(void*)) {
	int len_key = strlen(key1);
	long i = hash_str1(key1, len_key, ht->size);
	long k = hash_str2(key1, len_key, ht->size);
	char *key2;

	while (ht->array[i]) {
		if (ht->array[i] == ts) {
			i = (i + k) % ht->size;
			continue;
		};
		key2 = get_key(ht->array[i]);
		if (!strcmp(key2, key1)) {
			free(key2);
			break;
		}
		free(key2);
		i = (i + k) % ht->size;
	}

	return ht->array[i];
	free(key1);
}
