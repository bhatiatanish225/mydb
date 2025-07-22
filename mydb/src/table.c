// src/table.c

#include "table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void serialize_row(Row* source, void* destination) {
    memcpy(destination, &(source->id), sizeof(source->id));
    memcpy(destination + sizeof(source->id), &(source->username), COLUMN_USERNAME_SIZE + 1);
}

void deserialize_row(void* source, Row* destination) {
    memcpy(&(destination->id), source, sizeof(destination->id));
    memcpy(&(destination->username), source + sizeof(destination->id), COLUMN_USERNAME_SIZE + 1);
}

Table* db_open(const char* filename) {
    Pager* pager = pager_open(filename);
    Table* table = (Table*) malloc(sizeof(Table));
    table->pager = pager;
    table->root_page_num = 0;  // Use page 0 for simplicity
    return table;
}

void db_close(Table* table) {
    pager_close(table->pager);
    free(table);
}

void insert_row(Table* table, Row* row) {
    void* page = get_page(table->pager, table->root_page_num);

    uint32_t num_rows = table->pager->num_pages * ROWS_PER_PAGE;

    for (uint32_t i = 0; i < num_rows; i++) {
        void* row_slot = page + i * ROW_SIZE;
        Row temp;
        deserialize_row(row_slot, &temp);
        if (temp.id == 0) {  // Simplistic empty slot check
            serialize_row(row, row_slot);
            pager_flush(table->pager, table->root_page_num);
            printf("[Table] Inserted row ID: %d, Name: %s\n", row->id, row->username);
            return;
        }
    }

    printf("[Table] Page full. Row insertion failed.\n");
}

void select_all(Table* table) {
    void* page = get_page(table->pager, table->root_page_num);
    uint32_t num_rows = table->pager->num_pages * ROWS_PER_PAGE;

    printf("[Table] Rows:\n");

    for (uint32_t i = 0; i < num_rows; i++) {
        void* row_slot = page + i * ROW_SIZE;
        Row row;
        deserialize_row(row_slot, &row);

        if (row.id != 0) {
            printf("ID: %d, Username: %s\n", row.id, row.username);
        }
    }
}
