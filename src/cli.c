#include "cli.h"

#include <stddef.h>
#include <string.h>

#define MAX_CMD_LINE_LENGTH 64
#define MAX_ARGC			8

void CLI_Init(CLI *cli, CLICommand *cmdList, InterfaceRead readFunc, InterfaceWrite writeFunc)
{
	cli->Commands = cmdList;
	cli->Read	  = readFunc;
	cli->Write	  = writeFunc;
}

void CLI_ProcessCommand(CLI *cli, char *commandLine)
{
	static char	  cmdBuffer[MAX_CMD_LINE_LENGTH + 1] = {0}; // add one for '\0'
	static size_t bufferIndex						 = 0;
	if (commandLine == NULL) // No command passed to be processed go and read
	{
		// Ensure there is space in buffer
		if (bufferIndex >= MAX_CMD_LINE_LENGTH)
		{
			cli->Write("Buffer full, executing...\n");
			commandLine = cmdBuffer;
		}
		else
		{
			size_t numRead = cli->Read(&cmdBuffer[bufferIndex], MAX_CMD_LINE_LENGTH - bufferIndex);
			if (numRead == 0)
				return;

			char *newLine = strchr(cmdBuffer, '\n');
			if (newLine != NULL) // check for newline in command
			{
				*newLine	= '\0'; // terminate command;
				commandLine = cmdBuffer;
			}
		}
	}

	// There is something to execute
	if (commandLine != NULL)
	{
		char *		argv[MAX_ARGC];
		char *		token = NULL;
		const char *split = " ";
		int			argc  = 0;

		token = strtok(commandLine, split);
		while (token != NULL && argc < MAX_ARGC)
		{
			argv[argc++] = token;
			token		 = strtok(NULL, split);
		}

		if (argc == 0)
			return;

		CLICommand *currentCommand = cli->Commands;
		while (currentCommand->Command)
		{
			if (strncmp(currentCommand->Command, argv[0], strlen(currentCommand->Command)) == 0) // Match
			{
				currentCommand->Callback(cli, argc, argv);
				memset(cmdBuffer, 0, MAX_CMD_LINE_LENGTH + 1); // clear buffer
				bufferIndex = 0;
				return;
			}
			currentCommand++;
		}

		cli->Write("Command not found\n");
	}
}

void CLI_Cmd(CLI *cli, int argc, char *argv[])
{
	if (argc < 2)
	{
		CLI_Help(cli);
		return;
	}

	CLICommand *currentCommand = cli->Commands;
	while (currentCommand->Command)
	{
		if (strncmp(currentCommand->Command, argv[1], strlen(currentCommand->Command)) == 0) // Match
		{
			currentCommand->HelpCallback(cli);
			return;
		}
		currentCommand++;
	}

	CLI_Help(cli);
}

void CLI_Help(CLI *cli)
{
	cli->Write("\nUsage:\n");
	cli->Write("\thelp [command]\n");
	cli->Write("\nwhere command is one of the following:\n\n");

	CLICommand *currentCommand = cli->Commands;
	while (currentCommand->Command)
	{
		cli->Write("\t");
		cli->Write(currentCommand->Command);
		currentCommand++;
	}
	cli->Write("\n");
}
