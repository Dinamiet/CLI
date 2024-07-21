#ifndef __CLI_H__
#define __CLI_H__

#include "ansi_console_codes.h"

#include <stddef.h>
#include <stdint.h>

typedef struct CLICommand CLICommand;

typedef size_t (*InterfaceRead)(char* str, size_t max);
typedef size_t (*InterfaceWrite)(char* str);

typedef struct
{
	CLICommand*    Commands;
	InterfaceRead  Read;
	InterfaceWrite Write;
} CLI;

typedef void (*CmdFunc)(CLI* cli, int argc, char* argv[]);

struct CLICommand
{
	char*   Command;
	CmdFunc Callback;
	char**  Help;
};

void         CLI_Init(CLI* cli, CLICommand* cmdList, InterfaceRead readCallback, InterfaceWrite writeCallback);
void         CLI_ProcessCommand(CLI* cli, char* commandLine);
void         CLI_Cmd(CLI* cli, int argc, char* argv[]);
extern char* CLI_Help[];

#endif
