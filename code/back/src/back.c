#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "config.h"
#include "backConfig.h"

//Definitions for argument values
#define GET_FILE 1
#define LIST_FILE 3
#define DATE 5
#define ADD 9

void backupfile(Config* conf, char* filename);
void printusage();

// The formatter for the remote backup system command
const char* FORMATTER = "scp %s %s@%s:%s";

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
 * Prints a usage message detailing command line arguments
 */
void printusage(){

}
