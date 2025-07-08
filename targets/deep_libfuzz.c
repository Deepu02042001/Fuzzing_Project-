/* deep_libfuzz.c – NO main(), uses LLVMFuzzerTestOneInput */
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 8) return 0;

    if (data[0]=='A' && data[1]=='A')                 /* L1 */
    if (data[2]=='B' && data[3]=='B' && data[4]=='C') /* L2 */
    if (data[5]=='C' && data[6]=='D' && data[7]=='D') {
        volatile int *p = 0;
        *p = 0xBEEF;          /* crash */
    }
    return 0;
}
