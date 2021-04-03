#include "scanner.h"
#include <stdlib.h>
#include <stdio.h>

Scanner *_scanner(const char *source)
{
    Scanner *scanner = (Scanner *)malloc(sizeof(Scanner));
    scanner->source = (char *)malloc(sizeof(source));
    scanner->len = 0;
    scanner->column = 0;
    scanner->line = 0;
    scanner->current = 0;
    scanner->tokens = NULL;
    memcpy(scanner->source, source, sizeof(source));
    return scanner;
}

bool is_at_end(const Scanner *scanner)
{
    return (scanner->current >= strlen(scanner->source));
}
void to_string(const Scanner *scanner)
{
    int len  = *(scanner->tokens + 1) - scanner->tokens;
    for (int i = 0; i < len ; i++)
    {
        printf("Token:%s\n", getLexeme(scanner->tokens[i]));
    }
    printf("%s\n", "-----------");
    for (int i = 0; i < len; i++)
    {
        printf("%s\n", getLiteral(scanner->tokens[i]));
    }
}

static bool move(Scanner *scanner)
{
    if (is_at_end(scanner))
    {
        return false;
    }
    ((*scanner).current)++;
    return true;
}

char char_at_current(Scanner *scanner)
{
    ((*scanner).column)++;
    return scanner->source[scanner->current];
}
void add_token(TOKEN_TYPE token_type, char *lexeme, char *literal, Scanner *scanner)
{
    int len = ++(scanner->len);
    Token *token = c_token(token_type, lexeme, NULL, scanner->line);
    Token **more = (Token **)realloc(scanner->tokens, len);
    more[len - 1] = token;
    scanner->tokens = more;
}

void scan_token(const char c, Scanner *scanner)
{
    switch (c)
    {
    case '(':
        add_token(LEFT_PAREN);
        break;
    case ')':
        add_token(RIGHT_PAREN);
        break;
    case '{':
        add_token(LEFT_BRACE);
        break;
    case '}':
        add_token(RIGHT_BRACE);
        break;
    case ',':
        add_token(COMMA);
        break;
    case '.':
        add_token(DOT);
        break;
    case '-':
        add_token(MINUS);
        break;
    case '+':
        add_token(PLUS);
        break;
    case ';':
        add_token(SEMICOLON);
        break;
    case ':':
        add_token(COLON);
        break;
    case '*':
        add_token(STAR);
        break;
    case '!':
        add_token(c == '=' ? BANG_EQUAL : BANG);
        break;
    case '=':
        add_token(c == '=' ? EQUAL_EQUAL : EQUAL);
        break;
    case '<':
        add_token(c == '=' ? LESS_EQUAL : LESS);
        break;
    case '&':
        add_token(HUIT);
        break;
    case '?':
        add_token(INTERROGATION);
        break;
    case '>':
        add_token(c == '=' ? GREATER_EQUAL : GREATER);
        break;
    case '/':
        if (c == '/')
        {
            // A comment goes until the end of the line.
            while (scanner->source[scanner->current] != '\n' && !is_at_end(scanner))
                move(scanner);
        }
        else
        {
            add_token(SLASH);
        }
        break;
    case ' ':
    case '\r':
    case '\t':
        // Ignore whitespace.
        break;
    case '\n':
        (scanner->line)++;
        (scanner->column) = 0;
        break;
    case '"':
        add_token(STRING);
        p_string(scanner);
        break;
    default:
        if (is_number(scanner))
        {
            p_number(scanner);
            break;
        }
        else if (is_alpha(scanner))
        {
            p_identifier(scanner);
            break;
        }
        else
        {
            printf("Lines: %d:%d\tError%s :%s:Unexpected Token\n ",
                   scanner->line,
                   scanner->column,
                   (int)scanner->source[scanner->current],
                   scanner->source[scanner->current]);
            break;
        }
    }
    move(scanner);
}
