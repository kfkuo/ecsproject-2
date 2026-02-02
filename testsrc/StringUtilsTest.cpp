#include <gtest/gtest.h>
#include "StringUtils.h"

using namespace StringUtils;

TEST(StringUtilsTest, SliceTest){
    EXPECT_EQ(Slice("hello", 0, 2), "he");
    EXPECT_EQ(Slice("hello", 1, 4), "ello");
    EXPECT_EQ(Slice("hello", -2, 0), "lo");
    EXPECT_EQ(Slice("hello", 0, 0), "hello");
}

TEST(StringUtilsTest, Capitalize){
    EXPECT_EQ(StringUtils::Capitalize(""),std::string(""));
    EXPECT_EQ(StringUtils::Capitalize("hello"),std::string("Hello"));
    EXPECT_EQ(StringUtils::Capitalize(" hello world"),std::string(" hello world"));
    EXPECT_EQ(StringUtils::Capitalize("hello world"),std::string("Hello world"));
    EXPECT_EQ(StringUtils::Capitalize("HELLO WORLD"),std::string("Hello world"));
}

TEST(StringUtilsTest, Upper){
    EXPECT_EQ(Upper("hello"), "HELLO");
    EXPECT_EQ(Upper("Hello123"), "HELLO123");
    EXPECT_EQ(Upper(""), "");
}

TEST(StringUtilsTest, Lower){
    EXPECT_EQ(Lower("HELLO"), "hello");
    EXPECT_EQ(Lower("Hello123"), "hello123");
    EXPECT_EQ(Lower(""), "");
}

TEST(StringUtilsTest, LStrip){
    EXPECT_EQ(StringUtils::LStrip("Hello"),std::string("Hello"));
    EXPECT_EQ(StringUtils::LStrip(" Hello"),std::string("Hello"));
    EXPECT_EQ(StringUtils::LStrip("Hello "),std::string("Hello "));
    EXPECT_EQ(StringUtils::LStrip("   Hello"),std::string("Hello"));
    EXPECT_EQ(StringUtils::LStrip(" \r \t \nHello"),std::string("Hello"));
}

TEST(StringUtilsTest, RStrip){
    EXPECT_EQ(StringUtils::RStrip("      "),std::string(""));
    EXPECT_EQ(StringUtils::RStrip(""),std::string(""));
    EXPECT_EQ(StringUtils::RStrip("Hello"),std::string("Hello"));
    EXPECT_EQ(StringUtils::RStrip("Hello "),std::string("Hello"));
    EXPECT_EQ(StringUtils::RStrip(" Hello"),std::string(" Hello"));
    EXPECT_EQ(StringUtils::RStrip("Hello   "),std::string("Hello"));
    EXPECT_EQ(StringUtils::RStrip("Hello \r \t \n"),std::string("Hello"));
}

TEST(StringUtilsTest, Strip){
    EXPECT_EQ(StringUtils::Strip(" Hello"),std::string("Hello"));
    EXPECT_EQ(StringUtils::Strip("Hello "),std::string("Hello"));
    EXPECT_EQ(StringUtils::Strip("   Hello"),std::string("Hello"));
    EXPECT_EQ(StringUtils::Strip(" \r \t \nHello"),std::string("Hello"));
    EXPECT_EQ(StringUtils::Strip("      "),std::string(""));
    EXPECT_EQ(StringUtils::Strip(""),std::string(""));
    EXPECT_EQ(StringUtils::Strip("Hello   "),std::string("Hello"));
    EXPECT_EQ(StringUtils::Strip("Hello \r \t \n"),std::string("Hello"));
    EXPECT_EQ(StringUtils::Strip(" \r \t \nHello \r \t \n"),std::string("Hello"));
}

TEST(StringUtilsTest, Center){
    EXPECT_EQ(Center("hello", 7, '*'), "*hello*");
    EXPECT_EQ(Center("hello", 6), "hello ");
    EXPECT_EQ(Center("hello", 4, ' '), "hello");
}

TEST(StringUtilsTest, LJust){
    EXPECT_EQ(LJust("hello", 7, '*'), "hello**");
    EXPECT_EQ(LJust("hello", 3), "hello");
}

TEST(StringUtilsTest, RJust){
    EXPECT_EQ(RJust("hello", 7, '*'), "**hello");
    EXPECT_EQ(RJust("hello", 3), "hello");
}

TEST(StringUtilsTest, Replace){
    EXPECT_EQ(Replace("hello hello", "h", "H"), "Hello Hello");
    EXPECT_EQ(Replace("hello", "z", "x"), "hello");
}

TEST(StringUtilsTest, Split){
    std::vector<std::string> r1 = Split("hello world", " ");
    EXPECT_EQ(r1.size(), 2);
    EXPECT_EQ(r1[0], "hello");
    EXPECT_EQ(r1[1], "world");

    std::vector<std::string> r2 = Split("hello,world,again", ",");
    EXPECT_EQ(r2.size(), 3);
    EXPECT_EQ(r2[0], "hello");
    EXPECT_EQ(r2[1], "world");
    EXPECT_EQ(r2[2], "again");

    std::vector<std::string> r3 = Split("hello world again", "");
    EXPECT_EQ(r3.size(), 3);
    EXPECT_EQ(r3[0], "hello");
    EXPECT_EQ(r3[1], "world");
    EXPECT_EQ(r3[2], "again");
}

TEST(StringUtilsTest, Join){
    std::vector<std::string> v = {"hello", "world"};
    EXPECT_EQ(Join(" ", v), "hello world");
    EXPECT_EQ(Join("-", v), "hello-world");
    EXPECT_EQ(Join("", v), "helloworld");
}

TEST(StringUtilsTest, ExpandTabs){
    EXPECT_EQ(ExpandTabs("hell\tworld", 4), "hell   world");
    EXPECT_EQ(ExpandTabs("\thello", 4), "    hello");
}

TEST(StringUtilsTest, EditDistance){
    EXPECT_EQ(EditDistance("hello", "helloo"), 1);
    EXPECT_EQ(EditDistance("hello", "jello"), 1);
    EXPECT_EQ(EditDistance("Hello", "hello", true), 0);
    EXPECT_EQ(EditDistance("Hello", "hello", false), 1);
}
