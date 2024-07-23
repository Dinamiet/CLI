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

typedef void (*CLI_CommandFunction)(const CLI* cli, const size_t argc, const char* argv[]);
typedef size_t (*CLI_ReadFunction)(char* str, const size_t max);
typedef size_t (*CLI_WriteFunction)(const char* format, const va_list params);

typedef struct _CLICommand_
{
	const char*         Command;
	CLI_CommandFunction CmdFunc;
	const char**        Help;
} CLICommand;

typedef struct _CLI_
{
	const char*       Prompt;
	const CLICommand* CommandList;
	char              WorkingCommand[MAX_CMD_LINE_LENGTH];
	CLI_ReadFunction  Read;
	CLI_WriteFunction Write;
} CLI;

void   CLI_Init(CLI* cli, const char* prompt, const CLICommand* cmdList, const CLI_ReadFunction read, const CLI_WriteFunction write);
void   CLI_Process(CLI* cli);
void   CLI_DoCommand(const CLI* cli, const char* command);
size_t CLI_Write(const CLI* cli, const char* format, ...);
size_t CLI_Read(const CLI* cli, char* str, const size_t max);

void               CLI_Cmd(const CLI* cli, const size_t argc, const char* argv[]);
extern const char* CLI_Help[];

#endif
