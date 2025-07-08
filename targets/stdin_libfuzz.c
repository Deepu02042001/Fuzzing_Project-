// stdin_libfuzz.c
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size >= 8 && memcmp(data, "AABBCCDD", 8) == 0) {
        volatile int *p = 0; *p = 42;
    }
    return 0;
}
