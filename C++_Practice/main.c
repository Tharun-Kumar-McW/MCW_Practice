#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // printf("Addition : %d",addition(6,6)+CONSTONE);
    char *s = malloc(20);
    strcpy(s,"Hello");
    printf("%s\n",s);
    free(s);
    return 0;
}