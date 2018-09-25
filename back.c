
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

// The formatter for the remote backup system command
const char* FORMATTER = "scp %s %s@%s:%s";

int main(int argc, char* argv[]){
    char command[1024];
    FILE* fp;
    fp = openConfig();
    
    Config conf = {{0}, {0}, {0}, {0}};
    loadConfig(&conf, fp);

    sprintf(command, FORMATTER, "test.txt", conf.username, conf.hostname, conf.location);
    system(command);
}
