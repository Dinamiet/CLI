#ifndef __CLI_H__
#define __CLI_H__

#define MAX_CMD_NAME_LENGTH 16
#define MAX_CMD_LINE_LENGTH 32

typedef char (*ReadCallback)();

typedef void (*CmdCallback)(char *args);
typedef void (*CmdHelpCallback)();

typedef struct
{
	char Command[MAX_CMD_NAME_LENGTH];
	CmdCallback Callback;
	CmdHelpCallback HelpCallback;
} CLICommand;

void CLI_Init(CLICommand *cmdList, ReadCallback readCallback);
void CLI_ProcessCommand(char* commandLine);

#endif
