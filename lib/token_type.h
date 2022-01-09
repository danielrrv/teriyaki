
#ifndef __TOKEN_TYPE__
#define __TOKEN_TYPE__
	typedef enum TokenType
	{
		// Single-character tokens.
		IDENTIFIER,
		TAB,
		// SPACE,
		LEFT_PAREN,
		RIGHT_PAREN,
		LEFT_BRACE,
		RIGHT_BRACE,
		COMMA,
		DOT,
		MINUS,
		PLUS,
		COLON,
		SEMICOLON,
		SLASH,
		STAR,
		UNDERSCORE,
		INTERROGATION,
		AMPERSAND,
		NUMERAL,
		NEW_LINE,

		// One or two character tokens.
		BANG,
		BANG_EQUAL,
		EQUAL,
		EQUAL_EQUAL,
		GREATER,
		GREATER_EQUAL,
		LESS,
		LESS_EQUAL,
		PERCENT,
		PIPE,

		// Literals.
		
		STRING,
		NUMBER,
		BOOLEAN,


		// Keywords.
		AND,
		CLASS,
		ELSE,
		FALSE,
		FUN,
		FOR,
		IF,
		NIL,
		OR,
		PRINT,
		RETURN,
		SUPER,
		THIS,
		TRUE,
		VAR,
		WHILE,
		CONST,
		//My reserved words
		BE,
		AS,
		BEING,
		OTHERWISE,
		IN,
		OBJECT,
		MANY,
		OF,
		END,
		END_OF_FILE,

		//Expression
		UNARY,
		BINARY,
		GROUPING,
		ASSIGNMENT
	} TOKEN_TYPE;



void print_token(TOKEN_TYPE token);
#endif /*_TOKEN_TYPE_*/