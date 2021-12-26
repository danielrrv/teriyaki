#ifndef TOKEN_H_
#define TOKEN_H_
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "allocator.h"
#include "token_type.h"
typedef struct
{
    TOKEN_TYPE m_type;
    uint8_t *m_lexeme;
    uint8_t *m_literal;
    int m_line;
    int m_column;

} token_t;

token_t *c_token(TOKEN_TYPE, uint8_t *, uint8_t *, int, int);

uint8_t *toString(token_t *token) { return token->m_lexeme; }
uint8_t *getLiteral(token_t *token) { return token->m_literal; }
uint8_t *getLexeme(token_t *token) { return token->m_literal; }

token_t *c_token(TOKEN_TYPE token_type, uint8_t *lexeme, uint8_t *literal, int line, int column)
{
    token_t *token = (token_t *)teriyaki_calloc(1, sizeof(token_t));
    token->m_type = token_type;
    token->m_lexeme = NULL;
    token->m_literal = NULL;
    if (lexeme != NULL)
    {
        printf("%ld\n", strlen((char *)lexeme));
        token->m_lexeme = (uint8_t *)teriyaki_malloc(strlen((char *)lexeme) * sizeof(uint8_t));
        memcpy(token->m_lexeme, lexeme, strlen((char *)lexeme));
    }

    if (literal != NULL)
    {

        token->m_literal = (uint8_t *)teriyaki_malloc(strlen((char *)literal) * sizeof(uint8_t));
        memcpy(token->m_literal, literal, strlen((char *)literal));
    }

    token->m_line = line;
    token->m_column = column;
    return token;
}

#endif // TOKEN_H_