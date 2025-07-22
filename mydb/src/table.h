// src/table.h

#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include "pager.h"

#define COLUMN_USERNAME_SIZE 32

typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
} Row;

#define ROW_SIZE (sizeof(uint32_t) + COLUMN_USERNAME_SIZE + 1)
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)

typedef struct {
    Pager* pager;
    uint32_t root_page_num;
} Table;

void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);

Table* db_open(const char* filename);
void db_close(Table* table);

void insert_row(Table* table, Row* row);
void select_all(Table* table);

#endif
