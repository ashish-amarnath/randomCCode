#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int HASH_TABLE_SIZE = 127;

struct ht_entry {
	char *name;
	int id;
	struct ht_entry *next;
};

struct ht_entry **hash_table;

void init_hash_table() {
	int i = 0;
	hash_table = (struct ht_entry**) malloc(sizeof(struct ht_entry*) * HASH_TABLE_SIZE);
	for (i = 0; i < HASH_TABLE_SIZE; i++) {
		hash_table[i] = NULL;
	}
}

void print_ht_entry(const struct ht_entry *ent) {
	if (ent == NULL) {
		printf ("NULL");
	} else {
		printf("{0x%p: ,name:%s, id:%d} ", ent, ent->name, ent->id);
	}
}

void print_ht() {
	int i = 0;
	struct ht_entry *begin;
	for (i = 0; i < HASH_TABLE_SIZE; i++) {
		begin = hash_table[i];
		if (begin == NULL) {
			continue;
		}
		printf("hash index:%d\n", i);
		printf("\t");
		while(begin != NULL) {
			print_ht_entry(begin);
			begin = begin->next;
		}
		printf("\n");
	}
}

struct ht_entry* get_new_entry_node(char *name, int id) {
	struct ht_entry *new_ent = (struct ht_entry*) malloc(sizeof (struct ht_entry));
	new_ent->name = strdup(name);
	new_ent->id = id;
	new_ent->next = NULL;
}

int get_hash_value(const struct ht_entry *ent) {
	return _get_hash_value(ent->name, ent->id);
}

int _get_hash_value(const char *name, const int id) {
	return (strlen(name) + id) % HASH_TABLE_SIZE;
}

struct ht_entry* get_ht_entry(const char *name, const int id) {
	int hash_idx = _get_hash_value(name, id);
	struct ht_entry *begin = hash_table[hash_idx];
	struct ht_entry *res = NULL;
	if (begin == NULL) {
		res = NULL;
	} else {
		while (begin != NULL) {
			if (!strcmp(begin->name, name) && begin->id == id) {
				break;
			}
			begin = begin->next;
		}
		res = begin;
	}

	return res;
}

void hash_table_add(char *name , int id) {
	struct ht_entry *new_ent = get_new_entry_node(name, id);
	int ht_idx = get_hash_value(new_ent);
	struct ht_entry *exists = get_ht_entry(name, id);
	if (exists) {
		print_ht_entry(exists);
		printf (" already exists\n");
		return;
	}
	struct ht_entry *begin = hash_table[ht_idx];
	if (hash_table[ht_idx] == NULL) {
		hash_table[ht_idx] = new_ent;
	} else {
		new_ent->next = hash_table[ht_idx];
		hash_table[ht_idx] = new_ent;
	}
}

void test_hash_table() {
	hash_table_add("abc", 2);
	hash_table_add("abc", 2);
	hash_table_add("abc", 5);
	hash_table_add("def", 3);
	hash_table_add("ghi", 4);
	hash_table_add("jkl", 2);
	print_ht();
	printf ("search(\"abc\", 2):");
	print_ht_entry(get_ht_entry("abc", 2));
	printf ("\nsearch(\"abc\", 4):");
	print_ht_entry(get_ht_entry("abc", 4));
	printf("\n");
}

void main() {
	init_hash_table();
	test_hash_table();
}




