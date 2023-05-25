//
// Copyright (c) 2023 Adam Lichtl.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>

#include "Parser.h"

namespace parser {

using ::std::ifstream;
using ::std::runtime_error;
using ::testing::ElementsAre;
using ::testing::Pair;

TEST(Parser, OriginalTestCase) {
  auto index = Parser().parse("zzz aaa bbb aaa\n");
  EXPECT_THAT(index,
              ElementsAre(Pair("aaa", ElementsAre(4, 12)), Pair("bbb", ElementsAre(8)), Pair("zzz", ElementsAre(0))));
}

TEST(Parser, OriginalTestCaseFromFile) {
  ifstream file("../sample_files/orig.txt");
  ASSERT_TRUE(file);

  auto index = Parser().parse(file);
  EXPECT_THAT(index,
              ElementsAre(Pair("aaa", ElementsAre(4, 12)), Pair("bbb", ElementsAre(8)), Pair("zzz", ElementsAre(0))));
}

TEST(Parser, SmallBuffer) {
  const size_t buffer_size_bytes{2};
  auto index = Parser(buffer_size_bytes).parse("zzz aaa bbb aaa\n");
  EXPECT_THAT(index,
              ElementsAre(Pair("aaa", ElementsAre(4, 12)), Pair("bbb", ElementsAre(8)), Pair("zzz", ElementsAre(0))));
}

TEST(Parser, UTF8File) {
  ifstream file("../sample_files/limerick_lf_utf8.txt");
  ASSERT_TRUE(file);

  auto index = Parser().parse(file);
  ASSERT_EQ(index.size(), 30);

  auto it = index.find("består");
  ASSERT_NE(it, index.end());
  EXPECT_THAT(it->second, ElementsAre(95));
}

TEST(Parser, UTF8FileCRLF) {
  ifstream file("../sample_files/limerick_crlf_utf8.txt");
  ASSERT_TRUE(file);

  auto index = Parser().parse(file);
  ASSERT_EQ(index.size(), 30);

  auto it = index.find("består");
  ASSERT_NE(it, index.end());
  EXPECT_THAT(it->second, ElementsAre(96));
}

TEST(Parser, UTF8FileCRLFBOM) {
  ifstream file("../sample_files/limerick_crlf_utf8_bom.txt");
  ASSERT_TRUE(file);

  auto index = Parser().parse(file);
  ASSERT_EQ(index.size(), 30);

  auto it = index.find("består");
  ASSERT_NE(it, index.end());
  EXPECT_THAT(it->second, ElementsAre(99));
}

TEST(Parser, EmptyFile) {
  ifstream file("../sample_files/empty.txt");
  ASSERT_TRUE(file);

  auto index = Parser().parse(file);
  ASSERT_EQ(index.size(), 0);
}

TEST(Parser, NullFileThrows) {
  ifstream file("../sample_files/null.txt");
  ASSERT_TRUE(file);
  EXPECT_THROW(Parser().parse(file), runtime_error);
}

TEST(Parser, SingleCharFile) {
  ifstream file("../sample_files/single_char.txt");
  ASSERT_TRUE(file);

  auto index = Parser().parse(file);
  ASSERT_EQ(index.size(), 0);

  EXPECT_THAT(index, ElementsAre(Pair("a", ElementsAre(0))));
}

TEST(Parser, UTF16LEFileThrows) {
  ifstream file("../sample_files/limerick_crlf_utf16le_bom.txt");
  ASSERT_TRUE(file);
  EXPECT_THROW(Parser().parse(file), runtime_error);
}

TEST(Parser, UTF16BEFileThrows) {
  ifstream file("../sample_files/limerick_crlf_utf16be_bom.txt");
  ASSERT_TRUE(file);
  EXPECT_THROW(Parser().parse(file), runtime_error);
}

}  // namespace parser
