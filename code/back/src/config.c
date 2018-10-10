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
      value = (char*)realloc(value, strlen(newvalue) + 1);
      strcpy(value, newvalue);
      return value;
}

/**
 * Frees all the data allocated for each string in the config file
 *
 * parameters:
 *      conf - The config to free the data for
 */
void freeconfig(Config* conf){
    free(conf->username);
    free(conf->hostname);
    free(conf->location);
    free(conf->home);
}

/**
 * Saves the given config to a file. If the passed config is NULL this function
 * will use the static config initialized in this file. Also free's all of the
 * data in the config structure.
 *
 * parameters:
 *      filename - the name of the file to save the config data to
 *      conf - The config to save to the config.yaml file
 *
 * return:
 *      Returns a 0 on successful operation and 1 on failure
 */
int saveconfig(char* filename, Config* conf){
    FILE* fp = fopen(filename, "w");
    if (!fp){
        fprintf(stderr, "There was an error opening the cofig file.");
        fclose(fp);
        return 1;
    }
    
    //TODO This way of accessing each individual item in the structure seems
    //too restricting. Possibly add element to Config structure with an array
    //of **char pointing to each char*. This would allow for easy iteration
    //through the items in the array, meaning this would be generalized.
    // Put the cofig values in the file
    // TODO add validation that these values are not just a single char or
    // the null string
    fprintf(fp, USERNAME ": %s\n", conf->username);
    fprintf(fp, HOSTNAME ": %s\n", conf->hostname);
    fprintf(fp, LOCATION ": %s\n", conf->location);
    fprintf(fp, HOME ": %s\n", conf->home);

    fclose(fp);
    
    freeconfig(conf);

    return 0;
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
 * Loads the config file and stores it in the given config variable.
 * Dynamically allocates memory for each of the strings in the config struct.
 * Burden of freeing memory falls to calling function.
 * 
 * parameters:
 *      filename - The filepath of the file to load into memory
 *      conf - the config to load the data into
 * return:
 *      Returns a 0 if the operation succeeded and a 1 if it failed
 */
extern int loadconfig(char* filename, Config* conf){
    FILE* fp = fopen(filename, "r");
    if (!fp){
        fprintf(stderr, "There was an error opening the config file: %s.", 
            filename);
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
        errorstate = getconfigvalue(conf, buffer);
    }
    
    fclose(fp);
    
    return errorstate;
}
