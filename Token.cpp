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
		std::string m_lexeme;
		struct literal;
		int m_line;
	public:
		
		Token(TokenType type, std::string lexeme, int line)
		{
			m_type = type;
			m_lexeme = lexeme;
			m_line = line;
		}
		std::string toString()
		{
			return m_type;
		}
	};
} // namespace IToken
