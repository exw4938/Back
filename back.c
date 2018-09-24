
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The formatter for the remote backup system command
const char* FORMATTER = "scp %s %s@%s:%s";

int main(int argc, char* argv[]){
    FILE* fp;
    char username[256];
    char hostname[256];
    char location[256];
    char command[1024];

    for (int i = 0; i < 256; i++){
        username[i] = 0;
        hostname[i] = 0;
        location[i] = 0;
        command[i]  = 0;
    }

    fp = fopen("config.cfg", "r");
    
    fgets(username, 256, fp);
    fgets(hostname, 256, fp);
    fgets(location, 256, fp);

    if (hostname[strlen(hostname) - 1] == '\n')
        hostname[strlen(hostname) - 1] = 0;


    if (location[strlen(location) - 1] == '\n')
        location[strlen(location) - 1] = 0;


    if (username[strlen(username) - 1] == '\n')
        username[strlen(username) - 1] = 0;


    sprintf(command, FORMATTER, "test.txt", username, hostname, location);
    system(command);
}
