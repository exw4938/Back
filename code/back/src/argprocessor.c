/**
 * file: argprocessor.c
 * contributors: Ellis Wright
 * description: This file contains functionality for processing and registering
 * commands.
 */

/// This is done so 10 commands can be created before the program needs to 
/// start allocating new space for them
static int maxcommandcount = 10;
static int commandcount = 0;
static Command* commands = calloc(sizeof(Command), 10);

/**
 * This function registers a new command, it will be called from all the files
 * which have command functionality in order to register their commands.
 * This works very similary to the observer pattern, but one sided.
 *
 * parameters:
 *      command - The command to be registered
 */
void registercommand(Command command){
    commandcount++;
    if (commandcount > maxcommandcount){
        commands = realloc(commands, sizeof(Command) * commandcount);
    }
    *(commands + commandcount) = command;
}

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
