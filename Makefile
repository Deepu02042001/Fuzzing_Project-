# Makefile for building fuzzing target versions

# Build target for AFL++, Honggfuzz, and Radamsa (using our common code).
png_check_afl: png_check.c
	# Using AFL++ compiler wrapper; you can choose afl-clang-fast or afl-gcc.
	# Using clang-fast wrapper
	afl-clang-fast -o png_check_afl png_check.c


png_check_hf: png_check.c
	# For Honggfuzz, using hfuzz-clang wrapper.
	CC=/usr/local/bin/hfuzz-clang /usr/local/bin/hfuzz-clang -o png_check_hf png_check.c

# Build the LibFuzzer target version from our fuzz harness.
png_check_libfuzzer: fuzz_png_header.c
	clang -fsanitize=fuzzer,address -o png_check_libfuzzer fuzz_png_header.c

clean:
	rm -f png_check_afl png_check_hf png_check_libfuzzer
