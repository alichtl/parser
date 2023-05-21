//
// Copyright (c) 2023 Adam Lichtl.
//

#include <fstream>
#include <iostream>

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
  cout << "Hello, world " << num() << endl;
  return 0;
}
