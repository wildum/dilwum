#include "environment.h"
#include "tests/test.h"
#include "tools.h"
#include "brainDrawer.h"
#include <string.h>

bool Environment::debugMode = false;

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "test") == 0)
    {
        test::runAllTests();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "draw") == 0)
    {
        BrainDrawer brainDrawer;
        brainDrawer.drawRandomBrain();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "debug") == 0)
        Environment::debugMode = true;

    Environment::run();
    return 0;
}