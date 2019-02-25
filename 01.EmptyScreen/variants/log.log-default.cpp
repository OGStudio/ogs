FEATURE ogs.h/Include
#include <iostream>

FEATURE ogs.h/Impl
//! Cross-platform logging function.
void log(const char *message)
{
    std::cout << message << std::endl;
}
