#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "scanner.h"
#include "token.h"
#include "token_type.h"
typedef struct Keyword
{
    char *name;

    TOKEN_TYPE token_type;
} keyworkd_t;

keyworkd_t keywords[] = {
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
    Scanner *scanner = (Scanner *)malloc(sizeof(Scanner));
    scanner->source = (char *)malloc(strlen(source));
    scanner->len = 0;
    scanner->column = 0;
    scanner->line = 0;
    scanner->current = 0;
    scanner->tokens = NULL;
    memcpy(scanner->source, source, strlen(source));
    return scanner;
}

void scan(Scanner *scanner)
{
    while (!is_at_end(scanner))
    {
        char character = scanner->source[scanner->current];
        scan_token(character, scanner);
    }
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
    scanner->current++;
    scanner->column++;
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
    // printf("%d-%d-lexeme: %s\n", token_type, len, lexeme);
    Token *token = c_token(token_type, lexeme, NULL, scanner->line, scanner->column);
    Token **more = (Token **)realloc(scanner->tokens, len * sizeof(Token));
    more[len - 1] = token;
    scanner->tokens = more;
}

void add_token_with_literal(TOKEN_TYPE token_type, char *literal, Scanner *scanner)
{
    int len = ++(scanner->len);
    Token *token = c_token(token_type, NULL, literal, scanner->line, scanner->column);
    scanner->tokens = (Token **)realloc(scanner->tokens, len * sizeof(Token));
    scanner->tokens[len - 1] = token;
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

bool is_alpha_numeric(const char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || is_number(c) || c == '_');
}

void p_string(Scanner *scanner)
{
    int start = scanner->current;
    // printf("[%c]", scanner->source[scanner->current]);
    while (scanner->source[scanner->current + 1] != '"' && move(scanner))
    {
        
        if (scanner->source[scanner->current + 1] == '\n')
            ((*scanner).line)++;
    }
    char string[BUFFERSIZE];
    memset(string, '\0', BUFFERSIZE);
    // printf("string: %s\n\tstart:%d\tcurrent:%d\n", string,start ,scanner->current);
    strncpy(string, &scanner->source[start], (int)(scanner->current - start));
    printf("string: %s", string);
    add_token_with_literal(STRING, string, scanner);
}

bool p_identifier(Scanner *scanner)
{
    int start = scanner->current;
    char * initial_char = &(scanner->source[scanner->current]);
    while (is_alpha_numeric(scanner->source[scanner->current]) && move(scanner));
    char text[BUFFERSIZE];
    memset(text, '\0', BUFFERSIZE);
    strncpy(text, initial_char, (int)(scanner->current - start));
    // printf("start:%d\tcurrent:%d\ttext:%s\n", start,scanner->current, text );
    for (int i = 0; i < (sizeof(keywords) / sizeof(keyworkd_t)); i++)
    {
        // printf("%s, %s, %d", text, keywords[i].name, (int)strlen(text));
        int rx = strncmp(text, keywords[i].name, strlen(text));
        if (rx == 0)
        {
            add_token_with_lexeme(keywords[i].token_type, keywords[i].name, scanner);
            return true;
        }
    }
    add_token_with_lexeme(IDENTIFIER, text, scanner);
    return true;
}

void report_scanner_error(char *identifer, int line, int column)
{
    printf("Error:Unexpected Token %s\n at  line %d column %d", identifer, line, column);
    exit(1);
}

void scan_token(char c, Scanner *scanner)
{
    char local_char[1];
    memset(local_char, '\0', 1);
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
        add_token_with_lexeme(AMPERSAND, local_char, scanner);
        break;
    case '?':
        add_token_with_lexeme(INTERROGATION, local_char, scanner);
        break;
    case '#':
        add_token_with_lexeme(NUMERAL, local_char, scanner);
        break;
    case '>':
        add_token_with_lexeme(c == '=' ? GREATER_EQUAL : GREATER, local_char, scanner);
        break;
    case '%':
        add_token_with_lexeme(PERCENT, local_char, scanner);
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
            printf("Lines: %d:%d\tError:Unexpected Token [%c]\n ",
                   scanner->line,
                   scanner->column,
                   scanner->source[scanner->current]);
            exit(1);
        }
    }
    move(scanner);
}
