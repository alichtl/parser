//
// Copyright (c) 2023 Adam Lichtl.
//

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include "parser.h"

// From: https://unicode.org/faq/utf_bom.html#bom4
//
// | Bytes       | Encoding Form         |
// | ----------- | --------------------- |
// | 00 00 FE FF | UTF-32, big-endian    |
// | FF FE 00 00 | UTF-32, little-endian |
// | FE FF       | UTF-16, big-endian    |
// | FF FE       | UTF-16, little-endian |
// | EF BB BF    | UTF-8                 |

int main(int argc, char* argv[]) {
  // const string filepath{"../sample_files/limerick_crlf_utf8_bom.txt"};
  const string filepath{"../sample_files/limerick_crlf_utf8_bom.txt"};

  const size_t kBufferSize = 2048;
  char buffer[kBufferSize];

  // Verify file is UTF-8 encoded and remove the BOM if present
  ifstream file(filepath);
  if (!file) {
    throw runtime_error("Unable to open " + filepath + ": " + strerror(errno));
  }
  file.read(buffer, kBufferSize);
  auto n_chars_read = file.gcount();

  if (n_chars_read == 0) {
    cout << "File is empty" << endl;
    return EXIT_SUCCESS;
  }

  if (buffer[0] == char(0x00)) {
    throw runtime_error("Unable to parse " + filepath +
                        ": File starts with NULL character. Invalid encoding? "
                        "Only ASCII and UTF-8 are supported.");
  }

  if (buffer[0] == char(0xFF) || buffer[0] == char(0xFE)) {
    throw runtime_error(
        "Unable to parse " + filepath +
        ": Invalid encoding. Only ASCII and UTF-8 is supported.");
  }

  auto start = &buffer[0];
  auto length = n_chars_read;
  if (n_chars_read >= 3 && buffer[0] == char(0xEF) && buffer[1] == char(0xBB) &&
      buffer[2] == char(0xBF)) {
    // Remove UTF-8 BOM
    cout << "WARNING: Detected a UTF-8 BOM. Skipping these three bytes and "
            "excluding them from the indexing calculations."
         << endl;
    start += 3;
    length -= 3;
  }

  string s(start, length);

  cout << s << endl;

  file.close();

  return EXIT_SUCCESS;
}
