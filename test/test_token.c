#include "assert.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../lib/token.h"
#include "../lib/scanner.h"
#include "../lib/token_type.h"
#include "../lib/init.h"


void TESTCASE_read_file(char * filename){
	char lfilename[55];
	memset(lfilename, '\0', 55);
	strncpy(lfilename, filename, 55);
	char * out = read_file(filename);
	assert(sizeof(out) >0);
	free(out);
}

// void TESTCASE_scanner_constructor(){
// 	char * out ="class {int = 2; string str = ''}";
// 	Scanner *scanner = _scanner(out);
// }


void TESTCASE_token_constructor()
{
	TOKEN_TYPE toke_type = LEFT_BRACE;
	char *lexeme = "c";
	char *literal = "class";
	int line = 10;
	int column = 10;

	Token *token = c_token(toke_type, lexeme, literal, line, column);
	assert(token != NULL);
	assert(token->m_line == line);
	assert(token->m_lexeme == lexeme);
	assert(token->m_literal == literal);
	free(token);
}


void TESTCASE_run_script(char * filename){
	char lfilename[55];
	memset(lfilename, '\0', 55);
	strncpy(lfilename, filename, 55);
	char * source = read_file(filename);
	// printf("[%s]\n", source);
	Scanner *scanner = _scanner(source);
	// printf("%s\n", scanner->source);
	// assert(source==scanner->source);
	scan(scanner);
	free(scanner);
	free(source);
}