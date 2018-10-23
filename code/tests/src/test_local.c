/**
 * Tests for the local.c file
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "local.h"
#include "config.h"
static char* config = "configs/test_local_config.yaml";

static const int test_files_num = 2;
static char* test_files[2] = {
    "test_files/test1.c",
    "test_files/test2.zip"
};

/**
 * Tests if files are added to the .backup file properly
 * 
 * Adds strings to a psudo .backup file stored in the testing directory
 * and does comparisons
 *
 * return:
 *      Returns a 0 if the test passed 1 if it failed
 */
int test_add_file(){
    int ret = 0;
    Config conf;
    loadconfig(config, &conf);

    for(int i = 0; i < test_files_num; i++){
           ret += add_file(&conf, test_files[i]);
    }
    
    FILE* file = fopen(".backup", "r");
    char buffer[256];

    fgets(buffer, 256, file);
    buffer[strlen(buffer) - 1] = '\0';

    ret += abs(strcmp(buffer, test_files[0]));

    fgets(buffer, 256, file);
    buffer[strlen(buffer) - 1] = '\0';
    ret += abs(strcmp(buffer, test_files[1]));

    fclose(file);
    return ret;
}

int test_run_backup();

int test_backupfile();

int main(){
    int ret = 0;
    ret += test_add_file();
    return ret;
}
