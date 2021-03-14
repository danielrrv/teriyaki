
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Token.h"

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
bool is_at_end(const Scanner *);
bool is_number(const Scanner *);
bool is_alpha(const Scanner *);
bool is_alpha_numeric(const Scanner *);
void to_string(const Scanner *);
Token *scans(void);
bool move(Scanner *);
char char_at_current(const Scanner *);
void scan_token(const char, const Scanner *);
void p_identifier(const Scanner *);
void p_number(const Scanner *);
void add_token(TOKEN_TYPE, const char *, const char *, int, Scanner *);
void p_string(Scanner *);
