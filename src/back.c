#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

/// Definition for read string when opening a file stream
#define READ   "r"
/// Definition for append string when opening a file stream
#define APPEND "a"
/// Definition for write string when opening a file stream
#define WRITE "w"

/// Function for adding a file to be backed up
void addfile(char* filename, Config* conf);
void backupfile(Config* conf, char* filename);
/// Loads the .backup file and returns a pointer to the stream
static FILE* loadbackup(FILE* backup, Config* conf, char* mode);
/// Creates a temp tar file to store files specified in .backup
int createtar(Config* conf);

// The formatter for the remote backup system command
const char* FORMATTER = "scp %s %s@%s:%s";

int main(int argc, char* argv[]){
    FILE* fp;
    fp = openConfig();

    Config conf = {{0}, {0}, {0}, {0}};
    loadConfig(&conf, fp);

    fclose(fp);

    if (argc > 2 && !strncmp(argv[1], "-a", 2)){
        addfile(argv[2], &conf);
        return 0;
    }

    backupfile(&conf, "test.txt");
}

/**
 * Loads the .backup file and returns a pointer to the file stream
 *
 * backup: the file stream to set equal to use
 * conf: A pointer to the system wide config
 * mode: the mode to read the .backup file in (APPEND, READ, WRITE)
 *
 * return: a pointer to the file stream of the .backup file
 */
static FILE* loadbackup(FILE* backup, Config* conf, char* mode){
    char* backupfile = calloc(
        strlen(BACKUP_FILE) + strlen(conf->homedirectory) + 1, sizeof(char));
    
    // The .backup file should be in the user's home directory
    strcat(backupfile, conf->homedirectory);
    strcat(backupfile, "/");
    strcat(backupfile, BACKUP_FILE);

    backup = fopen(backupfile, mode);

    free(backupfile);

    return backup;
}

/**
 * Adds a file to the main backup list.
 *
 * filename: the name of the file to be added (with filepath)
 * conf: a pointer to the system wide config.
 * NOTE: The reason the config is not a global variable is for readability.
 */
void addfile(char* filename, Config* conf){
    FILE* backup;

    backup = loadbackup(backup, conf, APPEND);

    // Check if the .backup file was loaded correctly
    if (!backup){
        fprintf(stderr, 
            "There was an error accessing the .backup file... \n");
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

    sprintf(command, FORMATTER, filename, conf->username, conf->hostname, conf->location);
    system(command);
}

/**
 * Creates a temporary tar archive in the user's home folder.
 *
 * conf: A pointer to the system wide config
 *
 * return: a 0 on success and 1 on failure
 */
int createtar(Config* conf){
         
}
