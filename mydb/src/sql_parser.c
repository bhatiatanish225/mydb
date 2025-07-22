// src/sql_parser.c

#include "sql_parser.h"
#include <string.h>
#include <ctype.h>

// Converts input to uppercase for case-insensitive comparison
void to_upper(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

SqlCommandType parse_sql(const char* input) {
    char command[32];
    sscanf(input, "%31s", command);

    to_upper(command);

    if (strcmp(command, "SELECT") == 0) {
        return SQL_SELECT;
    } else if (strcmp(command, "INSERT") == 0) {
        return SQL_INSERT;
    } else if (strcmp(command, "DELETE") == 0) {
        return SQL_DELETE;
    } else {
        return SQL_UNKNOWN;
    }
}
