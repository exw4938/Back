#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <string.h>


/// Const representing the name of the config file
const char* CONFIG_FILE = "config.cfg";

/**
 * Opens the (*conf)ig file and validates that it exists.
 * Returns a pointer to the stream that the (*conf)ig can be read from; returns
 * null pointer if file could not be opened.
 */
FILE* openConfig(){
    FILE* fp;
    fp = fopen(CONFIG_FILE, "r");
    if (!fp){
        fprintf(stderr, "There was a problem reading the config file...");
        exit(1);
    }
    return fp;
}

/**
 * Loads the three values (username, hostname, location) from the (*conf)ig files
 * into program memory.
 *
 * (*conf): The (*conf)ig structure to store the (*conf)ig information in
 * fp: The stream to read the file from
 */
void loadConfig(Config* conf, FILE* fp){

    // TODO Add validation that the hostname provided in 'back setup' is valid
    // TODO Add implementation of 'back setup'
    // NOTE This might need generalization in a future iteration
    // Gets the three values from the (*conf)ig
    fgets((*conf).username, 256, fp);
    fgets((*conf).hostname, 256, fp);
    fgets((*conf).location, 256, fp);
    fgets((*conf).homedirectory, 256, fp);

    // Checks if the (*conf)ig file was read in correctly
    if ((*conf).username[0] == 0 || (*conf).hostname[0] == 0 || 
        (*conf).location[0] == 0 || (*conf).homedirectory[0] == 0){
        fprintf(stderr, "There was a problem while reading the file."
            "Run \"back setup\"to (re)(*conf)igure the program\n");
        exit(1);
    }

    // Removes any extraneous new line characters
    if ((*conf).hostname[strlen((*conf).hostname) - 1] == '\n')
        (*conf).hostname[strlen((*conf).hostname) - 1] = 0;
    if ((*conf).location[strlen((*conf).location) - 1] == '\n')
        (*conf).location[strlen((*conf).location) - 1] = 0;
    if ((*conf).username[strlen((*conf).username) - 1] == '\n')
        (*conf).username[strlen((*conf).username) - 1] = 0;
    if ((*conf).homedirectory[strlen((*conf).homedirectory) - 1] == '\n')
        (*conf).homedirectory[strlen((*conf).homedirectory) - 1] = 0;
}
