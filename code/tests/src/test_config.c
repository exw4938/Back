#include <assert.h>
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

int test_updateconfigvalue();
int test_saveconfig();
int test_getconfigvalue();

int test_loadconfig(){
    Config conf = {0, 0, 0, 0};

    for (int i = 0; i < sizeof(testconfigs); i++){
        assert(!loadconfig(testconfigs[i], &conf));
        assert(!conf.username == values[i][0] ? 1 : 0);
        assert(!conf.hostname == values[i][1] ? 1 : 0);
        assert(!conf.location == values[i][2] ? 1 : 0);
        assert(!conf.home == values[i][3] ? 1 : 0);
    }
}

int main(){
    assert(test_loadconfig());
    //assert(test_updateconfigvalue());
    //assert(test_saveconfig());
    //assert(test_getconfigvalue());
}
