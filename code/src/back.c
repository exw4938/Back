#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "backConfig.h"

/// Definition for read string when opening a file stream
#define READ   "r"
/// Definition for append string when opening a file stream
#define APPEND "a"
/// Definition for write string when opening a file stream
#define WRITE "w"

void backupfile(Config* conf, char* filename);

// The formatter for the remote backup system command
const char* FORMATTER = "scp %s %s@%s:%s";

int main(int argc, char* argv[]){
    Config conf;
    loadconfig(CONFIG_FILE, &conf);
    updateconfigvalue(g_conf.username, "morpheous");
    saveconfig(&g_conf);
    //printf("%s\n%s\n%s\n%s\n", g_conf.username, g_conf.hostname, g_conf.location, g_conf.home);
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
