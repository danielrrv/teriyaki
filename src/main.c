#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib/scanner.h"

enum
{
	OUTSIZE = 1024 * 80,
	BUFFERSIZE = 80

}; //*kb

void run_file(char *source)
{
	char filename[BUFFERSIZE];
	strncpy(filename, source, BUFFERSIZE);
	FILE *file = NULL;
	file = fopen(filename, "rb");
	if (!file)
	{
		fprintf(stderr, "Error to open file %s", filename);
		exit(1);
	};

	char out[OUTSIZE];

	while (!feof(file) || ferror(file))
	{
		char buffer[BUFFERSIZE];
		fgets(buffer, BUFFERSIZE, file);
		// printf("%s", buffer);
		strncat(out, buffer, BUFFERSIZE);
	}

	Scanner *scanner = _scanner(out);
	scan(scanner);
	// to_string(scanner);
	fclose(file);
	free(scanner);
}

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

int main(int argc, char *argv[])
{

	if (1 > argc)
	{
		printf("Usage: Teriyaki [script]\n");
		return 1;
	}
	else if (argc == 2)
	{
		run_file(argv[1]);
	}
	else
	{
		run_prompt();
	}
	return 0;
}