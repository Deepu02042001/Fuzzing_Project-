// fuzz_png_header.c

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;
    if (memcmp(Data, "\x89PNG\r\n\x1a\n", 8) == 0) {
        printf("Valid PNG!\n");
    }
    return 0;
}
