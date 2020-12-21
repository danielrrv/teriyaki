#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include "Token.cpp"
#include "TokenType.h"



class Scanner
{

private:
	int start = 0;
  	int current = 0;
  	int line = 1;
	std::string source;
	std::vector<IToken::Token> tokens;
protected:
  bool isAtEnd() {
    return current >= source.length();
  }
public:
	//TODO:: Call the Destructor.
	Scanner(std::string _source):source(_source){std::cout<<"Object created"<<std::endl;}
	~Scanner(){};
	std::vector<IToken::Token> scanTokens(){
		while (!isAtEnd()) {
      		// We are at the beginning of the next lexeme.
      		start = current;
			
      		scanToken();
    	}
		for (int i=0; i< source.length();i++){
			std::cout<<tokens[i].toString()<<std::endl;
		}
		return tokens;
	}
	char advance() {
    	current++;
		
	if(source[current]=='\n')line++;
    	return source[current - 1];
  	}
  	void scanToken() {
    	char c = advance();
    	switch (c) {
      		case '(': addToken(LEFT_PAREN); break;
      		case ')': addToken(RIGHT_PAREN); break;
      		case '{': addToken(LEFT_BRACE); break;
      		case '}': addToken(RIGHT_BRACE); break;
      		case ',': addToken(COMMA); break;
      		case '.': addToken(DOT); break;
      		case '-': addToken(MINUS); break;
      		case '+': addToken(PLUS); break;
      		case ';': addToken(SEMICOLON); break;
      		case '*': addToken(STAR); break; 
    	}
  	}

	void addToken(TokenType type) {
    	std::string text = source.substr(start, current);
    	tokens.push_back(IToken::Token(type, text, line));
  	}
};