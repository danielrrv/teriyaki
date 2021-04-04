#ifndef TOKEN_H_
#define TOKEN_H_
#include <stdlib.h>
#include "token_type.h"
typedef struct{
    TOKEN_TYPE m_type;
    char * m_lexeme;
    char * m_literal;
    int m_line;
} Token;

Token *c_token(TOKEN_TYPE, char *, char *, int);
char *toString(Token *);
char *getLiteral(Token *);
char *getLexeme(Token *);

#endif //TOKEN_H_