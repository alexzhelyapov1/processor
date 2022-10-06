#include "../include/proc.h"
#include "../include/asm.h"
#include "../include/text_tools.h"

int asm_main(const char* file_name) {
    // struct Bufer* bufer = init_bufer_for_file(file_name);
    // if (!bufer) {
    //     DEBUG_MESSAGE(debug_print(DEBUG_ERRORS, "Returned NULL ptr to bufer\n");)
    //     return -1;
    // }

    char* out_name = make_bin_name(file_name);
    

    // while (i < bufer->len) {

    // }
}

char* make_bin_name(const char* file_name) {
    char* bin_name = (char*) calloc(100, sizeof(char));
    strcpy(bin_name, file_name);
    int i = strlen(bin_name);
    while (i >= 0 && bin_name[i] != '.') i--;
    if (i < 0) {
        strcpy(bin_name, "output.asm");
    }
    else {
        strcpy(bin_name + i, ".asm");
    }
    DEBUG_MESSAGE(debug_print(DEBUG_MAIN_STEPS, "New bin name = %s\n", bin_name);)
    return bin_name;
}