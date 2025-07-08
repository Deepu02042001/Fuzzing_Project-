#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <png.h>

/* LibFuzzer entry point – **no main()** */
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 24) return 0;                // need header + IHDR width

    if (png_sig_cmp((png_bytep)data, 0, 8)) // not a PNG
        return 0;

    /* bytes 16-19 are IHDR width */
    if (!memcmp(data + 16, "ABCD", 4)) {
        volatile int *p = 0; *p = 1;        // deliberate crash
    }
    return 0;
}
