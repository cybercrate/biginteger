#ifndef ALEF_NUMERICS_BIGINTEGER_UTILITY_H
#define ALEF_NUMERICS_BIGINTEGER_UTILITY_H

#include "alef/algo.h"
#include "alef/numerics/types.h"

ALEF_GLOBAL_NAMESPACE_BEGIN

namespace __detail::num {

// Checks for value is valid.
static bool is_valid_number(const std::string& value, alf::num::radix_flag radix) {
    std::pair range{'0', '9'};

    if (radix == alf::num::radix_flag::binary) {
        range.second = '1';
    } else if (radix == alf::num::radix_flag::octal) {
        range.second = '7';
    } else if (radix == alf::num::radix_flag::hexadecimal) {
        range.second = 'F';
    }
    return std::ranges::all_of(value, [=](const auto c) {
        return c >= range.first && c <= range.second;
    });
}

// Removes first char if its sign.
static void remove_sign(std::string& value) {
    value.erase(0, 1);
}

// Removes leading not significant zeros.
static void remove_leading_zeros(std::string& value) {
    while (value.starts_with('0') && (value.length() != 1)) {
        value.erase(0, 1);
    }
}

} // namespace __detail::num

ALEF_GLOBAL_NAMESPACE_END

#endif // ALEF_NUMERICS_BIGINTEGER_UTILITY_H
