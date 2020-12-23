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
		Token(TokenType type, std::string lexeme, std::string literal, int line)
		{
			m_type = type;
			m_literal = literal;
			m_lexeme = lexeme;
			m_line = line;
		}
		std::string toString()
		{
			return m_lexeme;
		}
		std::string getLexeme() const{
			return m_lexeme;
		}
	};
} // namespace IToken
