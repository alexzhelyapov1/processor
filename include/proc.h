#ifndef PROC_H
#define PROC_H

#include <stdio.h>
#include <cstdarg>

// Debug settings
//-----------------------------------------------------------------------------
#define DEBUG_MESSAGE(code) code  // Define wrap for debug print
enum debug_level {
    NO_DEBUG,
    DEBUG_ERRORS,
    DEBUG_MAIN_STEPS,
    DEBUG_ALL
};
#define DEBUG_LEVEL DEBUG_ALL
//-----------------------------------------------------------------------------

FILE* file_logging_init(const char* name_of_file);
void debug_print(enum debug_level level, const char* format, ...);

#endif