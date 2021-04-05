#include <stdio.h>
#include <stdlib.h>
// #include <windows.h>
#include "scanner.h"
#include "init.h"

void *Teriyaki_malloc(size_t size);
enum
{
	OUTSIZE = 1024 * 80,
	BUFFERSIZE = 80

}; //*kb


void run_prompt()
{
	printf("Teriyaki 1.0.0 | By Daniel Rodriguez\n");
	char in[55];
	while (1)
	{
		printf(">>>");
		fgets(in, BUFFERSIZE, stdin);
		printf("%s\n", in);
	}
}

void run_file(char *source)
{
	char * out = read_file(source);
	Scanner *scanner = _scanner(out);
	scan(scanner);
	// to_string(scanner);
	free(scanner);
}


char * read_file(char * source){
	char filename[BUFFERSIZE];
	strncpy(filename, source, BUFFERSIZE);
	FILE *file = fopen(filename, "rb");
	if (!file)
	{
		fprintf(stderr, "Error to open file %s", filename);
		exit(1);
	};

	char * out = (char *)Teriyaki_malloc(OUTSIZE * sizeof(char));
	while (!feof(file) && !ferror(file)){
		char buffer[BUFFERSIZE];
		fgets(buffer, BUFFERSIZE, file);
		strncat(out, buffer, BUFFERSIZE);
	}
	fclose(file);
	return out;
}