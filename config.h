/**
 * file: config.h
 * description: Defines a structure to represent the config data and a function
 * to load the data into memory
 */

/// Structure stores all the information about the config
struct config {
    char username[256];
    char hostname[256];
    char location[256];
    char homedirectory[256];
};

typedef struct config Config;


/// function to load the actual information
void loadConfig(Config* conf, FILE* fp);
/// loads the stream to read the config file from
FILE* openConfig();
