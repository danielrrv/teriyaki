#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include "TeriyakiConfig.h"
#include "lib/Scanner.cpp"

#define BUFFERSIZE 1024 * 10

template <typename T>
struct printer
{
  void operator()(T &s)
  {
    std::cout << s << std::endl;
  }
};


inline void runFile(std::string path)
{
  std::ifstream file(path, std::ifstream::in);
  char buffer[BUFFERSIZE];
  do
  {

    file.read(buffer, BUFFERSIZE);
    if (file.gcount() > 0)
    {
      Scanner scanner(buffer);
      scanner.scanTokens();
      scanner.toString();
    }
  } while (!file.eof() && !file.fail());
}
inline void runPrompt()
{
  std::cout << "Teriyaki 1.0.0 | By Daniel Rodriguez\n";
  char line[BUFFERSIZE];
  for (;;)
  {
    std::cout << ">>> ";
    std::cin >> line;
    if (1 > strlen(line))
      std::exit(0);
    std::cout << line << std::endl;
  }
}

inline void report(int line, std::string where, std::string message)
{
  std::cerr << "[line " << line << "] Error at " << where << ": " << message << std::endl;
}

inline void error(int line, std::string message)
{
  report(line, "", message);
}

int main(int argc, char *argv[])
{

  if (1 > argc)
  {
    std::cout << "Usage: Teriyaki [script]" << '\n';
    return 1;
  }
  else if (argc == 2)
  {
    runFile(argv[1]);
  }
  else
  {
    runPrompt();
  }
  return 0;
}