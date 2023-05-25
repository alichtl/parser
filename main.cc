//
// Copyright (c) 2023 Adam Lichtl.
//

#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Parser.h"

using parser::Parser;
using std::cout;
using std::endl;
using std::ifstream;
using std::runtime_error;
using std::string;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " FILE" << endl;
    return EXIT_FAILURE;
  }
  const string filepath{argv[1]};

  try {
    ifstream file(filepath);
    if (!file) {
      throw runtime_error("Unable to open " + filepath + ": " + strerror(errno));
    }

    const auto index = Parser().parse(file);

    for (const auto& entry : index) {
      cout << entry.first;
      for (const auto word_index : entry.second) {
        cout << " " << word_index;
      }
      cout << endl;
    }
  } catch (const runtime_error& e) {
    cout << "ERROR: Unable to parse " << filepath << ": " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
