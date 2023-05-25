//
// Copyright (c) 2023 Adam Lichtl.
//

#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

#include <istream>
#include <map>
#include <string>
#include <vector>

class Parser {
 public:
  std::map<std::string, std::vector<std::size_t>> parse(std::istream& is);
};

#endif  // PARSER_PARSER_H_
