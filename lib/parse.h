#ifndef PARSER_TERIYAKI
#define PARSER_TERIYAKI

#include "token.h"
#include "expression.h"
#include "token_type.h"

typedef struct
{
	int current;
	token_t **tokens;
	expression_t **statements;
	int length_statements;
} parser_t;

static bool is_at_end(parser_t *parser)
{
	return parser->tokens[(long)parser->current]->kind == END_OF_FILE;
}

static token_t *peek(parser_t *parser)
{
	return parser->tokens[parser->current];
}
static token_t *next(parser_t *parser)
{
	if (!is_at_end(parser))
	{
		parser->current++;
		return peek(parser);
	}
}
static token_t *previous(parser_t *parser)
{
	return parser->tokens[parser->current - 1];
}

static bool match(TOKEN_TYPE token, parser_t *parser)
{
	return peek(parser)->kind == token;
}
static void consume(TOKEN_TYPE token, parser_t *parser, uint8_t *error)
{
	if (token == next(parser)->kind)
	{
		parser->current++;

		return;
	}
	printf("%s", (char *)error);
	exit(1);
}

static void move(parser_t *parser)
{
	parser->current++;
}

void add_new_expr(parser_t *parser, expression_t *expression)
{
	expression_t ** new_ptr= (expression_t **)realloc(parser->statements, sizeof(expression_t) * parser->length_statements + 1);
	parser->length_statements++;
	new_ptr[parser->length_statements - 1] = expression;
	parser->statements = new_ptr;
}

expression_t *primary(parser_t *parser, expression_t *expression)
{

	if (match(TRUE, parser))
	{
		expression->literal_expr.value = (uint8_t *)teriyaki_malloc(sizeof(uint8_t) * 2);
		memcpy(&expression->literal_expr.token, peek(parser), sizeof(token_t));
		memcpy(expression->literal_expr.value, "1", sizeof(uint8_t) * 2);
		return expression;
	}
	if (match(FALSE, parser))
	{
		expression->literal_expr.value = (uint8_t *)teriyaki_malloc(sizeof(uint8_t) * 2);
		memcpy(&expression->literal_expr.token, peek(parser), sizeof(token_t));
		memcpy(expression->literal_expr.value, "0", sizeof(uint8_t) * 2);
		return expression;
	}
	if (match(NUMBER, parser) || match(STRING, parser))
	{
		expression->literal_expr.value = (uint8_t *)teriyaki_malloc(strlen((char *)peek(parser)->lexeme));
		memcpy(&expression->literal_expr.token, peek(parser), sizeof(token_t));
		memcpy(expression->literal_expr.value, peek(parser)->lexeme, strlen((char *)peek(parser)->lexeme));
		return expression;
	}
	exit(1);
}
expression_t *unary(parser_t *parser, expression_t *expression)
{
	expression = primary(parser, expression);
	if (match(BANG, parser) || match(MINUS, parser))
	{
	}
	return expression;
}
expression_t *factor(parser_t *parser, expression_t *expression)
{
	expression = unary(parser, expression);
	if (match(SLASH, parser) || match(STAR, parser))
	{
	}
	return expression;
}
expression_t *addition(parser_t *parser, expression_t *expression)
{
	expression = factor(parser, expression);
	if (match(PLUS, parser) || match(MINUS, parser))
	{
	}
	return expression;
}
expression_t *comparison(parser_t *parser, expression_t *expression)
{
	expression = addition(parser, expression);
	if (match(LESS, parser) || match(LESS_EQUAL, parser) || match(GREATER_EQUAL, parser) || match(GREATER, parser))
	{
		expression->kind = BINARY;
		memcpy(expression->binary_expr.left, expression, sizeof(token_t));
		memcpy(&expression->binary_expr.operator_token, peek(parser), sizeof(token_t));
		move(parser);
		memcpy(expression->binary_expr.right, comparison(parser, expression), sizeof(token_t));
	}
	return expression;
}

expression_t *equality(parser_t *parser, expression_t *expression)
{
	expression = comparison(parser, expression);
	move(parser);
	if (match(EQUAL_EQUAL, parser) || match(BANG_EQUAL, parser))
	{
		expression->kind = BINARY;
		memcpy(expression->binary_expr.left, expression, sizeof(token_t));
		memcpy(&expression->binary_expr.operator_token, peek(parser), sizeof(token_t));
		move(parser);
		memcpy(&(expression->binary_expr.right), comparison(parser, expression), sizeof(token_t));
	}
	return expression;
}

void assignment_operation(parser_t *parser)
{

	expression_t *expr = (expression_t *)teriyaki_malloc(sizeof(expression_t));
	expr->kind = ASSIGNMENT;

	// Name
	memset(expr->assignment.name, '\0', 80);
	memcpy(expr->assignment.name, peek(parser)->lexeme, strlen((char *)peek(parser)->lexeme));
	// Consume as
	consume(AS, parser, (uint8_t *)"Expected 'as' token\n");

	(expr->assignment).as = (uint8_t *)malloc(strlen((char *)peek(parser)->lexeme));
	memcpy(expr->assignment.as, peek(parser)->lexeme, strlen((char *)peek(parser)->lexeme));

	consume(BE, parser, (uint8_t *)"Expected 'be' token\n");

	expr->assignment.right = (expression_t *)malloc(sizeof(expression_t));

	memcpy(expr->assignment.right, equality(parser, expr->assignment.right), sizeof(expression_t *));

	printf("value: %s\n", expr->assignment.right->literal_expr.value);
	consume(NEW_LINE, parser, (uint8_t *)"Expected '\\n' token\n");
	add_new_expr(parser, expr);
	return;
}

static void evaluate(parser_t *parser)
{
	if (match(IDENTIFIER, parser))
	{
		assignment_operation(parser);
		return;
	}
	if (match(FUN, parser))
	{
		move(parser);
	}
	if (match(OBJECT, parser))
	{
		move(parser);
	}
	move(parser);
}

void parse(token_t **tokens)
{
	parser_t parser;
	parser.current = 0;
	parser.length_statements = 0;
	parser.tokens = tokens;

	while (!is_at_end(&parser))
	{
		evaluate(&parser);
	}
}

#endif