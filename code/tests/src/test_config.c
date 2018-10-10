#include <assert.h>
#include <stdio.h>
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

    assert(!strcmp(conf.username, newusername));
    assert(!strcmp(conf.hostname, newhostname));
    assert(!strcmp(conf.location, newlocation));
    assert(!strcmp(conf.home, newhome));


    conf.username = updateconfigvalue(conf.username, extralongusername);
    conf.hostname = updateconfigvalue(conf.hostname, extralonghostname);
    conf.location = updateconfigvalue(conf.location, extralonglocation);
    conf.home = updateconfigvalue(conf.home, extralonghome);

    assert(!strcmp(conf.username, extralongusername));
    assert(!strcmp(conf.hostname, extralonghostname));
    assert(!strcmp(conf.location, extralonglocation));
    assert(!strcmp(conf.home, extralonghome));

    return 0;
}

int test_saveconfig(){
    char* username = "username";
    char* hostname = "hostname";
    char* location = "location";
    char* home = "home";

    Config conf = {username, hostname, location, home};
    
    saveconfig("test.yaml", &conf);
    resetconfig(&conf);
    loadconfig("test.yaml", &conf);
    
    assert(!strcmp(conf.username, username));
    assert(!strcmp(conf.hostname, hostname));
    assert(!strcmp(conf.location, location));
    assert(!strcmp(conf.home, home));
    return 0;
}

int test_getconfigvalue();

int test_loadconfig(){
    Config conf = {0, 0, 0, 0};

    for (int i = 0; i < (int)(sizeof(testconfigs)/sizeof(char*)); i++){
        assert(!loadconfig(testconfigs[i], &conf));
        assert(!conf.username == (!values[i][0] ? 0 : 1));
        assert(!conf.hostname == (!values[i][1] ? 0 : 1));
        assert(!conf.location == (!values[i][2] ? 0 : 1));
        assert(!conf.home == (!values[i][3] ? 0 : 1));
        resetconfig(&conf);
    }
    return 0;
}

int main(){
    test_loadconfig();
    test_updateconfigvalue();
    test_saveconfig();
    //assert(test_getconfigvalue());
    return 0;
}
