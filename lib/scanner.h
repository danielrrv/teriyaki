#ifndef SCANNER_H_
#define SCANNER_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"

typedef struct keyword
{
    char *name;
    TOKEN_TYPE type;
} keyword;

typedef struct
{
    int current;
    int line;
    int column;
    char *source;
    Token **tokens;
    /*lenght of the token already allocated*/
    int len;
} Scanner;
Scanner *_scanner(const char *);
void scan(Scanner *);
bool is_at_end(const Scanner *);
bool is_number(const char);
bool is_alpha(const Scanner *);
bool is_alpha_numeric(const Scanner *);
void to_string(const Scanner *);
Token *scans(void);
bool move(Scanner *);
char char_at_current(Scanner *);
void scan_token(char, Scanner *);
bool p_identifier(Scanner *);
void p_number(Scanner *);
// void add_identifier(TOKEN_TYPE, const char *, const char *, int, Scanner *);
void add_token_with_lexeme(TOKEN_TYPE, char *, Scanner *);
void add_token_with_literal(TOKEN_TYPE, char *, Scanner *);
void p_string(Scanner *);
#endif //SCANNER_H_