#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sql_parser.h"
#include "vm.h"
#include "table.h"

int main() {
    printf("Welcome to MyDB (SQLite-inspired)\n");
    printf("Database: mydb.db\n");

    char input[1024];
    Table* table = db_open("mydb.db");

    printf("mydb > ");
    while (fgets(input, sizeof(input), stdin)) {
        SqlCommandType cmd = parse_sql(input);

if (cmd == SQL_INSERT) {
    Row row;

    int id;
    char username[COLUMN_USERNAME_SIZE + 1];

    // Simple SQL value parsing
int matched = sscanf(input, "INSERT INTO users VALUES ( %d , '%32[^']' )", &id, username);

    if (matched == 2) {
        row.id = id;
        strcpy(row.username, username);
        insert_row(table, &row);
    } else {
        printf("[Parser] Failed to parse INSERT values.\n");
    }
}
        else if (cmd == SQL_SELECT) {
            select_all(table);
        }
        else if (cmd == SQL_DELETE) {
            printf("[VM] DELETE not implemented yet.\n");
        }
        else {
            printf("[Parser] Unknown or unsupported command.\n");
        }

        printf("mydb > ");
    }

    db_close(table);
    return 0;
}
