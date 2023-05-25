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
  Parser(size_t buffer_size_bytes = 2048) : buffer_size_bytes_{buffer_size_bytes} {}
  std::map<std::string, std::vector<std::size_t>> parse(std::istream& is) const;
  std::map<std::string, std::vector<std::size_t>> parse(std::string_view sv) const;

 private:
  const size_t buffer_size_bytes_;
};

}  // namespace parser

#endif  // PARSER_PARSER_H_
