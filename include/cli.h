#ifndef __CLI_H__
#define __CLI_H__

#include <stddef.h>
#include <stdint.h>

typedef struct CLICommand CLICommand;

typedef size_t (*InterfaceRead)(char* str, size_t max);
typedef size_t (*InterfaceWrite)(char* str);

typedef struct
{
	CLICommand*	   Commands;
	InterfaceRead  Read;
	InterfaceWrite Write;
} CLI;

typedef void (*CmdFunc)(CLI* cli, int argc, char* argv[]);
typedef void (*CmdHelpFunc)(CLI* cli);

struct CLICommand
{
	char*		Command;
	CmdFunc		Callback;
	CmdHelpFunc HelpCallback;
};

void CLI_Init(CLI* cli, CLICommand* cmdList, InterfaceRead readCallback, InterfaceWrite writeCallback);
void CLI_ProcessCommand(CLI* cli, char* commandLine);
void CLI_Cmd(CLI* cli, int argc, char* argv[]);
void CLI_Help(CLI* cli);

#endif
