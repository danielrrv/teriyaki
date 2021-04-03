#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum
{
	OUTSIZE = 1024 * 8,
	BUFFERSIZE = 55

}; //*kb

void runFile(char *source)
{
	char filename[55];
	strncpy(filename, source, 55);
	FILE *file = NULL;

	if (!(file = fopen(filename, "r")))
	{
		fprintf(stderr, "Error to open file %s", filename);
		exit(1);
	};

	char out[OUTSIZE];
	char buffer[BUFFERSIZE];
	do
	{
		fgets(buffer, BUFFERSIZE, file);
		strncat(out, buffer, BUFFERSIZE);
	} while (!feof(file) || ferror(file));
}

void runPrompt()
{
	printf("Teriyaki 1.0.0 | By Daniel Rodriguez\n");
	char in[55];
	while (1)
	{
		printf(">>>");
		fgets(in,BUFFERSIZE,stdin);
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
		runFile(argv[1]);
	}
	else
	{
		runPrompt();
	}
	return 0;
}