#ifndef SCANNER_H_
#define SCANNER_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"
#include "allocator.h"

enum
{
    OUTSIZE = 1024 * 80,
    BUFFERSIZE = 96

}; //*kb

typedef struct
{
    uint8_t *name;
    TOKEN_TYPE kind;
} keyword_t;

typedef struct
{
    int current;
    int line;
    int column;
    uint8_t *source;
    token_t **tokens;
    size_t token_length;
} scanner_t;

typedef struct Keyword
{
    uint8_t *name;
    TOKEN_TYPE kind;
} keyworkd_t;

keyworkd_t keywords[] = {
    {(uint8_t *)"true", TRUE},
    {(uint8_t *)"false", FALSE},
    {(uint8_t *)"if", IF},
    {(uint8_t *)"for", FOR},
    {(uint8_t *)"while", WHILE},
    {(uint8_t *)"be", BE},
    {(uint8_t *)"for", FOR},
    {(uint8_t *)"while", WHILE},
    {(uint8_t *)"Object", OBJECT},
    {(uint8_t *)"being", BEING},
    {(uint8_t *)"otherwise", OTHERWISE},
    {(uint8_t *)"const", CONST},
    {(uint8_t *)"or", OR},
    {(uint8_t *)"and", AND},
    {(uint8_t *)"as", AS}};

scanner_t *_scanner(const char *source)
{
    scanner_t *scanner = (scanner_t *)malloc(sizeof(scanner_t));
    scanner->source = (uint8_t *)malloc(strlen(source));
    scanner->column = 0;
    scanner->line = 0;
    scanner->current = 0;
    scanner->tokens = NULL;
    scanner->token_length = 0;
    memcpy(scanner->source, source, strlen(source));
    return scanner;
}

static bool is_at_end_lexer(const scanner_t *scanner)
{
    return (scanner->current >= strlen((char *)scanner->source));
}

static bool move_lexer(scanner_t *scanner)
{
    if (is_at_end_lexer(scanner))
    {
        return false;
    }
    scanner->current++;
    scanner->column++;
    return true;
}

static uint8_t char_at_current(scanner_t *scanner)
{
    return (uint8_t)scanner->source[scanner->current];
}

static void add_token(TOKEN_TYPE token_type, scanner_t *scanner)
{
    token_t *token = c_token(token_type, NULL, scanner->line, scanner->current, scanner->column + 1);
    token_t **new_ptr = (token_t **)realloc(scanner->tokens, (scanner->token_length + 1) * sizeof(token_t));
    new_ptr[scanner->token_length] = token;
    scanner->tokens = new_ptr;
    (scanner->token_length)++;
}

static void add_token_with_lexeme(TOKEN_TYPE token_type, uint8_t *lexeme, scanner_t *scanner, int start, int end)
{
    token_t *token = c_token(token_type, lexeme, scanner->line, start, end);
    token_t **new_ptr = (token_t **)realloc(scanner->tokens, (scanner->token_length + 1) * sizeof(token_t));
    new_ptr[scanner->token_length] = token;
    scanner->tokens = new_ptr;
    (scanner->token_length)++;
}

static bool is_digit(uint8_t c)
{
    return c >= '0' && c <= '9';
}

static bool is_alpha(uint8_t c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

static void scan_number(scanner_t *scanner)
{
    int start = scanner->current;
    while (is_digit(scanner->source[scanner->current]))
        move_lexer(scanner);
    if (scanner->source[scanner->current] == '.' && move_lexer(scanner))
    {
        while (is_digit(scanner->source[scanner->current]) && move_lexer(scanner))
            ;
    }
    uint8_t *number = (uint8_t *)teriyaki_malloc((scanner->current - start + 1) * sizeof(uint8_t));
    memcpy(number, &scanner->source[scanner->current], scanner->current - start);
    add_token_with_lexeme(NUMBER, number, scanner, start, scanner->current);
}
static bool is_number(uint8_t number)
{
    return number >= '0' && number <= '9';
}

static bool is_alpha_numeric(const uint8_t c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || is_number(c) || c == '_');
}

static void scan_identifier(scanner_t *scanner)
{
    int start = scanner->current;
    while (is_alpha_numeric(scanner->source[scanner->current + 1]))
    {
        move_lexer(scanner);
    }
    uint8_t *identifier = (uint8_t *)teriyaki_malloc((scanner->current + 1 + 1 - start) * sizeof(uint8_t));
    memset(identifier, '\0', scanner->current + 1 + 1 - start);
    memcpy(identifier, &scanner->source[start], (int)(scanner->current + 1 - start));
    printf("start:%d\tcurrent:%d\ttext:%s\n", start, scanner->current + 1, identifier);
    for (int i = 0; i < (sizeof(keywords) / sizeof(keyworkd_t)); i++)
    {
        int rx = strncmp((char *)identifier, (char *)keywords[i].name, strlen((char *)identifier));
        if (rx == 0)
        {
            // printf("keyword:%s, %d\n", keywords[i].name, keywords[i].kind);
            add_token_with_lexeme(keywords[i].kind, keywords[i].name, scanner, start, scanner->current);
            return;
        }
    }
    add_token_with_lexeme(IDENTIFIER, identifier, scanner, start, scanner->current);

    return;
}

