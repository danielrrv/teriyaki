#ifndef EXPRESSION_TERIYAKI
#define EXPRESSION_TERIYAKI

#include "token.h"
#include "token_type.h"

typedef struct _expression_t expression_t; 

typedef struct
{
	expression_t *left;
	expression_t *right;
	token_t operator_token;
} binary_expr_t;

typedef struct
{
	token_t token;
	uint8_t * value;
} literal_expr_t;

typedef struct
{
	expression_t *right;
	token_t operator_token;
} unary_expr_t;

typedef struct
{
	expression_t *expression;
} grouping_expr_t;

typedef struct{
	uint8_t name[80];
	uint8_t * as;
	expression_t * right; 
} assignment_expr_t;

typedef struct _expression_t{
	TOKEN_TYPE kind;
	binary_expr_t binary_expr;
	literal_expr_t literal_expr;
	unary_expr_t unary_expr;
	grouping_expr_t group_expr;
	assignment_expr_t assignment;
} expression_t;


#endif