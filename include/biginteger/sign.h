#ifndef WINGMANN_BIGINTEGER_TYPE_SIGN_H
#define WINGMANN_BIGINTEGER_TYPE_SIGN_H

namespace wingmann::numerics {

enum class SignFlag {
    positive = 0,
    negative = 1
};

struct Sign {
    /**
     * @brief Flag of sign.
     */
    SignFlag value;

public:
    /**
     * @brief Default constructor.
     */
    Sign() = delete;

    /**
     * @brief Constructs from sign flag.
     * @param flag Sign flag value.
     */
    explicit Sign(SignFlag flag) : value{flag} { }

public:
    /**
     * @brief Checks if the flag is positive.
     */
    [[nodiscard]]
    bool isPositive() const { return value == SignFlag::positive; }

    /**
     * @brief Checks if the flag is negative.
     */
    [[nodiscard]]
    bool isNegative() const { return !isPositive(); }

    /**
     * @brief Inverts the value of the flag.
     */
    void reverse() { value = isPositive() ? SignFlag::negative : SignFlag::positive; }
};

} // namespace wingmann::numerics

#endif // WINGMANN_BIGINTEGER_TYPE_SIGN_H
