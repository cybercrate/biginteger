#ifndef WINGMANN_BIGINTEGER_TYPE_RADIX_H
#define WINGMANN_BIGINTEGER_TYPE_RADIX_H

#include <string>

namespace wingmann::numerics {

/**
 * @brief The base of a system of number.
 */
enum class RadixFlag {
    Binary      = 2,
    Octal       = 8,
    Decimal     = 10,
    Hexadecimal = 16
};

/**
 * @brief Radix type.
 */
struct Radix {
    RadixFlag value;

public:
    /**
     * @brief Deleted default constructor.
     */
    Radix() = delete;

    /**
     * @brief Constructs from Radix flag.
     * @param flag Radix flag.
     */
    explicit Radix(RadixFlag flag) : value{flag} { }
};

// Returns the base char values of a system of number.
static constexpr auto baseChars(RadixFlag radix) {
    std::string value{"0123456789ABCDEF"};

    switch (radix) {
        case RadixFlag::Binary:
            return value.substr(0, 2);
        case RadixFlag::Octal:
            return value.substr(0, 8);
        case RadixFlag::Hexadecimal:
            return value.substr(0, 16);
        default:
            return value.substr(0, 10);
    }
}

} // namespace wingmann::numerics

#endif // WINGMANN_BIGINTEGER_TYPE_RADIX_H
