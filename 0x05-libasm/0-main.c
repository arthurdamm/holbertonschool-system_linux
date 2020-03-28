#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton School"
#define S2  ""
#define S3  "\0"
#define S4  "FOO"
#define S5  "ABCDEFGHI"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)

{
    printf("[%d] [%lu]\n", strlen(S1) == asm_strlen(S1), asm_strlen(S1));
    printf("[%d] [%lu]\n", strlen(S2) == asm_strlen(S2), asm_strlen(S2));
    printf("[%d] [%lu]\n", strlen(S3) == asm_strlen(S3), asm_strlen(S3));
    printf("[%d] [%lu]\n", strlen(S4) == asm_strlen(S4), asm_strlen(S4));
    printf("[%d] [%lu]\n", strlen(S5) == asm_strlen(S5), asm_strlen(S5));
    printf("All good!\n");
    return (EXIT_SUCCESS);
}
