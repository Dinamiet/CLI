#include "cli.h"

#include <stddef.h>
#include <string.h>

#define MAX_CMD_LINE_LENGTH 64
#define MAX_ARGC			8

void CLI_Init(CLI* cli, CLICommand* cmdList, InterfaceRead readFunc, InterfaceWrite writeFunc)
{
	cli->Commands = cmdList;
	cli->Read	  = readFunc;
	cli->Write	  = writeFunc;
}

void CLI_ProcessCommand(CLI* cli, char* commandLine)
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

			char* backSpace = strchr(cmdBuffer, 0x7F); // Check if backspace in cmd
			while (backSpace && bufferIndex)
			{
				*backSpace = '\0';
				strcpy(backSpace - 1, backSpace + 1);
				numRead--;
				bufferIndex--;
				cli->Write("\b "); // Clear char on interface
				backSpace = strchr(backSpace - 1, 0x7F); // Search for more backspaces
			}

			bufferIndex += numRead;

			char* newLine = strchr(cmdBuffer, '\n');
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
		char*		argv[MAX_ARGC];
		char*		token = NULL;
		const char* split = " ";
		int			argc  = 0;

		token = strtok(commandLine, split);
		while (token != NULL && argc < MAX_ARGC)
		{
			argv[argc++] = token;
			token		 = strtok(NULL, split);
		}

		cli->Write("\n");
		if (argc == 0)
			goto ClearCmdBuffer;

		CLICommand* currentCommand = cli->Commands;
		while (currentCommand->Command)
		{
			if (strncmp(currentCommand->Command, argv[0], strlen(currentCommand->Command)) == 0) // Match
			{
				currentCommand->Callback(cli, argc, argv);
				goto ClearCmdBuffer;
			}
			currentCommand++;
		}

		cli->Write("Command not found: '");
		cli->Write(cmdBuffer);
		cli->Write("'\n");
	ClearCmdBuffer:
		memset(cmdBuffer, 0, sizeof(cmdBuffer)); // clear buffer
		bufferIndex = 0;
	}
	cli->Write("\r>");
	cli->Write(cmdBuffer);
}

void CLI_Cmd(CLI* cli, int argc, char* argv[])
{
	if (argc < 2)
	{
		cli->Write("Available commands:\n");
		CLICommand* currentCommand = cli->Commands;
		while (currentCommand->Command)
		{
			cli->Write("\t");
			cli->Write(currentCommand->Command);
			currentCommand++;
		}
		cli->Write("\n");
		return;
	}

	CLICommand* currentCommand = cli->Commands;
	while (currentCommand->Command)
	{
		if (strncmp(currentCommand->Command, argv[1], strlen(currentCommand->Command)) == 0) // Match
		{
			size_t index= 0;
			while (currentCommand->Help[index] != 0)
			{
				cli->Write(currentCommand->Help[index++]);
				cli->Write("\n");
			}
			return;
		}
		currentCommand++;
	}
}

char* CLI_Help[]=
{
	"Prints available commands",
	"Usage: help [cmd]",
	0
};
