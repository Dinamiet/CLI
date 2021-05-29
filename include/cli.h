#ifndef __CLI_H__
#define __CLI_H__

#include <stdint.h>

typedef uint8_t (*ReadCallback)(char *str, uint8_t maxlen);
typedef uint8_t (*WriteCallback)(char *str);

typedef void (*CmdCallback)(int argc, char *argv[]);
typedef void (*CmdHelpCallback)();

typedef struct
{
	char*			Command;
	CmdCallback		Callback;
	CmdHelpCallback HelpCallback;
} CLICommand;

void CLI_Init(CLICommand *cmdList, ReadCallback readCallback, WriteCallback writeCallback);
void CLI_ProcessCommand(char *commandLine);
void CLI_Cmd(int argc, char *argv[]);
void CLI_Help();

#endif
