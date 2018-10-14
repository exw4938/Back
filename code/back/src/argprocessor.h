/**
 * file: argprocessor.h
 * contributors: Ellis Wright
 * description: Functions and structure for the command processing
 * module
 */

#ifndef _ARGPROCESSOR_H_
#define _ARGPROCESSOR_H_
/**
 * Structure represents one command which has the functionality contained
 * in the pointer to function. This pointer can be null, which represents
 * a precursor command which has children but no functionality itself
 */
struct command{
    void (*function)(char*, char*);
    struct command** commands;
    char* name;
}

/// Redefine the struct command type
typedef struct command Command;


/**
 * This function registers a new command, it will be called from all the files
 * which have command functionality in order to register their commands.
 * This works very similary to the observer pattern, but one sided.
 *
 * parameters:
 *      command - The command to be registered
 */
void registercommand(Command command);

/**
 * This function parses the actual command line arguments and calls the
 * functions they specify.
 *
 * parameters:
 *      argc - The length of the args array
 *      args - The list of command line arguments
 *
 * return:
 *      Return 0 if the operation suceeded and 1 if it failed
 */
int parsecommand(int argc, char* args[]);

#endif
