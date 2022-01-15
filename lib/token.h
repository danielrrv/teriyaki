#ifndef TOKEN_H_
#define TOKEN_H_
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "allocator.h"
#include "token_type.h"
typedef struct
{
    TOKEN_TYPE kind;
    uint8_t *lexeme;
    int line;
    int column;
    int start;
    int end;

} token_t;

token_t *c_token(TOKEN_TYPE kind, uint8_t *lexeme, int line, int start, int end)
{
    token_t *token = (token_t *)teriyaki_calloc(1, sizeof(token_t));
    token->kind = kind;
    if (lexeme != NULL)
    {
        token->lexeme = (uint8_t *)teriyaki_malloc((end + 1 - start) * sizeof(uint8_t));
        memcpy(token->lexeme, lexeme, (end + 1 - start) * sizeof(uint8_t));
    }
    token->line = line;
    token->start = start;
    token->end = end;
    return token;
}

#endif // TOKEN_H_