#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./lib/teriyaki.h"



int main(int argc, char *argv[])
{

	if (1 > argc)
	{
		printf("Usage: Teriyaki [script]\n");
		return 1;
	}
	else if (argc == 2)
	{	uint8_t file[FILE_NAME_SIZE];
		memset(file, '\0', FILE_NAME_SIZE);
		memcpy(file, argv[1], strlen(argv[1]));
		run_file(file);
	}
	else
	{
		run_prompt();
	}
	return 0;
}