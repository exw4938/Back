#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

/// Function for adding a file to be backed up
void addFile(char* filename, Config* conf);
void backupfile(Config* conf, char* filename);

// The formatter for the remote backup system command
const char* FORMATTER = "scp %s %s@%s:%s";

int main(int argc, char* argv[]){
    FILE* fp;
    fp = openConfig();

    Config conf = {{0}, {0}, {0}, {0}};
    loadConfig(&conf, fp);

    fclose(fp);

    if (argc > 2 && !strncmp(argv[1], "-a", 2)){
        addFile(argv[2], &conf);
        return 0;
    }

    backupfile(&conf, "test.txt");
}

/**
 * Adds a file to the main backup list.
 *
 * filename: the name of the file to be added (with filepath)
 * conf: a pointer to the system wide config.
 * NOTE: The reason the config is not a global variable is for readability.
 */
void addFile(char* filename, Config* conf){

    char backupfile[strlen(BACKUP_FILE) + strlen((*conf).homedirectory) + 1];
    for (long unsigned int i = 0; i < sizeof(backupfile); i++)
        backupfile[i] = 0;
    
    
    // The .backup file should be in the user's home directory
    strcat(backupfile, (*conf).homedirectory);
    strcat(backupfile, "/");
    strcat(backupfile, BACKUP_FILE);

    FILE* backup = fopen(backupfile, "a");
    // Check if the .backup file was loaded correctly
    if (!backup){
        fprintf(stderr, 
            "There was an error accessing the .backup file: %s\n", backupfile);
        exit(1);
    }
    
    fprintf(backup, "%s", filename);
    fclose(backup);
}

/**
 * Backs up the file to the remote server using scp.
 *
 * filename: the name of the file to be backed up
 */
void backupfile(Config* conf, char* filename){
    char command[1024];

    sprintf(command, FORMATTER, filename, (*conf).username, (*conf).hostname, (*conf).location);
    system(command);
}
