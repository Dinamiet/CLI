#include "cli.h"

#include <stdio.h>
#include <string.h>

void testing(int argc, char *argv[])
{
	if (argc == 1)
	{
		printf("Compile Date: %s - %s\n", __TIME__, __DATE__);
		return;
	}
	for (int i = 0; i < argc; i++) { printf("argv[%d]: %s\n", i, argv[i]); }
}

void testingHelp() { printf("\n\nHelp of testing command\n\n"); }

CLICommand commands[] = {{"help", CLI_Cmd, CLI_Help}, {"testing", testing, testingHelp}, {0, 0, 0}};

uint8_t readData(char *str, uint8_t maxLength)
{
	fgets(str, maxLength, stdin);
	uint8_t len = (uint8_t)strlen(str);
	if (len >= 6)
		str[len++] = '\n';
	return len;
}

uint8_t writeData(char *str) { return printf("%s", str); }

int main()
{
	CLI_Init(commands, readData, writeData);

	CLI_ProcessCommand("help");

	CLI_ProcessCommand(NULL);

	return 0;
}
