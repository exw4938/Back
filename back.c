
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Loads the three values stored in the config into the program
void loadConfig(char username[], char hostname[], char location, FILE* is);
// The formatter for the remote backup system command
const char* FORMATTER = "scp %s %s@%s:%s";

int main(int argc, char* argv[]){
    FILE* fp;
    char username[256];
    char hostname[256];
    char location[256];
    char command[1024];

    // Make sure the four arrays dont contain junk data
    for (int i = 0; i < 256; i++){
        username[i] = 0;
        hostname[i] = 0;
        location[i] = 0;
        command[i]  = 0;
    }

    fp = fopen("config.cfg", "r");
    
    loadConfig(username, hostname, location, fp);


    sprintf(command, FORMATTER, "test.txt", username, hostname, location);
    system(command);
}

/**
 * Loads the three values (username, hostname, location) from the config files
 * into program memory.
 *
 * username: Where to store the username variable
 * hostname: Where to store the hostname variable
 * location: Where to store the location variable
 */
void loadConfig(char username[], char hostname[], char location, FILE* is){
    // TODO Add validation that the hostname provided in 'back setup' is valid
    // TODO Add implementation of 'back setup'
    // NOTE This might need generalization in a future iteration
    // Gets the three values from the config
    fgets(username, 256, fp);
    fgets(hostname, 256, fp);
    fgets(location, 256, fp);

    // Checks if the config file was read in correctly
    if (username[0] == 0 || hostname[0] == 0 || location[0] == 0){
        fprintf(stderr, "There was a problem while reading the file."
            "Run \"back setup\"to (re)configure the program");
        exit(1);
    }

    // Removes any extraneous new line characters
    if (hostname[strlen(hostname) - 1] == '\n')
        hostname[strlen(hostname) - 1] = 0;
    if (location[strlen(location) - 1] == '\n')
        location[strlen(location) - 1] = 0;
    if (username[strlen(username) - 1] == '\n')
        username[strlen(username) - 1] = 0;  
}
