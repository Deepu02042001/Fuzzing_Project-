// vuln.c - compile with afl-gcc
#include <stdio.h>
#include <string.h>

int main() {
    char buf[100];
    fgets(buf, 300, stdin);
    if (strcmp(buf, "A"*300) == 0) {
        printf("Crashed!\n");
    }
    return 0;
}
