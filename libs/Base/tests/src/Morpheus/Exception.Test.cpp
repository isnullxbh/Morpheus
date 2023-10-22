/**
 * @file    Exception.Test.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    21.10.2023
 */

#include <gtest/gtest.h>

#include <Morpheus/Exception.hpp>

TEST(ExceptionTests, Construct)
{
    using namespace Morpheus;
    Exception e { "a{}b{}c", 10, "_" };
    EXPECT_EQ(e.message(), "a10b_c");
    EXPECT_STREQ(e.what(), "a10b_c");
}
