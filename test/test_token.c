#include "assert.h"
#include <stdlib.h>
#include <stdio.h>
#include "../lib/token.h"
#include "../lib/token_type.h"

void TESTCASE_token_constructor()
{
	TOKEN_TYPE toke_type = LEFT_BRACE;
	char *lexeme = "c";
	char *literal = "class";
	int line = 10;

	Token *token = c_token(toke_type, lexeme, literal, line);
	assert(token != NULL);
	assert(token->m_line == line);
	assert(token->m_lexeme == lexeme);
	assert(token->m_literal == literal);
}
