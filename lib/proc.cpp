#include "../include/proc.h"

FILE* log_file = file_logging_init("log_file.txt");

void debug_print(enum debug_level level, const char* format, ...) {
    va_list args;
    va_start(args, format);
    if (level <= DEBUG_LEVEL) {
        vfprintf(log_file, format, args);
    }
    va_end(args);
}

FILE* file_logging_init(const char* name_of_file) {
    FILE* f = fopen(name_of_file, "w");
    if (!f) {
        printf("Can't open file for logging!\n");
        return NULL;
    }
    return f;
}