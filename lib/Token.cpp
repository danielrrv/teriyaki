#include <iostream>
#include <string>
#include <map>
#include "TokenType.h"

namespace IToken
{
	class Token
	{

	private:
		TokenType m_type;
		std::string m_lexeme,m_literal;
		int m_line;
	public:
		Token(TokenType type, std::string lexeme, std::string literal, int line):
			m_type(type), m_lexeme(lexeme), m_literal(literal), m_line(line){}
		std::string toString(void){return m_lexeme;}
		std::string getLiteral(void){return m_literal;}
		std::string getLexeme(void) const{return m_lexeme;}
	};
} // namespace IToken
