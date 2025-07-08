#include <stdio.h>
#include <string.h>
#include <stdint.h>

static void heavy(uint8_t *b, size_t n) {
    /* Simulate ~20 ms of CPU load */
    for (size_t i = 0; i < 1000000; ++i)
        b[i % n] ^= (i * 31) & 0xFF;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) return 2;

    uint8_t buf[128];
    size_t n = fread(buf, 1, sizeof(buf), fp);
    fclose(fp);

    heavy(buf, n);  // simulate CPU load

    if (n >= 8 && !memcmp(buf, "AABBCCDD", 8)) {
        volatile int *p = 0;
        *p = 7;  // deliberate crash (now preserved)
    }

    return 0;
}

