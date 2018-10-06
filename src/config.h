/**
 * file: config.h
 * description: Defines a structure to represent the config data and a function
 * to load the data into memory
 * contributors: Ellis Wright
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

/// Const representing the name of the config file
#define CONFIG_FILE  "config.cfg"
#define BACKUP_FILE  ".backup"

/// Structure stores all the information about the config
struct config {
    // The username to use when accessing the server
    char* username;
    // The hostname of the server
    char* hostname;
    // The directory to store fils on in the server
    char* location;
    // The filepath of the home directory of the current user
    char* home;
};

typedef struct config Config;

// A version of the config
static Config conf;

/**
 * Loads the config file and stores it in the static config variable.
 * Dynamically allocates memory for each of the strings in the config struct.
 *
 * return:
 *      Returns a 0 if the operation succeeded and a 1 if it failed
 */
int loadconfig();

/**
 * Updates one of the values in the config. This includes reallocating
 * its data.
 *
 * parameters:
 *      value - A pointer to the config value to be changed. NOTE: This
 *      function uses realloc so this pointer's integrity is not garunteed
 *      after the function has run. Use the return value as the new value for
 *      that pointer
 *
 *      newvalue - The value to update the current config value with
 *
 * return:
 *      Returns a pointer to an area in memory containing the new value
 */
char* updateconfigvalue(char* value, const char* newvalue);

/**
 * Saves the given config to a file. If the passed config is NULL this function
 * will use the static config initialized in this file. Also free's all of the
 * data in the config structure.
 *
 * parameters:
 *      conf - The config to save to the config.cfg file
 *
 * return:
 *      Returns a 0 on successful operation and 1 on failure
 */
int saveconfig(Config* conf);

#endif
