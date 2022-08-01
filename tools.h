#ifndef TOOLS
#define TOOLS

#include <iostream>

class Tools
{
    public:
        static void log(const std::string& message)
        {
            std::cerr << message << std::endl;
        }
};

#endif