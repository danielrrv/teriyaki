

#include "token.h"

Token *c_token(TOKEN_TYPE *token_type, char *lexeme, char *literal, int line)
{
    Token *token = (Token *)calloc(1, sizeof(Token));
    token->m_type = token_type;
    token->m_lexeme = lexeme;
    token->m_literal = literal;
    token->m_line = line;
    return token;
}
char *toString(Token *token) { return token->m_lexeme; }
char *getLiteral(Token *token) { return token->m_literal; }
char *getLexeme(Token *token) { return token->m_literal; }
