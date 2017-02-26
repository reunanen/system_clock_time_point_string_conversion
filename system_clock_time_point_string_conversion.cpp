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

    std::string to_string(const std::chrono::system_clock::time_point& time_point, char dateTimeSeparator)
    {
        std::ostringstream oss;

        const time_t t = std::chrono::system_clock::to_time_t(time_point);

        const char* put_time_format = "%Y-%m-%d %X";

#ifdef _MSC_VER
        std::tm tm;
        gmtime_s(&tm, &t);
        oss << std::put_time(&tm, put_time_format);
#else
        oss << std::put_time(std::gmtime(&t), put_time_format);
#endif

        // TODO: support even other resolutions
        const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(time_point - std::chrono::system_clock::from_time_t(t)).count();

        assert(microseconds >= 0 && microseconds < 1e6);

        oss << "." << std::setw(6) << std::setfill('0') << microseconds;

        std::string time_string = oss.str();

        assert(time_string[10] == ' ');

        if (dateTimeSeparator != ' ') {
            time_string[10] = dateTimeSeparator;
        }

        return time_string;
    }

    std::chrono::system_clock::time_point from_string(const std::string& time_string)
    {
        if (time_string.length() < 19) {
            throw std::runtime_error("Unexpected time string: length < 19");
        }

        if (time_string[4] != '-' || time_string[7] != '-' || time_string[13] != ':' || time_string[16] != ':') {
            throw std::runtime_error("Unexpected time string format");
        }

        std::tm tm;

        tm.tm_wday = 0;
        tm.tm_yday = 0;
        tm.tm_year = std::stoi(time_string.substr(0, 4)) - 1900;
        tm.tm_mon = std::stoi(time_string.substr(5, 2)) - 1;
        tm.tm_mday = std::stoi(time_string.substr(8, 2));
        tm.tm_hour = std::stoi(time_string.substr(11, 2));
        tm.tm_min = std::stoi(time_string.substr(14, 2));
        tm.tm_sec = std::stoi(time_string.substr(17, 2));
        tm.tm_isdst = 0;

        const std::time_t t = _mkgmtime(&tm);

        std::chrono::system_clock::time_point time_point = std::chrono::system_clock::from_time_t(t);

        if (time_string.length() > 19) {
            if (time_string[19] != '.') {
                throw std::runtime_error("Unexpected time string format");
            }

            std::string fraction_of_seconds = time_string.substr(20);
            if (fraction_of_seconds.length() > 6) {
                throw std::runtime_error("Unexpectedly accurate fraction of seconds");
            }

            if (fraction_of_seconds.length() <= 3) {
                while (fraction_of_seconds.length() < 3) {
                    fraction_of_seconds += '0';
                }
                time_point = time_point + std::chrono::milliseconds(std::stoi(fraction_of_seconds));
            }
            else {
                while (fraction_of_seconds.length() < 6) {
                    fraction_of_seconds += '0';
                }
                time_point = time_point + std::chrono::microseconds(std::stoi(fraction_of_seconds));
            }
        }

        return time_point;
    }
}
