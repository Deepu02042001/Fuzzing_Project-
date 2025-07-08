import os
import subprocess
import time
import psutil
import binascii

# Load test cases
with open("fuzz_inputs_1000.txt", "r") as f:
    testcases = f.read().splitlines()

# Output CSV log
with open("results.csv", "w") as log:
    log.write("id,cpu_usage,exec_time,crash\n")

    for i, hex_input in enumerate(testcases):
        input_file = f"input_{i}.bin"
        with open(input_file, "wb") as fbin:
            fbin.write(binascii.unhexlify(hex_input))

        # Run the binary and monitor CPU usage
        start = time.time()
        try:
            proc = subprocess.Popen(["./vuln", input_file])
            ps_proc = psutil.Process(proc.pid)
            cpu_usage = []

            while proc.poll() is None:
                usage = ps_proc.cpu_percent(interval=0.1)
                cpu_usage.append(usage)

            avg_cpu = round(sum(cpu_usage) / len(cpu_usage), 2) if cpu_usage else 0.0
            crashed = proc.returncode != 0
        except Exception as e:
            avg_cpu = 0.0
            crashed = 1  # treat failure as crash

        exec_time = round(time.time() - start, 3)

        log.write(f"{i},{avg_cpu},{exec_time},{crashed}\n")
        print(f"[{i}] CPU: {avg_cpu}%, Time: {exec_time}s, Crash: {crashed}")
