#include "environment.h"
#include "tests/test.h"
#include "tools.h"
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "test") == 0)
        test::runAllTests();
    else
        Environment::run();
    return 0;
}