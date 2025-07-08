/* deep_target.c  – has main() */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc != 2) return 1;

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) return 2;

    uint8_t buf[16] = {0};
    size_t n = fread(buf, 1, sizeof(buf), fp);
    fclose(fp);

    /* ----- 3-level logic gate ----- */
    if (n >= 8 && buf[0]=='A' && buf[1]=='A')          /* L1 */
    if (buf[2]=='B' && buf[3]=='B' && buf[4]=='C')      /* L2 */
    if (buf[5]=='C' && buf[6]=='D' && buf[7]=='D') {    /* L3 */
        volatile int *p = 0;
        *p = 0xDEAD;            /* crash */
    }
    return 0;
}

