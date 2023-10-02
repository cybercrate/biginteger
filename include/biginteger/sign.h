#ifndef WINGMANN_BIGINTEGER_TYPE_SIGN_H
#define WINGMANN_BIGINTEGER_TYPE_SIGN_H

namespace wingmann::numerics {

enum class sign_flag {
    positive = 0,
    negative = 1
};

struct sign {
    /// @brief Flag of sign.
    sign_flag value;

public:
    /// @brief Default constructor.
    sign() = delete;

    /// @brief Constructs from sign flag.
    /// @param flag Sign flag value.
    ///
    explicit sign(sign_flag flag) : value{flag} { }

public:
    /// @brief Checks if the flag is positive.
    [[nodiscard]]
    bool is_positive() const { return value == sign_flag::positive; }

    /// @brief Checks if the flag is negative.
    [[nodiscard]]
    bool is_negative() const { return !is_positive(); }

    /// @brief Inverts the value of the flag.
    void reverse() { value = is_positive() ? sign_flag::negative : sign_flag::positive; }
};

} // namespace wingmann::numerics

#endif // WINGMANN_BIGINTEGER_TYPE_SIGN_H
