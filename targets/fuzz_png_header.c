#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // We require at least 8 bytes for a PNG header.
    if (Size < 8)
        return 0;
    // Check if first 8 bytes match PNG signature.
    if (memcmp(Data, "\x89PNG\r\n\x1a\n", 8) == 0) {
        printf("Valid PNG header found!\n");
    }
    return 0;
}
