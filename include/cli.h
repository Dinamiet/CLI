#ifndef _CLI_H_
#define _CLI_H_

/**
 * \file
 * Command Line Interface
 *
 * Provides a command line interface framework for functions to execute with a console like output to display output
 */

#include "ansi_console_codes.h"

#include <stddef.h>
#include <stdint.h>

typedef struct _CLI_ CLI;

typedef void (*CLI_CommandFunction)(CLI* cli, size_t argc, char* argv[]);
typedef size_t (*CLI_ReadFunction)(char* str, size_t max);
typedef size_t (*CLI_WriteFunction)(char* str);

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
	CLI_ReadFunction  Read;
	CLI_WriteFunction Write;
} CLI;

void         CLI_Init(CLI* cli, char* prompt, CLICommand* cmdList, CLI_ReadFunction read, CLI_WriteFunction write);
void         CLI_ProcessCommand(CLI* cli, char* commandLine);
void         CLI_Cmd(CLI* cli, int argc, char* argv[]);
extern char* CLI_Help[];

#endif
