#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton School"
#define C1  'n'
#define C2  'S'
#define C3  's'

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    printf("strchr:%p | asm_strchr:%p\n", strchr(S1, C1), asm_strchr(S1, C1));
    printf("strchr:%p | asm_strchr:%p\n", strchr(S1, C2), asm_strchr(S1, C2));
    printf("strchr:%p | asm_strchr:%p\n", strchr(S1, C3), asm_strchr(S1, C3));
    assert(strchr(S1, C1) == asm_strchr(S1, C1));
    assert(strchr(S1, C2) == asm_strchr(S1, C2));
    assert(strchr(S1, C3) == asm_strchr(S1, C3));

    printf("All good!\n");
    return (EXIT_SUCCESS);
}