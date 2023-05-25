<h1>Parser</h1>

A console application to index the words within a text file.

**Table of Contents**

- [Description](#description)
- [Prerequisites](#prerequisites)
- [Setup](#setup)
- [APPENDIX: File encoding check](#appendix-file-encoding-check)

## Description

This application parses a UTF-8 text file into “words”, where each “word” is defined as any consecutive sequence of non-whitespace characters. Whitespace is defined as characters checked by the `isspace()` standard function (i.e. ‘` `‘, ‘`\t`’, ‘`\n`’, ‘`\v`’, ‘`\f`’, ‘`\r`’).

The program prints all unique words in lexicographical order, each on its own line. After each word, separated by spaces, the program prints the character index (0-based, in bytes) of the start of each instance of that word within the original file.

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
  - The directions below assume you're running commands from within this new `build` directory.
- `cmake ..`

Build and run the parser:

- `make parser`
- `./parser <file.txt>`
  - To reproduce the example above, run: `./parser ../sample_files/orig.txt`
  - Other files are available in the `sample_files` directory, some of which are used by the unit tests in `Parser_test.cc`.

Run unit tests (uses the GoogleTest framework):

- `make parser_test`
- `./parser_test`

## APPENDIX: File encoding check

This program only accepts files in the UTF-8 format, either with or without a byte-order mark (BOM).
It detects potential encoding issues by examining the first few bytes of the file.

For manual verification, the raw binary contents of a file can be viewed with `hexdump -C <file>`.

See also <https://unicode.org/faq/utf_bom.html>.

| **BOM**     | **Encoding**          |
| ----------- | --------------------- |
| 00 00 FE FF | UTF-32, big-endian    |
| FF FE 00 00 | UTF-32, little-endian |
| FE FF       | UTF-16, big-endian    |
| FF FE       | UTF-16, little-endian |
| EF BB BF    | UTF-8                 |

<sub>Copyright &copy; 2023 Adam Lichtl</sub>
