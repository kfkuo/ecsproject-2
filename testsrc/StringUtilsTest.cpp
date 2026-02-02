#include <gtest/gtest.h>
#include "StringUtils.h"

TEST(StringUtilsTest, SliceTest){
    EXPECT_EQ(StringUtils::Slice("Hello World", 0, 5), std::string("Hello"));
    EXPECT_EQ(StringUtils::Slice("Hello World", 6, -1), std::string("Worl"));
    EXPECT_EQ(StringUtils::Slice("Hello World", 0), std::string(""));
    EXPECT_EQ(StringUtils::Slice("Hello World", -1), std::string(""));
}

TEST(StringUtilsTest, Capitalize){
    EXPECT_EQ(StringUtils::Capitalize("hello world"), std::string("Hello world"));
    EXPECT_EQ(StringUtils::Capitalize("hEllo world"), std::string("Hello world"));
    EXPECT_EQ(StringUtils::Capitalize(" Hello"), std::string(" hello"));
}

TEST(StringUtilsTest, Upper){
    EXPECT_EQ(StringUtils::Upper("hello"), std::string("HELLO"));
    EXPECT_EQ(StringUtils::Upper("HeLLo"), std::string("HELLO"));
    EXPECT_EQ(StringUtils::Upper(" Hello"), std::string(" HELLO"));
}

TEST(StringUtilsTest, Lower){
    EXPECT_EQ(StringUtils::Lower("HELLO"), std::string("hello"));
    EXPECT_EQ(StringUtils::Lower("HeLLo"), std::string("hello"));
    EXPECT_EQ(StringUtils::Lower(" Hello"), std::string(" hello"));
}

