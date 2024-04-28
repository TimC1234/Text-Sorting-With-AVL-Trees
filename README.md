# Wordlist AVL Tree

## Overview

This program implements a Wordlist class using an AVL tree as its underlying data structure. The Wordlist class is capable of storing words from a file along with their frequencies and provides functionalities such as counting the number of different words, total number of words, most frequent word, and percentage of singleton words.

## Features

- **Word Frequency Tracking**: The Wordlist class tracks the frequency of each word in the provided file.
- **AVL Tree Implementation**: Uses an AVL tree to efficiently store and manage word frequencies.
- **Printing Statistics**: Provides functionality to print statistics such as the number of different words, total number of words, most frequent word, and percentage of singleton words.
- **Constructor**: Includes constructors to create an empty Wordlist object or initialize it with words from a file.
- **Destructor**: Properly deallocates memory by implementing a destructor to free memory allocated for the AVL tree nodes.

## Getting Started

To use the Wordlist AVL Tree implementation, follow these steps:

1. Ensure you have the necessary files: `Wordlist.h` and `a5_main.cpp`.
2. Compile the program using a C++ compiler.
3. Run the compiled executable to test the Wordlist class functionalities.

## Usage

```bash
# Compile the program
make a5_main

# Run the executable
./a5_main
