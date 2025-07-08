#include <stdint.h>
#include <stddef.h>
#include <string.h>

static void heavy(uint8_t *b, size_t n) {
    for (size_t i = 0; i < 1000000; ++i)
        b[i % n] ^= (i * 31) & 0xFF;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 8) return 0;

    // Copy to mutable buffer
    uint8_t buf[128];
    size_t len = size < sizeof(buf) ? size : sizeof(buf);
    memcpy(buf, data, len);

    heavy(buf, len);  // CPU load

    if (!memcmp(buf, "AABBCCDD", 8)) {
        volatile int *p = 0;
        *p = 7;  // crash
    }

    return 0;
}
