#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "scanner.h"
#include "token.h"
#include "token_type.h"
struct Keyword
{
    char *name;

    TOKEN_TYPE token_type;
};

struct Keyword keywords[] = {
    {"if", IF},
    {"for", FOR},
    {"while", WHILE},
    {"if", IF},
    {"for", FOR},
    {"while", WHILE},
    {"class", CLASS},
    {"const", CONST},
    {"or", OR},
    {"and", AND}};

Scanner *_scanner(const char *source)
{
    printf("%s", source);
    Scanner *scanner = (Scanner *)malloc(sizeof(Scanner));
    scanner->source = (char *)malloc(sizeof(source));
    scanner->len = 0;
    scanner->column = 0;
    scanner->line = 0;
    scanner->current = 0;
    scanner->tokens = NULL;
    memcpy(scanner->source, source, sizeof(*source));
    return scanner;
}

void scan(Scanner *scanner)
{
    printf("%s", scanner->source);
    // while (!is_at_end(scanner))
    // {
    //     char character = scanner->source[scanner->current];
    //     scan_token(character, scanner);
    // }
    // return scanner->tokens;
}

bool is_at_end(const Scanner *scanner)
{
    return (scanner->current >= strlen(scanner->source));
}
void to_string(const Scanner *scanner)
{
    // int len  = *(scanner->tokens + 1) - scanner->tokens;
    int len = sizeof(scanner->tokens) / sizeof(Token *);
    for (int i = 0; i < len; i++)
    {
        printf("Token:%s\n", getLexeme(scanner->tokens[i]));
    }
    printf("%s\n", "-----------");
    for (int i = 0; i < len; i++)
    {
        printf("%s\n", getLiteral(scanner->tokens[i]));
    }
}

bool move(Scanner *scanner)
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

void add_token_with_lexeme(TOKEN_TYPE token_type, char *lexeme, Scanner *scanner)
{
    int len = ++(scanner->len);
    Token *token = c_token(token_type, lexeme, NULL, scanner->line);
    Token **more = (Token **)realloc(scanner->tokens, len);
    more[len - 1] = token;
    scanner->tokens = more;
}
void add_token_with_literal(TOKEN_TYPE token_type, char *literal, Scanner *scanner)
{
    int len = ++(scanner->len);
    Token *token = c_token(token_type, NULL, literal, scanner->line);
    Token **more = (Token **)realloc(scanner->tokens, len);
    more[len - 1] = token;
    scanner->tokens = more;
}
void p_number(Scanner *scanner)
{
    int start = scanner->current;
    while (isdigit(scanner->source[scanner->current]))
        move(scanner);
    if (scanner->source[scanner->current] == '.' && move(scanner))
    {
        while (isdigit(scanner->source[scanner->current]) && move(scanner))
            ;
    }
    //FIXME: unsafe operation.
    char value[55];
    memcpy(value, &scanner->source[scanner->current], scanner->current - start);
    add_token_with_lexeme(NUMBER, value, scanner);
}
bool is_number(char number)
{
    return number >= '0' && number <= '9';
}

void p_string(Scanner *scanner)
{
    int start = scanner->current;
    while (scanner->source[scanner->current] != '"' && move(scanner))
    {
        if (scanner->source[scanner->current] == '\n')
            ((*scanner).line)++;
    }
    char value[255];
    memcpy(value, &scanner->source[scanner->current], scanner->current - start);
    add_token_with_literal(STRING, value, scanner);
}

bool p_identifier(Scanner *scanner)
{
    int start = scanner->current;
    while (isalnum(scanner->source[scanner->current]) && move(scanner))
        ;
    char text[55];
    memcpy(text, &scanner->source[scanner->current], scanner->current - start);
    for (int i = 0; i < sizeof(keywords); i++)
    {
        int rx = strncmp(text, keywords[i].name, sizeof(text));
        if (rx == 0)
        {
            add_token_with_literal(IDENTIFIER, keywords[i].name, scanner);
            return true;
        }
    }
    return false;
}

void scan_token(char c, Scanner *scanner)
{
    char local_char[8];
    memset(local_char, '\0', 8);
    local_char[0] = c;
    switch (c)
    {
    case '(':

        add_token_with_lexeme(LEFT_PAREN, local_char, scanner);
        break;
    case ')':
        add_token_with_lexeme(RIGHT_PAREN, local_char, scanner);
        break;
    case '{':
        add_token_with_lexeme(LEFT_BRACE, local_char, scanner);
        break;
    case '}':
        add_token_with_lexeme(RIGHT_BRACE, local_char, scanner);
        break;
    case ',':
        add_token_with_lexeme(COMMA, local_char, scanner);
        break;
    case '.':
        add_token_with_lexeme(DOT, local_char, scanner);
        break;
    case '-':
        add_token_with_lexeme(MINUS, local_char, scanner);
        break;
    case '+':
        add_token_with_lexeme(PLUS, local_char, scanner);
        break;
    case ';':
        add_token_with_lexeme(SEMICOLON, local_char, scanner);
        break;
    case ':':
        add_token_with_lexeme(COLON, local_char, scanner);
        break;
    case '*':
        add_token_with_lexeme(STAR, local_char, scanner);
        break;
    case '!':
        add_token_with_lexeme(c == '=' ? BANG_EQUAL : BANG, local_char, scanner);
        break;
    case '=':
        add_token_with_lexeme(c == '=' ? EQUAL_EQUAL : EQUAL, local_char, scanner);
        break;
    case '<':
        add_token_with_lexeme(c == '=' ? LESS_EQUAL : LESS, local_char, scanner);
        break;
    case '&':
        add_token_with_lexeme(HUIT, local_char, scanner);
        break;
    case '?':
        add_token_with_lexeme(INTERROGATION, local_char, scanner);
        break;
    case '>':
        add_token_with_lexeme(c == '=' ? GREATER_EQUAL : GREATER, local_char, scanner);
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
            add_token_with_lexeme(SLASH, local_char, scanner);
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
        add_token_with_lexeme(STRING, local_char, scanner);
        p_string(scanner);
        break;
    default:
        if (is_number(scanner->source[scanner->current]))
        {
            p_number(scanner);
            break;
        }
        else if (isalpha(scanner->source[scanner->current]))
        {
            p_identifier(scanner);
            break;
        }
        else
        {
            // printf("Lines: %d:%d\tError%s :%s:Unexpected Token\n ",
            //        scanner->line,
            //        scanner->column,
            //        (int)scanner->source[scanner->current],
            //        scanner->source[scanner->current]);
            // break;
        }
    }
    move(scanner);
}
