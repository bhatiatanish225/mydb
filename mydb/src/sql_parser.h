// src/sql_parser.h

#ifndef SQL_PARSER_H
#define SQL_PARSER_H

typedef enum {
    SQL_UNKNOWN,
    SQL_SELECT,
    SQL_INSERT,
    SQL_DELETE
} SqlCommandType;

SqlCommandType parse_sql(const char* input);

#endif
