#include "hashTable.h"

int main() {

    int size = TABLE_SIZE;

    hash_table* table = init_hash_table(size);

    person ahren = { .name = "Ahren", .apples = 15 };
    person ryan = { .name = "Ryan", .apples = 21 };
    person sonia = { .name = "Sonia", .apples = 10 };

    insert_table(table, &ahren);
    insert_table(table, &ryan);
    insert_table(table, &sonia);
    insert_table(table, &ahren);

    print_table(table, size);

    printf("Check if Ryan exists: ");
    person* tmp = get_name(table, "Ryan");
    if (tmp == NULL) {
        printf("Not Found!\n");
    }
    else {
        printf("Found %s.\n", tmp->name);
    }

    printf("Check if Simon exists: ");
    tmp = get_name(table, "Simon");
    if (tmp == NULL) {
        printf("Not Found!\n");
    }
    else {
        printf("Found %s.\n", tmp->name);
    }

    printf("\n");

    size = NEW_TABLE_SIZE;

    resize(table, size);

    person Bobby = { .name = "Bobby", .apples = 50 };
    person Karen = { .name = "Karen", .apples = 100 };

    insert_table(table, &Bobby);
    insert_table(table, &Karen);

    print_table(table, size);

    free_table(table);

    return 0;
}