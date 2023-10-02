#ifndef WINGMANN_BIGINTEGER_TYPE_RADIX_H
#define WINGMANN_BIGINTEGER_TYPE_RADIX_H

#include <string>

namespace wingmann::numerics {

/// @brief The base of a system of number.
enum class radix_flag {
    binary      = 2,
    octal       = 8,
    decimal     = 10,
    hexadecimal = 16
};

/// @brief Radix type.


struct radix {
    radix_flag value;

public:
    /// @brief Deleted default constructor.
    radix() = delete;

    /// @brief Constructs from radix flag.
    /// @param value Radix flag.
    ///
    explicit radix(radix_flag flag) : value{flag} { }
};

// Returns the base char values of a system of number.
static constexpr auto base_chars(radix_flag radix) {
    std::string value{"0123456789ABCDEF"};

    switch (radix) {
        case radix_flag::binary:
            return value.substr(0, 2);
        case radix_flag::octal:
            return value.substr(0, 8);
        case radix_flag::hexadecimal:
            return value.substr(0, 16);
        default:
            return value.substr(0, 10);
    }
}

} // namespace wingmann::numerics

#endif // WINGMANN_BIGINTEGER_TYPE_RADIX_H
