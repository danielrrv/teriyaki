
#ifndef __TOKEN_TYPE__
#define __TOKEN_TYPE__
	typedef enum TokenType
	{
		// Single-character tokens.
		IDENTIFIER,
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
		HUIT,

		// One or two character tokens.
		BANG,
		BANG_EQUAL,
		EQUAL,
		EQUAL_EQUAL,
		GREATER,
		GREATER_EQUAL,
		LESS,
		LESS_EQUAL,

		// Literals.
		
		STRING,
		NUMBER,

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
	} TOKEN_TYPE;


#endif /*_TOKEN_TYPE_*/