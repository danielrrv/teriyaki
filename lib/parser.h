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

static void move(parser_t *parser)
{
	parser->current++;
}

static bool match(TOKEN_TYPE token, parser_t *parser)
{
	return peek(parser)->kind == token;
}

static bool match_and_move(TOKEN_TYPE token, parser_t *parser){
	if(peek(parser)->kind == token) {
		move(parser);
		return true;
	}
	return false;
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


void add_new_expr(parser_t *parser, expression_t *expression)
{
	expression_t **new_ptr = (expression_t **)realloc(parser->statements, sizeof(expression_t) * parser->length_statements + 1);
	parser->length_statements++;
	new_ptr[parser->length_statements - 1] = expression;
	parser->statements = new_ptr;
}

expression_t *primary(parser_t *parser, expression_t *expression)
{
	if (match_and_move(TRUE, parser))
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
	printf("Expected token:%d\n", peek(parser)->kind);
	exit(1);
}
expression_t *unary(parser_t *parser, expression_t *expression)
{
	expression = primary(parser, expression);
	if (match_and_move(BANG, parser) || match(MINUS, parser))
	{
	}
	return expression;
}
expression_t *factor(parser_t *parser, expression_t *expression)
{
	expression = unary(parser, expression);
	if (match_and_move(SLASH, parser) || match_and_move(STAR, parser))
	{
	}
	return expression;
}
expression_t *addition(parser_t *parser, expression_t *expression)
{
	expression = factor(parser, expression);
	if (match_and_move(PLUS, parser) || match(MINUS, parser))
	{
	}
	return expression;
}
expression_t *comparison(parser_t *parser, expression_t *expression)
{
	expression = addition(parser, expression);
	if (match_and_move(LESS, parser) || match(LESS_EQUAL, parser) || match(GREATER_EQUAL, parser) || match(GREATER, parser))
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

	if (match_and_move(EQUAL_EQUAL, parser) || match(BANG_EQUAL, parser))
	{
		expression->kind = BINARY;
		memcpy(expression->binary_expr.left, expression, sizeof(token_t));
		memcpy(&expression->binary_expr.operator_token, peek(parser), sizeof(token_t));
		move(parser);
		memcpy(expression->binary_expr.right, comparison(parser, expression), sizeof(token_t));
	}
	return expression;
}

expression_t *_and(parser_t *parser, expression_t *expression)
{
	expression = equality(parser, expression);
	
	if (match_and_move(AND, parser))
	{
		expression->kind = BINARY;
		memcpy(expression->binary_expr.left, expression, sizeof(token_t));
		memcpy(&expression->binary_expr.operator_token, peek(parser), sizeof(token_t));
		move(parser);
		memcpy(expression->binary_expr.right, equality(parser, expression), sizeof(token_t));
	}
	return expression;
}

expression_t *_or(parser_t *parser, expression_t *expression)
{

	expression = _and(parser, expression);
	if (match_and_move(OR, parser))
	{
		expression->kind = BINARY;
		memcpy(expression->binary_expr.left, expression, sizeof(token_t));
		memcpy(&expression->binary_expr.operator_token, peek(parser), sizeof(token_t));
		move(parser);
		memcpy(expression->binary_expr.right, _and(parser, expression), sizeof(token_t));
	}
	return expression;
}

void assignment_operation(parser_t *parser)
{

	expression_t *expression = (expression_t *)teriyaki_malloc(sizeof(expression_t));
	// Name
	expression->kind = DECLARATION;
	memset(expression->assignment.name, '\0', 80);
	memcpy(expression->assignment.name, peek(parser)->lexeme, strlen((char *)peek(parser)->lexeme));
	consume(AS, parser, (uint8_t *)"Expected 'as' token\n");
	(expression->assignment).as = (uint8_t *)malloc(strlen((char *)peek(parser)->lexeme));
	memcpy(expression->assignment.as, peek(parser)->lexeme, strlen((char *)peek(parser)->lexeme));
	expression->assignment.right = NULL;
	move(parser);
	if (match_and_move(BE, parser))
	{
		expression->kind = ASSIGNMENT;
		expression->assignment.right = (expression_t *)malloc(sizeof(expression_t));
		memset(expression->assignment.right, '\0', sizeof(expression_t));
		memcpy(expression->assignment.right, _or(parser, expression->assignment.right), sizeof(expression_t));
		printf("value: %s\n", expression->assignment.right->literal_expr.value);
		// consume(NEW_LINE, parser, (uint8_t *)"Expected '\\n' token\n");
		// add_new_expr(parser, expression);
		return;
	}
	consume(NEW_LINE, parser, (uint8_t *)"Expected '\\n' token\n");
	add_new_expr(parser, expression);
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
	parser_t parser = {
		.current = 0,
		.length_statements = 0,
	};
	parser.tokens = tokens;
	while (!is_at_end(&parser))
	{
		evaluate(&parser);
	}
}

#endif