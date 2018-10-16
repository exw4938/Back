#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "config.h"
#include "backConfig.h"

//Definitions for argument values
#define GET_FILE 1
#define LIST_FILE 3
#define DATE 5
#define ADD 9

void backupfile(Config* conf, char* filename);
void printusage();
/// Adds all users specified files into a tar file and moves it to the server
int run_backup(Config* conf);
/// Adds the file specified by name to the .backup file
int add_file(Config* conf, char* filename);


// The formatter for the remote backup system command
const char* FORMATTER = "scp %s %s@%s:%s";
const char* TAR_COMMAND = "tar -cvf %s.tar -T %s/.backup\0";

int main(int argc, char* argv[]){
    /// Whether or not a date was specified
    int date_flag = 0;
    /// Whether or not a main command has been processed yet
    int command_flag = 0;

    int opt, arglen, arg_flag;
    // The filename and date to use if they are specified
    char *filename, *date;


    while((opt = getopt(argc, argv, "g:l::a:d:")) != -1){
        switch(opt){
            case 'g':
                arglen = strlen(optarg);
                filename = malloc(sizeof(char) * arglen + 1);
                strncpy(filename, optarg, arglen + 1);
                arg_flag += GET_FILE;
                break;
            case 'l':
                if (optarg != 0){
                    arglen = strlen(optarg);
                    date = malloc(sizeof(char) * arglen + 1);
                    strncpy(date, optarg, arglen + 1);
                    arg_flag += DATE;
                }
                arg_flag += LIST_FILE;
                break;
            case 'a':
                arglen = strlen(optarg);
                filename = malloc(sizeof(char) * arglen + 1);
                strncpy(filename, optarg, arglen + 1);
                arg_flag += ADD;
                break;
            case 'd':
                arglen = strlen(optarg);
                date = malloc(sizeof(char) * arglen + 1);
                strncpy(date, optarg, arglen);
                break;
            default:
                fprintf(stderr, "Invalid arguments: ");
                printusage();
                break;
        }
    }
    
    Config conf = {0};
    loadconfig("config.yaml", &conf);
    int ret_val;
    switch(arg_flag){
        case ADD:
             ret_val = add_file(&conf, filename);
             freeconfig(&conf);
             return ret_val;
    }
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

/**
 * Prints a usage message detailing command line arguments
 */
void printusage(){

}
