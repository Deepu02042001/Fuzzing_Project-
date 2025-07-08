#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buf[100];
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) return 1;
    fread(buf, 1, 100, fp);
    fclose(fp);

    if (memcmp(buf, "AABBCCDD", 8) == 0) {
        int *ptr = NULL;
        *ptr = 1; // Deliberate crash
    }
    return 0;
}
