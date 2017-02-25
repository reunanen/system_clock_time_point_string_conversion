//               Copyright 2017 Juha Reunanen
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SYSTEM_CLOCK_TIME_POINT_STRING_CONVERSION_H
#define SYSTEM_CLOCK_TIME_POINT_STRING_CONVERSION_H

#include <chrono>
#include <string>

namespace system_clock_time_point_string_conversion {

    std::string to_string(const std::chrono::system_clock::time_point& time_point);
    //std::chrono::system_clock::time_point from_string(const std::string& time_string);

}

#endif // SYSTEM_CLOCK_TIME_POINT_STRING_CONVERSION