#include "gtest/gtest.h"
#include "point.h"
#include "exception.h"

using namespace rela;

TEST(point_test, base_test)
{
    constexpr point temp1(5, 5);
    constexpr point temp2(-5, -5);

    EXPECT_FALSE(temp1 == temp2);
    EXPECT_TRUE(temp1 != temp2);

    constexpr point mid_point = temp1 + temp2;
    EXPECT_EQ(mid_point, point(0,0));

    EXPECT_EQ(-temp1, temp2);

    EXPECT_EQ(point(0,0).distance(), 0);
    EXPECT_EQ(point(1,0).distance(), 1);
    EXPECT_EQ(point(0,1).distance(), 1);
    EXPECT_EQ(point(-1,0).distance(), 1);
    EXPECT_EQ(point(0,-1).distance(), 1);

    EXPECT_EQ(temp2.abs(), temp1);
    EXPECT_EQ(temp1.abs(), temp1);
}

TEST(point_test, str_test)
{
    point temp1;
    std::string str1 = "(1,2)";
    EXPECT_EQ(temp1.from_string(str1), point(1,2));
    EXPECT_EQ(point::from_string(str1).to_string(), str1);

    std::string str2 = "qweasdasdasdfd";
    EXPECT_THROW(temp1.from_string(str2), stream_to_point_error);
}