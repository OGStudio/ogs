FEATURE ogs.h/Include
#include <cstdarg>

FEATURE ogs.h/Impl
//! Construct a string using printf-like syntax.

//! NOTE Only 1024 characters fit in.
std::string printfString(const char *fmt, ...)
{
    const int PRINTF_STRING_MAX_STRLEN = 1024;
    va_list args;
    char msg[PRINTF_STRING_MAX_STRLEN];
    va_start(args, fmt);
    vsnprintf(msg, PRINTF_STRING_MAX_STRLEN, fmt, args);
    va_end(args);
    return msg;
}
