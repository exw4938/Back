#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "config.h"
#include "local.h"
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
 * Prints a usage message detailing command line arguments
 */
void printusage(){
    puts("Usage: back" 
    "[-g filename] [-a filename] [-l [filename]] [-d date]\n"
    "-g\tGets the file specified by filename from the remote server\n"
    "-a\tAdds the file specified by filename to the backup list\n"
    "-l\tLists all the files in the archive specified by filename\n"
    "-d\tChanges the [gl] args to get use the archive specified by date\n"
    "\tinstead of the most recent one");
}
