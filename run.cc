//
// Copyright (c) 2023 Adam Lichtl.
//

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const size_t kBufferSize = 2048;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " FILE" << endl;
    return EXIT_FAILURE;
  }

  try {
    const string filepath{argv[1]};
    ifstream file(filepath);
    if (!file) {
      throw runtime_error("Unable to open " + filepath + ": " + strerror(errno));
    }

    char buffer[kBufferSize];
    size_t buffer_offset = 0;  // offset of buffer within the file
    size_t idx = 0;            // index within the buffer

    file.read(buffer, kBufferSize);
    auto n_chars_read = file.gcount();

    if (n_chars_read >= 1 && buffer[0] == char(0x00)) {  // Detects UTF-32BE
      throw runtime_error("Unable to parse " + filepath +
                          ": File starts with NULL character. Invalid encoding? "
                          "Only ASCII and UTF-8 are supported.");
    }

    if (n_chars_read >= 1 && buffer[0] == char(0xFF) ||
        buffer[0] == char(0xFE)) {  // Detects UTF-32LE, UTF-16BE, and UTF-16LE
      throw runtime_error("Unable to parse " + filepath + ": Invalid encoding. Only ASCII and UTF-8 is supported.");
    }

    if (n_chars_read >= 3 && buffer[0] == char(0xEF) && buffer[1] == char(0xBB) && buffer[2] == char(0xBF)) {
      idx += 3;  // Skip the UTF-8 BOM if found.
    }

    map<string, vector<size_t>> dict{};
    vector<char> word{};
    size_t word_offset = 0;
    while (n_chars_read > 0) {
      for (; idx < n_chars_read; ++idx) {
        if (isspace(buffer[idx])) {
          if (word.size() > 0) {
            dict[string(word.begin(), word.end())].push_back(word_offset);
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
      file.read(buffer, kBufferSize);
      n_chars_read = file.gcount();
    }

    for (const auto& entry : dict) {
      cout << entry.first;
      for (auto word_index : entry.second) {
        cout << " " << word_index;
      }
      cout << endl;
    }
  } catch (runtime_error e) {
    cout << "ERROR: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
