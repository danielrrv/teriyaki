#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TESTCASE_token_constructor();
void TESTCASE_read_file(char *);
void TESTCASE_run_script(char *);

int main(int argc, char *argv[])
{

	TESTCASE_token_constructor();

	// if (argc == 2)
	// {
	// char filename[55];
	// memset(filename, '\0', 55);
	// strncpy(filename, argv[1], 55);

	TESTCASE_read_file("/home/daniel/projects/teriyaki/build/test/example.txt");
	TESTCASE_run_script("/home/daniel/projects/teriyaki/build/test/example.txt");
	// }
	printf("All test are run successfully!\n");
	// printf("None is compiling");
	return 0;
}