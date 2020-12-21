#include <iostream>
#include <string>
#include <fstream>
#include<cstring>
#include "TeriyakiConfig.h"
#include "Scanner.cpp"



#define BUFFERSIZE 1024*10

inline void runFile(std::string path){
  std::ifstream file(path , std::ifstream::in);
  char buffer[BUFFERSIZE];
  do{
    
    file.read(buffer, BUFFERSIZE);
    if(file.gcount() > 0){
      Scanner scanner(buffer);
      scanner.scanTokens();
    }
  } while(!file.eof()&&!file.fail());
}
inline void runPrompt(){
  std::cout<<"Teriyaki 1.0.0 | By Daniel Rodriguez\n";
  char line[BUFFERSIZE];
  for(;;){
    std::cout<<">>> ";
    std::cin >> line;
    if(1 > strlen(line))std::exit(0);
    std::cout<<line<<std::endl;
  }
}

int main(int argc, char* argv[]){

  if (1 > argc) {
      std::cout<<"Usage: Teriyaki [script]"<<'\n';
      return 1; 
    } else if (argc == 2) {
      runFile(argv[1]);
    } else {
      runPrompt();
    }
	return 0;
}