#include "hashTable.h"

// djb2 Hash Function by Dan Bernstein
unsigned int hash(char* str, int max) {
	unsigned long hash = 5381;
	int c;
	unsigned char* u_str = (unsigned char*)str;

	while (c = *u_str++) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash % max;
}

// Initialize a table by making it empty
hash_table* init_hash_table(int size) {

	if (size <= 0) {
		printf("Invalid Size!");
		return NULL;
	}

	hash_table* table = malloc(sizeof(hash_table));
	if (table == NULL) {
		return NULL;
	}

	table->entries = malloc(sizeof(hash_table) * size);
	if (table->entries == NULL) {
		return NULL;
	}

	for (int i = 0; i < size; i++) {
		table->entries[i] = NULL;
	}

	table->size = size;
	table->count = 0;
}

// Free memory that was allocated to the hash table
bool free_table(hash_table* table) {
	printf("Destroying hash table with size: %d\n", table->size);

	if (table == NULL) {
		return false;
	}

	if (table->count == 0) {
		return false;
	}

	for (int i = 0; i < table->size; i++) {
		person* p = table->entries[i];

		if (p != NULL) {
			free(p);
		}
	}

	free(table->entries);
	free(table);

	return true;
}

// Print table
void print_table(hash_table* table, int size) {

	printf("List of people's name and number of apples:\n");

	for (int i = 0; i < table->size; i++) {
		if (table->entries[i] == NULL) {
			printf("\t%i\t---\n", i);
		}
		else {
			printf("\t%i\t ", i);
			person* tmp = table->entries[i];

			while (tmp != NULL) {
				printf("(Name: %s, Apples: %d) - ", tmp->name, tmp->apples);
				tmp = tmp->next;
			}
			printf("\n");
		}
	}

	printf("End of List\n\n");
}

// Add a person to the table
bool insert_table(hash_table* table, person* p) {
	if (table == NULL || p == NULL) {
		return false;
	}

	int index = hash(p->name, table->size);

	person* tmp = table->entries[index];

	// Checks if a person with the name exists
	while (tmp != NULL) {
		if (strcmp(tmp->name, p->name) == 0) {

			printf("Can't add the name, %s, because it already exists!\n",
				tmp->name);

			return false;
		}

		tmp = tmp->next;
	}

	// allocate entry
	person* new_p = malloc(sizeof(person));
	if (new_p == NULL) return false;

	// set new person's values
	new_p->name = p->name;
	new_p->apples = p->apples;
	new_p->next = table->entries[index];

	// insert new person at the beginning of the linked list
	table->entries[index] = new_p;

	// increase count
	table->count++;

	return true;
}

// Find a person by their name in the table
person* get_name(hash_table* table, char* name) {
	int index = hash(name, table->size);

	person* tmp = table->entries[index];

	while (tmp != NULL) {
		if (strncmp(tmp->name, name, MAX_NAME) == 0) {
			return tmp;
		}

		tmp = tmp->next;
	}

	return NULL;
}

// Resize the table
void resize(hash_table* table, int new_size) {
	hash_table* new_table = init_hash_table(new_size);

	for (int i = 0; i < table->size; i++) {
		person* current = table->entries[i];
		while (current != NULL) {
			insert_table(new_table, current);
			current = current->next;
		}
	}

	table->count = new_table->count;

	table->size = new_table->size;

	person** current_entries = table->entries;
	table->entries = new_table->entries;
}