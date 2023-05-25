//
// Copyright (c) 2023 Adam Lichtl.
//

#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

#include <istream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parser {

class Parser {
 public:
  std::map<std::string, std::vector<std::size_t>> parse(std::istream& is);
  std::map<std::string, std::vector<std::size_t>> parse(std::string_view sv);
};

}  // namespace parser

#endif  // PARSER_PARSER_H_
