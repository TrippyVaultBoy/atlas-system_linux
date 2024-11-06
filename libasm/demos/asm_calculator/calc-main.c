#include "demos.h"


int main() {
    int arg1 = 1;
    int i;

    for (i = 0; i <= 10; i++) {
        printf("1 + %d = %d\n", i, asm_calculator(arg1, i, '+'));
    }
    return 0;
}