static void report_scanner_error(uint8_t *identifer, int line, int column)
{
    printf("Error:Unexpected Token %s\n at  line %d column %d", identifer, line, column);
    exit(1);
}
uint8_t scan_string(scanner_t *scanner)
{
    int start = scanner->current;
    while (scanner->source[scanner->current + 1] != '"')
    {
        move_lexer(scanner);
        if (scanner->source[scanner->current + 1] == '\n')
            ((*scanner).line)++;
    }
    move_lexer(scanner);
    uint8_t *string = (uint8_t *)teriyaki_malloc(scanner->current + 1 + 1 - start);
    memset(string, '\0', scanner->current + 1 + 1 - start);
    memcpy(string, &scanner->source[start], (int)(scanner->current + 1 - start));
    // printf("start:%d\tcyurrent:%d\ttext:%s\n", start, scanner->current + 1, string);
    add_token_with_lexeme(STRING, string, scanner, start, scanner->current);
}

static void scan_token(scanner_t *scanner)
{
    printf("char:%d\n", scanner->source[scanner->current]);
    switch (scanner->source[scanner->current])
    {
    case '(':
        add_token(LEFT_PAREN, scanner);
        break;
    case ')':
        add_token(RIGHT_PAREN, scanner);
        break;
    case '{':
        add_token(LEFT_BRACE, scanner);
        break;
    case '}':
        add_token(RIGHT_BRACE, scanner);
        break;
    case ',':
        add_token(COMMA, scanner);
        break;
    case '.':
        add_token(DOT, scanner);
        break;
    case '-':
        add_token(MINUS, scanner);
        break;
    case '+':
        add_token(PLUS, scanner);
        break;
    case ';':
        add_token(SEMICOLON, scanner);
        break;
    case ':':
        add_token(COLON, scanner);
        break;
    case '*':
        add_token(STAR, scanner);
        break;
    case '!':
        add_token(scanner->source[scanner->current + 1] == '=' ? BANG_EQUAL : BANG, scanner);
        break;
    case '=':
        add_token(scanner->source[scanner->current + 1] == '=' ? EQUAL_EQUAL : EQUAL, scanner);
        break;
    case '<':
        add_token(scanner->source[scanner->current + 1] == '=' ? LESS_EQUAL : LESS, scanner);
        break;
    case '&':
        add_token(AMPERSAND, scanner);
        break;
    case '?':
        add_token(INTERROGATION, scanner);
        break;
    case '#':
        add_token(NUMERAL, scanner);
        break;
    case '>':
        add_token(scanner->source[scanner->current + 1] == '=' ? GREATER_EQUAL : GREATER, scanner);
        break;
    case '|':
        add_token(PIPE, scanner);
        break;
    case '%':
        add_token(PERCENT, scanner);
        break;
    case '/':
        if (scanner->source[scanner->current + 1] == '/')
        {
            // A comment goes until the end of the line.
            while (scanner->source[scanner->current] != '\n' && !is_at_end_lexer(scanner))
                move_lexer(scanner);
        }
        else
        {
            add_token(SLASH, scanner);
        }
        break;
    // case ' ':
    //     add_token(SPACE, scanner);
    //     break;
    case '\t':
        add_token(TAB, scanner);
        break;
    case ' ':
    case '\r':

        // Ignore whitespace.
        break;
    case '\n':
        add_token(NEW_LINE, scanner);
        (scanner->line)++;
        (scanner->column) = 0;
        break;
    case '"':
        scan_string(scanner);
        break;

    default:

        if (is_number(scanner->source[scanner->current]))
        {
            scan_number(scanner);
            break;
        }
        else if (is_alpha(scanner->source[scanner->current]))
        {
            scan_identifier(scanner);
            break;
        }
        else
        {
            printf("Lines: %d:%d\tError:Unexpected Token [%c]\n ",
                   scanner->line,
                   scanner->column,
                   scanner->source[scanner->current]);
            exit(1);
        }
    }
    move_lexer(scanner);
}

token_t **scan(scanner_t *scanner)
{
    while (!is_at_end_lexer(scanner))
    {
        char character = scanner->source[scanner->current];
        scan_token(scanner);
    }
    token_t *end_of_file = c_token(END_OF_FILE, NULL, scanner->line, scanner->current, scanner->current);
    token_t **new_ptrs = (token_t **)realloc(scanner->tokens, (scanner->token_length + 1) * sizeof(token_t));
    new_ptrs[scanner->token_length] = end_of_file;
    scanner->tokens = new_ptrs;
    (scanner->token_length)++;
    return scanner->tokens;
}

#endif // SCANNER_H_