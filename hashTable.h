#ifndef HASH_TABLE
#define HASH_TABLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256

#define TABLE_SIZE 5
#define NEW_TABLE_SIZE 10

// (key, value) --> (name, apples)
typedef struct person {
    char* name;
    int apples;
    struct person* next;
} person;

// Hash Table
typedef struct hash_table {
    int size;
    int count;
    person** entries;
} hash_table;

unsigned int hash(char* str, int max);

hash_table* init_hash_table(int size);

bool free_table(hash_table* table);

void print_table(hash_table* table, int size);

bool insert_table(hash_table* table, person* p);

person* get_name(hash_table* table, char* name);

void resize(hash_table* table, int new_size);

#endif