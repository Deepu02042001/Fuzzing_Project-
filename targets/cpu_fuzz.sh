#!/bin/bash

# === CONFIG ===
CORPUS=corpora/cpu
DURATION=60  # seconds per fuzzer run
LOG="logs/fuzz_cpu_log.txt"
mkdir -p logs

log_line() {
    echo "$1" | tee -a "$LOG"
}

log_line "?? CPU-Intensive Fuzzing Run: $(date)"
log_line "Each fuzzer will run for $DURATION seconds"
log_line "----------------------------"

run_fuzzer() {
    local NAME=$1
    local CMD=$2
    local CRASH_PATTERN=$3

    log_line "[*] Starting $NAME..."
    echo "Please enter power reading BEFORE running $NAME:"
    read -p "  Power START (mWh): " P_START

    START=$(date +%s)
    eval "$CMD"
    END=$(date +%s)

    echo "Please enter power reading AFTER running $NAME:"
    read -p "  Power END (mWh): " P_END

    DURATION_REAL=$((END - START))
    DELTA=$((P_END - P_START))

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
  "AFL_SKIP_CPUFREQ=1 timeout $DURATION afl-fuzz -i $CORPUS -o logs/out_cpu_afl -- ./cpu_afl @@ > logs/afl_cpu_stdout.log 2>&1" \
  "find logs/out_cpu_afl/default/crashes -type f ! -name 'README.txt' | head -n 1"

# === Honggfuzz ===
run_fuzzer "Honggfuzz" \
  "timeout $DURATION honggfuzz -i $CORPUS -o logs/out_cpu_hongg -- ./cpu_hongg ___FILE___ > logs/hongg_cpu_stdout.log 2>&1" \
  "find logs/out_cpu_hongg -name '*.fuzz' | head -n 1"

# === LibFuzzer ===
run_fuzzer "LibFuzzer" \
  "timeout $DURATION ./cpu_libfuzz $CORPUS > logs/libfuzz_cpu_stdout.log 2>&1" \
  "grep -o './crash-[a-zA-Z0-9]*' logs/libfuzz_cpu_stdout.log | head -n 1"

log_line "? CPU fuzzing complete. Summary in $LOG"
