
#FuzzDeck-🔍

FuzzDeck is a structured fuzzing framework built to run and compare performance across four powerful fuzzers — AFL++, Honggfuzz, LibFuzzer, and Radamsa. The tool supports automated compilation, input corpus creation, fuzzing execution, crash monitoring, and power profiling, designed especially for Raspberry Pi, Kali, and resource-constrained systems.
---

## 📚 Table of Contents

- [✨ Features](#-features)  
- [🗂️ Folder Structure](#-folder-structure)  
- [⚙️ Installation](#️-installation)  
  - [Install AFL++](#1-afl)  
  - [Install Honggfuzz](#2-honggfuzz)  
  - [Install LibFuzzer](#3-libfuzzer)  
  - [Install Radamsa](#4-radamsa)  
- [🚀 Usage](#-usage)  
- [🎥 Demo](#-demo)  
- [🔧 Configuration](#-configuration)  
- [🤝 Contributing](#-contributing)  
- [✅ Tests](#-tests)  
- [📦 Deployment](#-deployment)  
- [🧱 Built With](#-built-with)  
- [🙏 Acknowledgments](#-acknowledgments)

---

<video width="720" height="480" controls>
  <source src="./video/FuzzDeck_Demo.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>



## ✨ Features

- Install and use 4 major fuzzers: AFL++, Honggfuzz, LibFuzzer, Radamsa.
- Fuzzing sample C programs (e.g., `png_check.c`) using different strategies.
- Organized folder structure for corpus, targets, scripts, and videos.
- Support for Makefile-based automation.
- Slides and video demos provided.

---

## 🗂️ Folder Structure

```bash
Fuzzing_Project-/
├── commands/          # Shell scripts for each fuzzer's execution
├── input_corpus/      # Seed files for input
├── slides/            # Project slides (PDF/PPT)
├── targets/           # Source code of vulnerable/test programs
├── video/             # Video demos of fuzzing in action
├── .gitignore         
├── Makefile           # Build rules for compiling with fuzzers
├── fuzz_png_header    # Sample C file for fuzzing
├── png_check_afl      # Binary built for AFL++
├── png_check_hf       # Binary built for Honggfuzz
├── png_check_libfuzz  # Binary built for LibFuzzer
└── README.md          # Documentation
```

---

## ⚙️ Installation

### 1. AFL++
```bash
sudo apt update
sudo apt install build-essential clang llvm git -y
git clone https://github.com/AFLplusplus/AFLplusplus.git
cd AFLplusplus
make distrib
sudo make install
```

### 2. Honggfuzz
```bash
sudo apt install unzip pkg-config libbfd-dev binutils-dev -y
git clone https://github.com/google/honggfuzz.git
cd honggfuzz
make
sudo cp hfuzz_cc/hfuzz-clang /usr/local/bin/
```

### 3. LibFuzzer
```bash
sudo apt install clang -y
clang -fsanitize=fuzzer,address fuzz_png_header.c -o png_check_libfuzz
```

### 4. Radamsa
```bash
sudo apt install git make gcc -y
git clone https://gitlab.com/akihe/radamsa.git
cd radamsa
make
sudo make install
```

---

## 🚀 Usage

### AFL++
```bash
afl-fuzz -i input_corpus -o afl_out ./png_check_afl @@
```

### Honggfuzz
```bash
honggfuzz -i input_corpus -o hf_out -- ./png_check_hf ___FILE___
```

### LibFuzzer
```bash
./png_check_libfuzz
```

### Radamsa
```bash
radamsa input_corpus/seed1 > mutated_input
```

---

## 🎥 Demo

- [x] See video folder: `video/`
- [x] See slides folder: `slides/`

---

## 🔧 Configuration

- Add new targets to `targets/`
- Modify `Makefile` to compile with different fuzzers
- Place seed files in `input_corpus/`
- Place demo scripts in `commands/`

---

## 🤝 Contributing

1. Fork the repository
2. Create a new branch
3. Commit your changes
4. Push to your fork
5. Submit a pull request

---

## ✅ Tests

To verify installation:
```bash
which afl-fuzz
which honggfuzz
which radamsa
clang --version
```

To compile:
```bash
make all
```

---

## 📦 Deployment

```bash
chmod +x commands/*.sh
./commands/afl_run.sh
```

For full packaging:
```bash
make clean && make all
```

---

## 🧱 Built With

- C, Make
- Clang, GCC
- AFL++, Honggfuzz, LibFuzzer, Radamsa

---

## 🙏 Acknowledgments

- Open source developers of AFL++, Honggfuzz, Radamsa, and LibFuzzer
