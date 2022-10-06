#include <stdio.h>
#include "include/asm.h"
#include "include/proc.h"

int main() {
    printf("Hello\n");
    asm_main("input.txt");
    return 0;
}