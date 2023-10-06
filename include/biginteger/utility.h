#ifndef ALEF_NUMERICS_BIGINTEGER_UTILITY_H
#define ALEF_NUMERICS_BIGINTEGER_UTILITY_H

#include "radix.h"
#include "sign.h"

#include <algorithm>
#include <ranges>

namespace wingmann::numerics::__detail {

// Checks for value is valid.
static bool isValidNumber(const std::string& value, RadixFlag radix) {
    std::pair range{'0', '9'};

    if (radix == RadixFlag::Binary) {
        range.second = '1';
    } else if (radix == RadixFlag::Octal) {
        range.second = '7';
    } else if (radix == RadixFlag::Hexadecimal) {
        range.second = 'F';
    }
    return std::ranges::all_of(value, [=](const auto c) {
        return c >= range.first && c <= range.second;
    });
}

// Removes first char if its sign.
static void removeSign(std::string& value) {
    value.erase(0, 1);
}

// Removes leading not significant zeros.
static void removeLeadingZeros(std::string& value) {
    while (value.starts_with('0') && (value.length() != 1)) {
        value.erase(0, 1);
    }
}

static constexpr auto charToInt32 = [](const char value) {
    auto number{static_cast<int>(value)};
    return std::isdigit(value) ? (number - 0x30) : (std::tolower(number - 0x61) + 0xA);
};

} // namespace wingmann::numerics::__detail

#endif // ALEF_NUMERICS_BIGINTEGER_UTILITY_H
