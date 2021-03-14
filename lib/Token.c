

#include "token.h"
char *toString(Token token) { return token->m_lexeme; }
char *getLiteral(Token token) { return token->m_literal; }
char *getLexeme(Token token) { return token->m_literal; }
