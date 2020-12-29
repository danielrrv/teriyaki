#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <regex>

#include "Token.cpp"
#include "TokenType.h"

template <typename T>
void print(T &s)
{
	std::cout << " " << s << '\n';
}
template <typename T>
void print(T &&s)
{
	std::cout << " " << s << '\n';
}

class Scanner
{

private:
	int current = 0;
	int line = 1;
	int column;
	std::string source;
	std::vector<IToken::Token> tokens;
	std::map<std::string, TokenType> keywords = {
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
		std::cout << "-----------" << std::endl;
		for (int i = 0; i < tokens.size(); i++)
		{
			print(tokens[i].getLiteral());
		}
	}
	//TODO:: Call the Destructor.
	Scanner(const std::string &_source) : source(_source) { std::cout << "Object created" << std::endl; }
	~Scanner(){};
	std::vector<IToken::Token> scanTokens()
	{
		while (!isAtEnd())
		{
			char c = charAtCurrent();
			scanToken(c);
		}
		return tokens;
	}
	bool move()
	{
		if (isAtEnd())
		{
			return false;
		}
		current++;
		return true;
	}

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
			addToken(STRING);
			string();
			break;
		default:
			if (isNumber())
			{
				number();
				break;
			}
			else if (isAlpha())
			{
				identifier();
				break;
			}
			else
			{
				std::cerr << "Lines: " << line << ":" << column << "\t"
						  << "Error " << (int)source[current] << ":" << source[current] << ": "
						  << "Unexpected Token" << '\n';
				break;
			}
		}
		move();
	}

	void identifier()
	{
		int start = current;
		std::map<std::string,TokenType>::iterator it;
		while (isAlphaNumeric() && move())
			;
		std::string text = source.substr(start, current - start);
		it = keywords.find(text);
		TokenType type = IDENTIFIER;
		if(it!=keywords.end()){
			type = keywords.at(text);
		}
		addToken(type, text);
	}
	bool isNumber()
	{
		return source[current] >= '0' && source[current] <= '9';
	}
	bool isAlpha()
	{
		return (source[current] >= 'a' && source[current] <= 'z') ||
			   (source[current] >= 'A' && source[current] <= 'Z') ||
			   source[current] == '_';
	}
	bool isAlphaNumeric()
	{
		return isAlpha() || isNumber();
	}
	void number()
	{
		int start = current;
		while (isNumber())
			move();
		if (source[current] == '.' && move())
		{
			while (isNumber() && move())
				;
		}
		std::string value = source.substr(start, (current + 1) - start);
		addToken(NUMBER, value);
	}

	void addToken(TokenType type)
	{
		std::string text = source.substr(current, 1);
		tokens.push_back(IToken::Token(type, text, "", line));
	}

	void addToken(TokenType type, std::string literal)
	{
		std::string text = source.substr(current, 1);
		tokens.push_back(IToken::Token(type, text, literal, line));
	}

	void string()
	{
		int start = current;

		while (source[current] != '"' && move())
		{
			if (source[current] == '\n')
				line++;
		}
		std::string value = source.substr(start, (current + 1) - start);

		addToken(STRING, value);
	}
};