TEST(StringUtilsTest, LStrip){
    EXPECT_EQ(StringUtils::LStrip(" Hello World"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::LStrip("  Hello World"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::LStrip("\nHello World"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::LStrip("\tHello World"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::LStrip("\rHello World"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::LStrip("\vHello World"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::LStrip("\fHello World"), std::string("Hello World"));
}

TEST(StringUtilsTest, RStrip){
    EXPECT_EQ(StringUtils::RStrip("Hello World "), std::string("Hello World"));
    EXPECT_EQ(StringUtils::RStrip("Hello World  "), std::string("Hello World"));
    EXPECT_EQ(StringUtils::RStrip("Hello World\n"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::RStrip("Hello World\t"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::RStrip("Hello World\r"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::RStrip("Hello World\v"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::RStrip("Hello World\f"), std::string("Hello World"));
}

TEST(StringUtilsTest, Strip){
    EXPECT_EQ(StringUtils::Strip(" Hello World "), std::string("Hello World"));
    EXPECT_EQ(StringUtils::Strip("  Hello World  "), std::string("Hello World"));
    EXPECT_EQ(StringUtils::Strip("\nHello World\n"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::Strip("\tHello World\t"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::Strip("\rHello World\r"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::Strip("\vHello World\v"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::Strip("\fHello World\f"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::Strip(" Hello World"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::Strip("Hello World "), std::string("Hello World"));
}

TEST(StringUtilsTest, Center){
    EXPECT_EQ(StringUtils::Center("Hello World", 13), std::string(" Hello World "));
    EXPECT_EQ(StringUtils::Center("Hello World", 12), std::string("Hello World "));
    EXPECT_EQ(StringUtils::Center("Hello World", 11), std::string("Hello World"));
    EXPECT_EQ(StringUtils::Center("Hello World", 1), std::string("Hello World"));
    EXPECT_EQ(StringUtils::Center("Hello World", 13, 'x'), std::string("xHello Worldx"));
}

TEST(StringUtilsTest, LJust){
    EXPECT_EQ(StringUtils::LJust("Hello World", 13), std::string("Hello World  "));
    EXPECT_EQ(StringUtils::LJust("Hello World", 11), std::string("Hello World"));
    EXPECT_EQ(StringUtils::LJust("Hello World", 1), std::string("Hello World"));
    EXPECT_EQ(StringUtils::LJust("Hello World", 12, 'x'), std::string("Hello Worldx"));
}

TEST(StringUtilsTest, RJust){
    EXPECT_EQ(StringUtils::RJust("Hello World", 13), std::string("  Hello World"));
    EXPECT_EQ(StringUtils::RJust("Hello World", 11), std::string("Hello World"));
    EXPECT_EQ(StringUtils::RJust("Hello World", 1), std::string("Hello World"));
    EXPECT_EQ(StringUtils::RJust("Hello World", 12, 'x'), std::string("xHello World"));
}

TEST(StringUtilsTest, Replace){
    EXPECT_EQ(StringUtils::Replace("Hello World", "World", "Worms"), std::string("Hello Worms"));
    EXPECT_EQ(StringUtils::Replace("Hello World", "World", ""), std::string("Hello "));
    EXPECT_EQ(StringUtils::Replace("Hello World", "l", "w"), std::string("Hewwo Worwd"));
    EXPECT_EQ(StringUtils::Replace("Hello World", "a", "w"), std::string("Hello World"));
    EXPECT_EQ(StringUtils::Replace("Hello World", "L", ""), std::string("Hello World"));
}

TEST(StringUtilsTest, Split){
    std::vector<std::string> result1{"Hello", "Worldly", "Worms"};
    EXPECT_EQ(StringUtils::Split("Hello Worldly Worms"), result1);

    std::vector<std::string> result4{"Hello", "Worldly", "Worms"};
    EXPECT_EQ(StringUtils::Split("Hello\tWorldly\tWorms"), result4);

    std::vector<std::string> result5{"Hello", "Worldly", "Worms"};
    EXPECT_EQ(StringUtils::Split("Hello\nWorldly\nWorms"), result5);

    std::vector<std::string> result6{"Hello", "Worldly", "Worms"};
    EXPECT_EQ(StringUtils::Split("Hello\rWorldly\rWorms"), result6);

    std::vector<std::string> result7{"Hello", "Worldly", "Worms"};
    EXPECT_EQ(StringUtils::Split("Hello\vWorldly\vWorms"), result7);

    std::vector<std::string> result8{"Hello", "Worldly", "Worms"};
    EXPECT_EQ(StringUtils::Split("Hello\fWorldly\fWorms"), result8);

    std::vector<std::string> result9{"", "Hello", "Worldly", "Worms"};
    EXPECT_EQ(StringUtils::Split(" Hello Worldly Worms"), result9);

    std::vector<std::string> result2{"Hello Worldly Worms"};
    EXPECT_EQ(StringUtils::Split("Hello Worldly Worms", "z"), result2);

    std::vector<std::string> result3{"He", "", "o Wor", "d", "y Worms"};
    EXPECT_EQ(StringUtils::Split("Hello Worldly Worms", "l"), result3);
}

TEST(StringUtilsTest, Join){
    std::vector<std::string> input1{"Hello", "Wriggly", "Worms"};
    EXPECT_EQ(StringUtils::Join(" ", input1), std::string("Hello Wriggly Worms"));

    std::vector<std::string> input2{"Hello", "Wriggly", "Worms"};
    EXPECT_EQ(StringUtils::Join("", input2), std::string("HelloWrigglyWorms"));

    std::vector<std::string> input3{"Worms"};
    EXPECT_EQ(StringUtils::Join("x", input3), std::string("Worms"));

    std::vector<std::string> input4{"Hello", "Wriggly", "Worms"};
    EXPECT_EQ(StringUtils::Join("x", input4), std::string("HelloxWrigglyxWorms"));
}

TEST(StringUtilsTest, ExpandTabs){
    EXPECT_EQ(StringUtils::ExpandTabs("Hello\tWorld"), std::string("Hello   World"));
    EXPECT_EQ(StringUtils::ExpandTabs("He\tll\to \tWo\trl\td", 2), std::string("He  ll  o   Wo  rl  d"));
    EXPECT_EQ(StringUtils::ExpandTabs("\tHello\tWorld", 0), std::string("HelloWorld"));    
}

TEST(StringUtilsTest, EditDistance){
    EXPECT_EQ(StringUtils::EditDistance("Hello", ""), 5);
    EXPECT_EQ(StringUtils::EditDistance("", "World"), 5);
    EXPECT_EQ(StringUtils::EditDistance("Hello", "Hello"), 0);
    EXPECT_EQ(StringUtils::EditDistance("Hello", "hellO", true), 0);
    EXPECT_EQ(StringUtils::EditDistance("Hello", "Hi"), 4);
    EXPECT_EQ(StringUtils::EditDistance("Helllo", "Hello"), 1);
    EXPECT_EQ(StringUtils::EditDistance("HeLlo", "Hello"), 1);
    EXPECT_EQ(StringUtils::EditDistance("Helo", "Hello"), 1);
    EXPECT_EQ(StringUtils::EditDistance("Hello", "Beluga"), 4);
    EXPECT_EQ(StringUtils::EditDistance("Hello", "Wormfood"), 7);
}
