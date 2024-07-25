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

#define MAX_CMD_LINE_LENGTH 64 /** Maximum number of characters for a single command */

typedef struct _CLI_ CLI;

/**
 * Command function template.
 * \param cli The CLI from which the command was issued
 * \param argc Number of arguments of the command
 * \param argv Arguments of the command
 */
typedef void (*CLI_CommandFunction)(const CLI* cli, const size_t argc, const char* argv[]);

/**
 * The CLI expects to receive data according to this function
 * \param str Buffer where read data need to be placed
 * \param max Maximum number of data bytes the CLI can read/receive
 * \return The number of bytes read
 */
typedef size_t (*CLI_ReadFunction)(char* str, const size_t max);

/**
 * The CLI provide output according to this function
 * \param format The output string, may contain format specifiers
 * \param params The parameters for the format specifiers contained in format
 */
typedef size_t (*CLI_WriteFunction)(const char* format, va_list params);

/**
 * The CLI Command structure.
 * Link a command to a function with a provided help message
 */
typedef struct _CLICommand_
{
	const char*         Command; /** The command which will be used call the function */
	CLI_CommandFunction CmdFunc; /** The function to execute when the command is received */
	const char**        Help;    /** Help information about the command, for example the usage instructions */
} CLICommand;

/**
 * CLI configuration and setup storage.
 */
typedef struct _CLI_
{
	const char*       Prompt;      /** Command line prompt line, written after command execution/waiting for next input */
	const CLICommand* CommandList; /** Command list associated with this command line. Array is terminated with a NULL entry */
	char              WorkingCommand[MAX_CMD_LINE_LENGTH]; /** Stores partial commands not yet ready for execution. */
	CLI_ReadFunction  Read;                                /** The function to use when receiving/reading data */
	CLI_WriteFunction Write;                               /** The function to use to provide sending/writing data */
} CLI;

/**
 * CLI Initialization
 * Populates and initializes a CLI for use
 * \param cli The Command Line Interface to initialize
 * \param prompt The CLI prompt  to use when waiting for new input
 * \param cmdList NULL terminated commands to be available on this interface
 * \param read Function to receive data
 * \param write Function to write data
 */
void CLI_Init(CLI* cli, const char* prompt, const CLICommand* cmdList, const CLI_ReadFunction read, const CLI_WriteFunction write);

/**
 * Processes any data/commands available.
 * Data is read using the provided read function, executing available commands
 * \param cli The CLI's data to receive and commands to process
 */
void CLI_Process(CLI* cli);

/**
 * Executes the provided command.
 * \param cli The CLI that will execute the command
 * \param command The command to execute
 */
void CLI_DoCommand(const CLI* cli, const char* command);

/**
 * Write to the CLI
 * \param cli The interface to write to
 * \param format The string to write, supports format specifiers
 * \return The number of bytes written
 */
size_t CLI_Write(const CLI* cli, const char* format, ...);

/**
 * Read fromm the CLI
 * \param cli The interface to read from
 * \param str Read data storage
 * \param max The maxmimum number of bytes to read
 * \return The number of bytes read
 */
size_t CLI_Read(const CLI* cli, char* str, const size_t max);

/**
 * A CLI help command. It provides help about other available commands.
 * Without arguments it will provide a list of all the available commands the CLI is able to handle.
 * When providing a command as an argument, it's help will be provided.
 * Add it to a command list with a suitable command name to use it.
 * \param cli The CLI interface on which the command was received
 * \param argc The number of arguments passed
 * \param argv The arguments
 */
void CLI_Cmd(const CLI* cli, const size_t argc, const char* argv[]);

/**
 * The help commands help/information.
 * A NULL terminated array with each element written out in a new line
 */
extern const char* CLI_Help[];

#endif
