#include "cli.h"

#include <stddef.h>
#include <string.h>

#define MAX_CMD_LINE_LENGTH 64
#define MAX_ARGC 8

CLICommand *  cliCmdList	   = NULL;
ReadCallback  cliReadCallback  = NULL;
WriteCallback cliWriteCallback = NULL;

void CLI_Init(CLICommand *cmdList, ReadCallback readCallback, WriteCallback writeCallback)
{
	cliCmdList		 = cmdList;
	cliReadCallback	 = readCallback;
	cliWriteCallback = writeCallback;
}

void CLI_ProcessCommand(char *commandLine)
{
	static char		cmdBuffer[MAX_CMD_LINE_LENGTH + 1]; // add one for 0
	static uint32_t bufferIndex = 0;
	if (commandLine == NULL) // No command passed to be processed go and read
	{
		// Ensure there is space in buffer
		if (bufferIndex >= MAX_CMD_LINE_LENGTH)
		{
			cliWriteCallback("Buffer full, executing...\n");
			commandLine = cmdBuffer;
		}
		else
		{
			uint8_t numRead = cliReadCallback(&cmdBuffer[bufferIndex], MAX_CMD_LINE_LENGTH - bufferIndex);
			bufferIndex += numRead;
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

		CLICommand *currentCommand = cliCmdList;
		while (currentCommand->Command)
		{
			if (strncmp(currentCommand->Command, argv[0], strlen(currentCommand->Command)) == 0) // Match
			{
				currentCommand->Callback(argc, argv);
				memset(cmdBuffer, 0, MAX_CMD_LINE_LENGTH + 1); // clear buffer
				bufferIndex = 0;
				return;
			}
			currentCommand++;
		}

		cliWriteCallback("Command not found\n");
	}
}

void CLI_Cmd(int argc, char *argv[])
{
	if (argc < 2)
	{
		CLI_Help();
		return;
	}

	CLICommand *currentCommand = cliCmdList;
	while (currentCommand->Command)
	{
		if (strncmp(currentCommand->Command, argv[1], strlen(currentCommand->Command)) == 0) // Match
		{
			currentCommand->HelpCallback();
			return;
		}
		currentCommand++;
	}

	CLI_Help();
}

void CLI_Help()
{
	cliWriteCallback("\nUsage:\n");
	cliWriteCallback("\thelp [command]\n");
	cliWriteCallback("\nwhere command is one of the following:\n\n");

	CLICommand *currentCommand = cliCmdList;
	while (currentCommand->Command)
	{
		cliWriteCallback("\t");
		cliWriteCallback(currentCommand->Command);
		currentCommand++;
	}
	cliWriteCallback("\n");
}
