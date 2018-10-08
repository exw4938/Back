#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <string.h>


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
char* updateconfigvalue(char* value, const char* newvalue){


}

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
int saveconfig(Config* conf){


}

/**
 * Helper function for loadconfig, takes a line of input read from the
 * config.yaml file and sets the value of the passed conf object to the
 * value specified by the file. Also allocates memory for the config value.
 *
 * parameters:
 *      conf: A pointer to the config to return a pointer to
 *      inputline: The line to process for config values
 *
 * return:
 *      Returns a 0 if the operation succeeded and 1 if it failed
 */
int getconfigvalue(Config* conf, char* inputline){
    char* token = strtok(inputline, ":");

    // Get the token's corresponding value and remove leading whitespace
    char* value = strtok(NULL, "\0");
    while (value[0] == ' ')
        value++;

    int tokenlen = strlen(token);

    // Checks which of the config values the line specifies
    if (!strncmp(token, USERNAME, tokenlen)){

        conf->username = (char*)malloc(strlen(value) + 1);
        strcpy(conf->username, value);
        return 0;

    }else if (!strncmp(token, HOSTNAME, tokenlen)){

        conf->hostname = malloc(strlen(value) + 1);
        strcpy(conf->hostname, value);
        return 0;

    }else if (!strncmp(token, LOCATION, tokenlen)){

        conf->location = malloc(strlen(value) + 1);
        strcpy(conf->location, value);
        return 0;

    }else if (!strncmp(token, HOME, tokenlen)){

        conf->home = malloc(strlen(value) + 1);
        strcpy(conf->home, value);
        return 0;

    }else{

        fprintf(stderr, "There was an error reading the config file. Invalid"
            " config value: %s", inputline);
        return 1;

    }
    
}

/**
 * Loads the config file and stores it in the static config variable.
 * Dynamically allocates memory for each of the strings in the config struct.
 * Burden of freeing memory falls to calling function.
 *
 * return:
 *      Returns a 0 if the operation succeeded and a 1 if it failed
 */
int loadconfig(){
    FILE* fp;
    fp = fopen(CONFIG_FILE, "r");
    if (!fp){
        fprintf(stderr, "There was an error opening the cofig file.");
        fclose(fp);
        return 1;
    }

    char buffer[1024] = {0};
    int bufferlen, errorstate = 0;

    // Gets the values from the config
    while (fgets(buffer, 1024, fp) && !errorstate){
        bufferlen = strlen(buffer);
        if (buffer[bufferlen - 1] == '\n'){
            buffer[bufferlen - 1] = '\0';
        }
        errorstate = getconfigvalue(&g_conf, buffer);
    }
    
    fclose(fp);
    
    printf("%s\n%s\n%s\n%s\n", g_conf.username, g_conf.hostname, g_conf.location, g_conf.home);
    return errorstate;
}
