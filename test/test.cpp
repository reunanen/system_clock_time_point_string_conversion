//               Copyright 2017 Juha Reunanen
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "../system_clock_time_point_string_conversion.h"
#include <gtest/gtest.h>

void convert_back_and_forth(const std::string& time_string)
{
    const auto time_point = system_clock_time_point_string_conversion::from_string(time_string);

    const std::string time_string_converted = system_clock_time_point_string_conversion::to_string(time_point);

    std::string time_string_expected = time_string;
    if (time_string_expected.length() < 20) {
        time_string_expected += '.';
    }
    while (time_string_expected.length() < 26) {
        time_string_expected += '0';
    }

    EXPECT_EQ(time_string_converted, time_string_expected);
}

TEST(test, convert_no_fraction_of_second)
{
    convert_back_and_forth("2017-02-27T11:22:33");
    convert_back_and_forth("2017-02-27T11:22:33.");
}

TEST(test, convert_milliseconds)
{
    convert_back_and_forth("2017-02-27T11:22:33.444");
}

TEST(test, convert_microseconds)
{
    convert_back_and_forth("2017-02-27T11:22:33.444444");
}

TEST(test, convert_irregular)
{
    convert_back_and_forth("2017-02-27T11:22:33.4");
    convert_back_and_forth("2017-02-27T11:22:33.44");
    convert_back_and_forth("2017-02-27T11:22:33.4444");
    convert_back_and_forth("2017-02-27T11:22:33.44444");
}

TEST(test, convert_leap_day)
{
    convert_back_and_forth("2016-02-29T11:22:33");
}

TEST(test, try_invalid)
{
    EXPECT_THROW(convert_back_and_forth("asdf"), std::exception);
}

TEST(test, try_unsupported)
{
    EXPECT_THROW(convert_back_and_forth("2017-02-27T11:22:33.4444444"), std::exception);
}
