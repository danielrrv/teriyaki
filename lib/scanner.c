#include "scanner.h"
#include <stdlib.h>
#include <stdio.h>

Scanner *_scanner(const char *source)
{
    Scanner *scanner = (Scanner *)malloc(sizeof(Scanner));
    scanner->source = (char *)malloc(sizeof(source));
    scanner->tokens = (Token *)malloc(sizeof(Token));
    memcpy(scanner->source, source, sizeof(source));
    return scanner;
}

bool is_at_end(Scanner *scanner)
{
    return (scanner->current >= strlen(scanner->source));
}
void to_string(const Scanner *scanner)
{

    for (int i = 0; i < sizeof(scanner->tokens) / sizeof(Token *); i++)
    {
        printf("Token:%s\n", getLexeme(scanner->tokens[i]));
    }
    printf("%s\n", "-----------");
    for (int i = 0; i < sizeof(scanner->tokens) / sizeof(Token *); i++)
    {
        printf("%s\n", getLiteral(scanner->tokens[i]));
    }
}