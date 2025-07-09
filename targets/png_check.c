#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("Error opening file");
        return 1;
    }

    unsigned char header[8];
    if (fread(header, 1, 8, f) != 8) {
        printf("File too short\n");
        fclose(f);
        return 0;
    }
    fclose(f);

    if (memcmp(header, "\x89PNG\r\n\x1a\n", 8) == 0) {
        printf("Valid PNG header found!\n");
    } else {
        printf("Invalid PNG header.\n");
    }
    return 0;
}
