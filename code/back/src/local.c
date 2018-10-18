/**
 * file: local.c
 * contributors: Ellis Wright
 * descripttion: This file provides functionality for local file manuptulation
 * and management
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "local.h"
#include "config.h"


/// Defines the command for moving the file to the remote server
const char* FORMATTER = "scp %s %s@%s:%s";
/// Defines the command for moving the file to the remote server
const char* TAR_COMMAND = "tar -cvf %s.tar -T %s/.backup\0";

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
 * Runs a full backup by collecting all the values in the .backup file,
 * placing them in a tar archive, then transferring them to the remote server.
 *
 * parameters:
 *      conf - A pointer to the config file
 *
 * return:
 *      Returns 0 if the operation suceeded 1 if it failed
 */
int run_backup(Config* conf){
    char* backupfile = malloc(strlen(conf->home) + 9);
    strcat(backupfile, conf->home);
    strcat(backupfile, "/.backup");

    //Essentially checks if the .backup file exists so we can print
    //our own error message in stead of tar's
    FILE* backup = fopen(backupfile, "r");
    if (!backup){
        fprintf(stderr, "There was an error finding the .backup file.\n");
        free(backupfile);
        return 1;
    }else{
        fclose(backup);
        free(backupfile);
    }
    
    char command[1024] = {0};

    time_t t = time(0);
    char* date = ctime(&t);

    sprintf(command, TAR_COMMAND, date, conf->home);
    return system(command);      
}

/**
 * Adds the file specified by filename to the .backup file
 *
 * parameters:
 *      filename - The name and FULL PATH of the file to add
 *      conf - A pointer to the config information
 *
 * return:
 *      Returns a 0 if the operation suceeded and 1 if it failed.
 */
int add_file(Config* conf, char* filename){
    //Check to make sure the file actually exists
    FILE* tmp = fopen(filename, "r");
    if (!tmp){
        fprintf(stderr, "Sorry the file %s does not exist.", filename);
        return 1;
    }
    fclose(tmp);

    char* backupfile = malloc(strlen(conf->home) + 9);
    strcat(backupfile, conf->home);
    strcat(backupfile, "/.backup");
    
    FILE* backup = fopen(backupfile, "a");
    if (!backup){
        fprintf(stderr, "There was an issue opening the .backup file");
        free(backupfile);
        return 1;
    }
    
    fputs(filename, backup);
    fclose(backup);

    free(backupfile);
    return 0;
}
