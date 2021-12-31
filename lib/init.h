#ifndef INIT_H_
#define INIT_H_
#include "lexer.h"



#define FILE_NAME_SIZE 64

void run_prompt();
void run_file(uint8_t *);
uint8_t * read_file(uint8_t *);


void *teriyaki_malloc(size_t size);


#define handle_error(msg)\
    do{perror(msg);} while(0)




void run_prompt()
{
	printf("Teriyaki 1.0.0 | By Daniel Rodriguez\n");
	uint8_t input[80];
	while (1)
	{
		printf(">>> ");
		fgets(input, BUFFERSIZE, stdin);
		printf("%s\n", input);
	}
}

void run_file(uint8_t *source)
{
	uint8_t * out = read_file(source);
	scanner_t *scanner = _scanner(out);
	scan(scanner);
}

uint8_t * read_file(uint8_t * source){
	uint8_t filename[BUFFERSIZE];
	strncpy(filename, source, BUFFERSIZE);
	FILE * file = fopen(filename, "rb");
	if (!file)
	{
		handle_error("No file found.");
		exit(1);
	};

	uint8_t * out = (uint8_t *)teriyaki_malloc(OUTSIZE * sizeof(char));
	memset(out, '\0', OUTSIZE * sizeof(char));
	while (!feof(file) && !ferror(file)){
		uint8_t buffer[BUFFERSIZE];
		fgets(buffer, BUFFERSIZE, file);
		strncat(out, buffer, BUFFERSIZE);
	}
	fclose(file);
	return out;
}

#endif //INIT_H_