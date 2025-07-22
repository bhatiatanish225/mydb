// src/vm.c

#include "vm.h"
#include <stdio.h>

void execute_query(SqlCommandType cmd) {
    switch (cmd) {
        case SQL_SELECT:
            printf("[VM] Executing SELECT operation...\n");
            break;
        case SQL_INSERT:
            printf("[VM] Executing INSERT operation...\n");
            break;
        case SQL_DELETE:
            printf("[VM] Executing DELETE operation...\n");
            break;
        default:
            printf("[VM] Cannot execute: Unknown command.\n");
    }
}
