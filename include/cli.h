#ifndef _CLI_H_
#define _CLI_H_

/**
 * \file
 * Command Line Interface
 *
 * Provides a command line interface framework for functions to execute with a console like output to display output
 */

#include "ansi_console_codes.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_CMD_LINE_LENGTH 64

typedef struct _CLI_ CLI;

typedef void (*CLI_CommandFunction)(CLI* cli, size_t argc, char* argv[]);
typedef size_t (*CLI_ReadFunction)(char* str, size_t max);
typedef size_t (*CLI_WriteFunction)(char* format, va_list params);

typedef struct _CLICommand_
{
	char*               Command;
	CLI_CommandFunction CmdFunc;
	char**              Help;
} CLICommand;

typedef struct _CLI_
{
	char*             Prompt;
	CLICommand*       CommandList;
	char              WorkingCommand[MAX_CMD_LINE_LENGTH];
	CLI_ReadFunction  Read;
	CLI_WriteFunction Write;
} CLI;

void         CLI_Init(CLI* cli, char* prompt, CLICommand* cmdList, CLI_ReadFunction read, CLI_WriteFunction write);
void         CLI_Process(CLI* cli);
void         CLI_DoCommand(CLI* cli, char* command);
size_t       CLI_Write(CLI* cli, char* format, ...);
size_t       CLI_Read(CLI* cli, char* str, size_t max);

void         CLI_Cmd(CLI* cli, int argc, char* argv[]);
extern char* CLI_Help[];

#endif
