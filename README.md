<h1>Parser</h1>

A console application to index the words within a text file.

**Table of Contents**

- [Description](#description)
- [Prerequisites](#prerequisites)
- [Setup](#setup)

## Description

This application parses a UTF-8 text file into “words”, where each “word” is defined as any consecutive sequence of non-whitespace characters. Whitespace is defined as characters checked by the `isspace()` standard function (i.e. ‘` `‘, ‘`\t`’, ‘`\n`’, ‘`\v`’, ‘`\f`’, ‘`\r`’).

The program prints all unique words in lexicographical order, each on its own line. After each word, separated by spaces, the program prints the character index (0-based) of the start of each instance of that word within the original file.

Example:

**some_file.txt**

```
zzz aaa bbb aaa
```

`./parse some_file.txt`

```
aaa 4 12
bbb 8
zzz 0
```

## Prerequisites

Required:

- CMake
- A C++ compiler

Optional:

- VS Code with the following extensions:
  - C/C++ Extension Pack
  - CMake Tools

## Setup

Generate build files. If on Linux/Mac, this will generate a Makefile.

- `mkdir build`
- `cd build`
- `cmake ..`

Build and run the parser (still within the `build` directory):

- `make parser`
- `./parser <file.txt>`

Run unit tests (uses the GoogleTest framework):

- `make parser_test`
- `./parser_test`
