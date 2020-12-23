#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <regex>
#include "Token.cpp"
#include "TokenType.h"

class Scanner
{

private:

	int current = 0;
	int line = 1;
	int column;
	std::string source;
	std::vector<IToken::Token> tokens;

protected:
	bool isAtEnd()
	{
		return current >= source.length();
	}

public:
	void toString()
	{
		for (int i = 0; i < tokens.size(); i++)
		{
			std::cout << "Token: " << tokens[i].getLexeme() << "\n";
		}
	}
	//TODO:: Call the Destructor.
	Scanner(const std::string& _source) : source(_source) { std::cout << "Object created" << std::endl; }
	~Scanner(){};
	std::vector<IToken::Token> scanTokens()
	{
		while (!isAtEnd())
		{
			// We are at the beginning of the next lexeme.
		
		
		
			char c = charAtCurrent();
			scanToken(c);
			//current++;
		}

		return tokens;
	}
	void move(){;current ++;}

	char charAtCurrent()
	{
		column++;
		return source[current];
	}
	void scanToken(const char &c)
	{
		
		switch (c)
		{
		case '(':
			addToken(LEFT_PAREN);
			break;
		case ')':
			addToken(RIGHT_PAREN);
			break;
		case '{':
			addToken(LEFT_BRACE);
			break;
		case '}':
			addToken(RIGHT_BRACE);
			break;
		case ',':
			addToken(COMMA);
			break;
		case '.':
			addToken(DOT);
			break;
		case '-':
			addToken(MINUS);
			break;
		case '+':
			addToken(PLUS);
			break;
		case ';':
			addToken(SEMICOLON);
			break;
		case ':':
			addToken(COLON);
			break;
		case '*':
			addToken(STAR);
			break;
		case '!':
			addToken(c == '=' ? BANG_EQUAL : BANG);
			break;
		case '=':
			addToken(c == '=' ? EQUAL_EQUAL : EQUAL);
			break;
		case '<':
			addToken(c == '=' ? LESS_EQUAL : LESS);
			break;
		case '>':
			addToken(c == '=' ? GREATER_EQUAL : GREATER);
			break;
		case '/':
			if (c == '/')
			{
				// A comment goes until the end of the line.
				while (source[current] != '\n' && !isAtEnd())
					move();
			}
			else
			{
				addToken(SLASH);
			}
			break;
		case ' ':
		case '\r':
		case '\t':
			// Ignore whitespace.
			break;
		case '\n':
			line++;
			column = 0;
			break;
		case '"':
			string();
			break;
		default:
			std::cerr << "Lines: " << line << ":" << column << "\t"
					  << "Error " << (int)source[current] << ":" << source[current] << ": "
					  << "Unexpected Token" << '\n';
			break;
		}
		 move();
	}

	void addToken(TokenType type)
	{
		std::string text = source.substr(current,1);
		tokens.push_back(IToken::Token(type, text, "", line));
	}

	void addToken(TokenType type, std::string literal)
	{
		std::string text = source.substr(current,1);
		tokens.push_back(IToken::Token(type, text, literal, line));
	}

	void string()
	{
		int start = current;
		//printf(start);
		move();
		while (source[current] != '"' && !isAtEnd())
		{
			if (source[current] == '\n')line++;
			

			if (isAtEnd())
			{
				std::cerr << line << ":" << current << '\t' << "Error " << source[current] << ": "
						  << "Unexpected Token" << std::endl;
				return;
			}

			// The closing ".
			move();

			// Trim the surrounding quotes.
			//std::string value = "sdasd";
		}
			std::string value = source.substr(start, (current+1) - start);	
			addToken(STRING, value);
	}
};