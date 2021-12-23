#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
// #include <windows.h>
#include "scanner.h"
#include "init.h"

void *teriyaki_malloc(size_t size);


#define handle_error(msg)\
    do{perror(msg);} while(0)




void run_prompt()
{
	printf("Teriyaki 1.0.0 | By Daniel Rodriguez\n");
	char input[80];
	while (1)
	{
		printf(">>>");
		fgets(input, BUFFERSIZE, stdin);
		printf("%s\n", input);
	}
}

void run_file(char *source)
{
	char * out = read_file(source);
	Scanner *scanner = _scanner(out);
	scan(scanner);
}

static int camili = 0;
char * read_file(char * source){
	char filename[BUFFERSIZE];
	strncpy(filename, source, BUFFERSIZE);
	FILE * file = fopen(filename, "rb");
	if (!file)
	{
		char err[BUFFERSIZE];
		sprintf(err, "Error to open file ");
		sprintf(err + strlen(err), "%s", filename);
		handle_error(err);
		exit(1);
	};

	char * out = (char *)teriyaki_malloc(OUTSIZE * sizeof(char));
	memset(out, '\0', OUTSIZE * sizeof(char));
	while (!feof(file) && !ferror(file)){
		char buffer[BUFFERSIZE];
		fgets(buffer, BUFFERSIZE, file);
		strncat(out, buffer, BUFFERSIZE);
	}
	fclose(file);
	return out;
}