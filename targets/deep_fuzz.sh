#!/bin/bash

# === CONFIG ===
CORPUS=corpora/deep
DURATION=60  # seconds per fuzzer run
LOG="fuzz_log.txt"
mkdir -p logs

log_line() {
    echo "$1" | tee -a "$LOG"
}

log_line "Fuzzing run started: $(date)"
log_line "Each fuzzer runs for $DURATION seconds"
log_line "----------------------------"

# === Function: Run a fuzzer with power prompts ===
run_fuzzer() {
    local NAME=$1
    local CMD=$2
    local CRASH_PATTERN=$3

    log_line "[*] Starting $NAME..."
    echo "Please enter power reading BEFORE starting $NAME:"
    read -p "  Power START (mWh): " P_START

    START=$(date +%s)
    eval "$CMD"
    END=$(date +%s)

    echo "Please enter power reading AFTER running $NAME:"
    read -p "  Power END (mWh): " P_END

    DURATION_REAL=$((END - START))
    DELTA=$((P_END - P_START))

    # Detect crash
    CRASH_FILE=$(eval "$CRASH_PATTERN")
    log_line "[$NAME] Duration: ${DURATION_REAL}s"
    log_line "[$NAME] Power used: ${DELTA} mWh"
    if [[ -n "$CRASH_FILE" ]]; then
        log_line "[$NAME] Crash: $CRASH_FILE"
    else
        log_line "[$NAME] No crash found"
    fi
    log_line "----------------------------"
}

# === AFL++ ===
run_fuzzer "AFL++" \
  "AFL_SKIP_CPUFREQ=1 timeout $DURATION afl-fuzz -i $CORPUS -o logs/out_afl -- ./deep_afl @@ > logs/afl_stdout.log 2>&1" \
  "find logs/out_afl/default/crashes -type f ! -name 'README.txt' | head -n 1"

# === Honggfuzz ===
run_fuzzer "Honggfuzz" \
  "timeout $DURATION honggfuzz -i $CORPUS -o logs/out_hongg -- ./deep_hongg ___FILE___ > logs/hongg_stdout.log 2>&1" \
  "find logs/out_hongg -name '*.fuzz' | head -n 1"

# === LibFuzzer ===
run_fuzzer "LibFuzzer" \
  "timeout $DURATION ./deep_libfuzz $CORPUS > logs/libfuzz_stdout.log 2>&1" \
  "grep -o './crash-[a-zA-Z0-9]*' logs/libfuzz_stdout.log | head -n 1"

log_line "? All fuzzers completed. Summary saved to $LOG"
