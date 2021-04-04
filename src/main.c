#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/init.h"







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