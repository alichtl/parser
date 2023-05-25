//
// Copyright (c) 2023 Adam Lichtl.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Parser.h"

namespace parser {

using ::testing::ElementsAre;
using ::testing::Pair;

TEST(Parser, OriginalTestCase) {
  EXPECT_THAT(Parser().parse("zzz aaa bbb aaa\n"),
              ElementsAre(Pair("aaa", ElementsAre(4, 12)), Pair("bbb", ElementsAre(8)), Pair("zzz", ElementsAre(0))));
}

}  // namespace parser
