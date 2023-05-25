//
// Copyright (c) 2023 Adam Lichtl.
//

#include "Parser.h"

#include <istream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace parser {

using ::std::istream;
using ::std::istringstream;
using ::std::map;
using ::std::runtime_error;
using ::std::size_t;
using ::std::string;
using ::std::string_view;
using ::std::vector;

map<string, vector<size_t>> Parser::parse(istream& is) const {
  char buffer[buffer_size_bytes_];
  size_t buffer_offset{0};  // offset of buffer within the file
  size_t idx{0};            // index within the buffer

  is.read(buffer, buffer_size_bytes_);
  auto n_chars_read = is.gcount();

  if (n_chars_read >= 1 && buffer[0] == char(0x00)) {  // Detects UTF-32BE
    throw runtime_error(
        "Stream starts with NULL character. Invalid encoding? "
        "Only ASCII and UTF-8 are supported.");
  }

  if (n_chars_read >= 1 && buffer[0] == char(0xFF) ||
      buffer[0] == char(0xFE)) {  // Detects UTF-32LE, UTF-16BE, and UTF-16LE
    throw runtime_error("Invalid encoding. Only ASCII and UTF-8 is supported.");
  }

  if (n_chars_read >= 3 && buffer[0] == char(0xEF) && buffer[1] == char(0xBB) && buffer[2] == char(0xBF)) {
    idx += 3;  // Skip the UTF-8 BOM if found.
  }

  map<string, vector<size_t>> index{};
  vector<char> word{};
  size_t word_offset{0};
  while (n_chars_read > 0) {
    for (; idx < n_chars_read; ++idx) {
      if (isspace(buffer[idx])) {
        if (word.size() > 0) {
          index[string(word.begin(), word.end())].push_back(word_offset);
          word.clear();
        }
      } else {
        if (word.size() == 0) {
          word_offset = buffer_offset + idx;
        }
        word.push_back(buffer[idx]);
      }
    }
    buffer_offset += n_chars_read;
    idx = 0;
    is.read(buffer, buffer_size_bytes_);
    n_chars_read = is.gcount();
  }
  if (word.size() > 0) {
    index[string(word.begin(), word.end())].push_back(word_offset);
  }

  return index;
}

map<string, vector<size_t>> Parser::parse(string_view sv) const {
  istringstream is{string{sv}};
  return parse(is);
}

}  // namespace parser
