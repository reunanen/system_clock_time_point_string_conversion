//               Copyright 2017 Juha Reunanen
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "system_clock_time_point_string_conversion.h"

#include <sstream>
#include <iomanip>
#include <assert.h>

namespace system_clock_time_point_string_conversion {

    std::string to_string(const std::chrono::system_clock::time_point& time_point)
    {
        std::ostringstream oss;

        const time_t t = std::chrono::system_clock::to_time_t(time_point);
        oss << std::put_time(std::gmtime(&t), "%Y-%m-%d %X");

        // TODO: support even other resolutions
        const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time_point - std::chrono::system_clock::from_time_t(t)).count();

        assert(milliseconds >= 0 && milliseconds < 1000);

        oss << "." << std::setw(3) << std::setfill('0') << milliseconds;

        return oss.str();
    }

    // TODO!
    //std::chrono::system_clock::time_point from_string(const std::string& time_string)
    //{
    //    std::chrono::system_clock::time_point time_point;
    //    return time_point;
    //}

}
