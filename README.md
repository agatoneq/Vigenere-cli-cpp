
# 🔐 Vigenere Cipher Tool

A command-line application written in C++ that supports **encryption**, **decryption**, and **cryptanalysis (key breaking)** using the **Vigenère cipher**.

This was my **first real programming project** – created in C++ during my first semester of studies. It introduced me to command-line applications, file handling, basic cryptography, and algorithmic thinking. Despite being a beginner at the time, I implemented full support for all cipher modes — including automatic key length detection and frequency analysis to guess unknown keys.


## 📌 Features

- **Encryption**  
  Encrypts a plaintext file using a Vigenère cipher and a key from a file.

- **Decryption**  
  Decrypts a ciphertext file using the provided Vigenère key.

- **Key Breaking**  
  Attempts to break the cipher without knowing the key by:
  - Using the **Friedman test** to estimate key length
  - Applying **frequency analysis** to deduce the key itself (for English-language ciphertexts)

- **Command-line interface**  
  Supports switches like `--en`, `--de`, `--br` and flags for input/output/key files

- **Robust file I/O**  
  Handles missing files, incorrect formats, and empty inputs gracefully.


## 🛠 Usage

```bash
./vigenere --en -i input.txt -o output.txt -k key.txt
./vigenere --de -i encrypted.txt -o decrypted.txt -k key.txt
./vigenere --br -i encrypted.txt -o decrypted.txt
```

Launching the program without arguments will display help instructions. The interface is in Polish, but the logic and documentation are universal.


## 📁 Structure

- `vigenere.h` – core functions: encryption, decryption, key length detection, key guessing
- `main.cpp` – handles CLI input and calls logic functions
- `Ustawienia` struct – manages file paths and cipher mode flags


## 🧠 Algorithms

- **Friedman test**  
  Counts coincidences between shifted ciphertexts to estimate key length.

- **Frequency analysis**  
  Matches letter frequencies in ciphertext slices with expected frequencies in English to guess the key.

- **Vigenère logic**  
  Each character is encrypted/decrypted by offsetting it based on a repeating keyword.


## 📊 Sample Results

- Successfully decrypted ciphertexts up to **20k+ characters** with short keys (<13 chars)
- Properly handled empty inputs and file-related errors
- Stable for files up to ~1.5 GB in size before memory limits occur


## 💡 What I learned

- Basics of cryptographic algorithms
- File I/O and memory management in C++
- Command-line argument parsing
- Debugging and testing
- How to break a cipher with math 😊


## 📜 License

This project is educational. Feel free to explore, learn from it, and improve it.
