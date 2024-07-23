#include "cli.h"

#include <stdbool.h>
#include <string.h>

#define MAX_ARGC            8

void CLI_Init(CLI* cli, const char* prompt, const CLICommand* cmdList, const CLI_ReadFunction read, const CLI_WriteFunction write)
{
	cli->Prompt      = prompt;
	cli->CommandList = cmdList;
	cli->Read        = read;
	cli->Write       = write;
}

void CLI_Process(CLI* cli)
{
	bool   haveCommand   = false;
	size_t commandLength = strlen(cli->WorkingCommand);

	if (commandLength >= MAX_CMD_LINE_LENGTH)
	{
		CLI_Write(cli, LF "Buffer full, executing..." LF);
		haveCommand = true;
	}
	else
	{
		size_t numRead = cli->Read(&cli->WorkingCommand[commandLength], MAX_CMD_LINE_LENGTH - commandLength);

		if (numRead == 0) // Nothing new available
			return;

		// Handle backspace
		char* backSpace = strchr(cli->WorkingCommand, '\b');
		while (backSpace)
		{
			*backSpace     = '\0';
			uint8_t offset = cli->WorkingCommand[0] == '\0' ? 0 : 1;
			strcpy(backSpace - offset, backSpace + 1);
			backSpace = strchr(backSpace - offset, '\b');
		}

		// Find command end
		char* newLine = strchr(cli->WorkingCommand, '\n');
		if (newLine)
		{
			*newLine    = '\0';
			haveCommand = true;
		}
	}

	if (haveCommand)
	{
		CLI_DoCommand(cli, cli->WorkingCommand);
		memset(cli->WorkingCommand, 0, MAX_CMD_LINE_LENGTH);
	}
	else
	{
		CLI_Write(cli, CR EL_ "%s%s", cli->Prompt, cli->WorkingCommand);
	}
}

void CLI_DoCommand(const CLI* cli, const char* command)
{
	char cmd[MAX_CMD_LINE_LENGTH + 1];
	if (!command)
		return;

	strncpy(cmd, command, MAX_CMD_LINE_LENGTH);

	const char* argv[MAX_ARGC];
	char*       token = NULL;
	const char* split = " ";
	size_t      argc  = 0;

	// Tokenize command
	token = strtok(cmd, split);
	while (token && argc < MAX_ARGC)
	{
		argv[argc++] = token;
		token        = strtok(NULL, split);
	}

	CLI_Write(cli, LF);
	if (argc == 0) // Empty command
		goto do_command_done;

	const CLICommand* currentCommand = cli->CommandList;
	while (currentCommand->Command)
	{
		if (strcmp(currentCommand->Command, argv[0]) == 0) // Match
		{
			currentCommand->CmdFunc(cli, argc, argv); // Call command
			goto do_command_done;
		}
		currentCommand++;
	}

	CLI_Write(cli, "Command not found: '%s'" LF, argv[0]);
do_command_done:
	CLI_Write(cli, CR "%s", cli->Prompt);
}

size_t CLI_Write(const CLI* cli, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	size_t written = cli->Write(format, args);
	va_end(args);
	return written;
}

size_t CLI_Read(const CLI* cli, char* str, const size_t max) { return cli->Read(str, max); }

void CLI_Cmd(const CLI* cli, const size_t argc, const char* argv[])
{
	const CLICommand* currentCommand = cli->CommandList;
	// When no args are provided with command - just list all commands
	if (argc < 2)
	{
		CLI_Write(cli, "Available commands:");
		size_t      index          = 0;
		while (currentCommand->Command)
		{
			CLI_Write(cli, (index++ % 4) ? HT "%s" : LF HT "%s", currentCommand->Command);
			currentCommand++;
		}
		CLI_Write(cli, LF);
		return;
	}

	// Print help for specific command
	while (currentCommand->Command)
	{
		if (strcmp(currentCommand->Command, argv[1]) == 0) // Match
		{
			size_t index = 0;
			while (currentCommand->Help[index] != 0) { CLI_Write(cli, "%s" LF, currentCommand->Help[index++]); }
			return;
		}
		currentCommand++;
	}
}

const char* CLI_Help[] = {
		"Prints available commands",
		"Usage: help [cmd]",
		0,
};
