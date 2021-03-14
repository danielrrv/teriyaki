
#include "token_type.h"

typedef struct
{
    TOKEN_TYPE m_type;
    char *m_lexeme;
    char *m_literal;
    int m_line;
} Token;

Token *_Token(TOKEN_TYPE *, char *lexeme, char *, int);
char *toString(Token);
char *getLiteral(Token);
char *getLexeme(Token);