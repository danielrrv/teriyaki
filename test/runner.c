#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TESTCASE_token_constructor();
void TESTCASE_read_file(char *);

int main(int argc, char *argv[])
{

	TESTCASE_token_constructor();
	if (argc == 2)
	{
		char filename[55];
		memset(filename, '\0', 55);
		strncpy(filename, argv[1], 55);
		TESTCASE_read_file(filename);
	}

	printf("All test are run successfully!");
	// printf("None is compiling");
	return 0;
}