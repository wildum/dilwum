#include "environment.h"
#include "tests/test.h"
#include "tools.h"
#include "brainDrawer.h"
#include "config/config.h"
#include <string.h>

bool Environment::debugMode = false;

int main(int argc, char *argv[])
{
    tools::log("start program");

    std::string configPath = "config/config.json";
    try
    {
        Config::readConfig(configPath);
    }
    catch (...)
    {
        tools::log("cant read the config");
        return -1;
    }
    
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

    if (argc > 1 && strcmp(argv[1], "replay") == 0)
    {
        std::string fileName = argc > 2 ? argv[2] : "lastPlay.txt";
        Environment::run(fileName);
    }
    else
    {
        Environment::run();
    }

    return 0;
}