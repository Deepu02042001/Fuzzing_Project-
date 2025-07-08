#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    unsigned char buf[128] = {0};
    size_t n = fread(buf, 1, sizeof(buf), stdin);

    /* Vulnerability trigger */
    if (n >= 8 && memcmp(buf, "AABBCCDD", 8) == 0) {
        int *p = NULL;          // null-ptr deref
        *p = 42;
    }
    return 0;
}
