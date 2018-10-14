#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

static char* testconfigs[] = 
{
    "configs/missing_home.yaml",
    "configs/missing_hostname.yaml",
    "configs/missing_location.yaml",
    "configs/missing_username.yaml",
    "configs/normal.yaml"
};

// This array represents the error state each of the variables shopuld
// be in after reading the corresponding config's in testconfigs.
// the rows are arranged as follows {username, hostname, location, home}
// if the value in the array is 0, the string should have been read in, if
// it is one the string should be NULL
static int values[][4] =
{
    {0, 0, 0, 1},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {1, 0, 0, 0},
    {0, 0, 0, 0}
};

void resetconfig(Config* conf){
    conf->username = 0;
    conf->hostname = 0;
    conf->location = 0;
    conf->home = 0;
}

int test_updateconfigvalue(){
    int ret = 0;
    Config conf = {0, 0, 0, 0};
    loadconfig("configs/normal.yaml", &conf);
    char* newusername = "test_user";
    char* newhostname = "test_host_name";
    char* newlocation = "test_location";
    char* newhome = "test_home";
    
    char* extralongusername = "this is an extra long username to test realloc";
    char* extralonghostname = "this is an extra long hostname to test realloc";
    char* extralonglocation = "this is an extra long location to test realloc";
    char* extralonghome = "this is an extra long home to test realloc";

    conf.username = updateconfigvalue(conf.username, newusername);
    conf.hostname = updateconfigvalue(conf.hostname, newhostname);
    conf.location = updateconfigvalue(conf.location, newlocation);
    conf.home = updateconfigvalue(conf.home, newhome);

    ret += abs(strcmp(conf.username, newusername));
    ret += abs(strcmp(conf.hostname, newhostname));
    ret += abs(strcmp(conf.location, newlocation));
    ret += abs(strcmp(conf.home, newhome));


    conf.username = updateconfigvalue(conf.username, extralongusername);
    conf.hostname = updateconfigvalue(conf.hostname, extralonghostname);
    conf.location = updateconfigvalue(conf.location, extralonglocation);
    conf.home = updateconfigvalue(conf.home, extralonghome);

    ret += abs(strcmp(conf.username, extralongusername));
    ret += abs(strcmp(conf.hostname, extralonghostname));
    ret += abs(strcmp(conf.location, extralonglocation));
    ret += abs(strcmp(conf.home, extralonghome));

    return ret;
}

int test_saveconfig(){
    int ret = 0;
    char* username = malloc(10);
    strcpy(username, "username\0");
    char* hostname = malloc(9);
    strcpy(hostname, "hostname\0");
    char* location = malloc(9);
    strcpy(location, "location\0");
    char* home = malloc(5);
    strcpy(home, "home\0");

    Config conf = {username, hostname, location, home};
    
    saveconfig("test.yaml", &conf);
    resetconfig(&conf);
    loadconfig("test.yaml", &conf);
    
    ret += abs(strcmp(conf.username, "username\0"));
    ret += abs(strcmp(conf.hostname, "hostname\0"));
    ret += abs(strcmp(conf.location, "location\0"));
    ret += abs(strcmp(conf.home, "home\0"));
    return ret;
}

int test_getconfigvalue();

int test_loadconfig(){
    int ret = 0;
    Config conf = {0, 0, 0, 0};

    for (int i = 0; i < (int)(sizeof(testconfigs)/sizeof(char*)); i++){
        ret += loadconfig(testconfigs[i], &conf);
        ret += (!conf.username) == (values[i][0] ? 0 : 1);
        ret += (!conf.hostname) == (values[i][1] ? 0 : 1);
        ret += (!conf.location) == (values[i][2] ? 0 : 1);
        ret += (!conf.home) == (values[i][3] ? 0 : 1);
        resetconfig(&conf);
    }
    return ret;
}

int main(){
    int ret = 0;
    ret += test_loadconfig();
    ret += test_updateconfigvalue();
    ret += test_saveconfig();
    //assert(test_getconfigvalue());
    return ret;
}
