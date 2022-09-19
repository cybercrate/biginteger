#ifndef WINGMANN_BIGINTEGER_H
#define WINGMANN_BIGINTEGER_H

#include <string>
#include <cmath>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <vector>
#include <cctype>

namespace wingmann::numerics {

class big_integer {
    int radix_{10};
    bool signed_{};
    std::string value_{"0"};

public:
    big_integer() = default;
    big_integer(std::int32_t value);
    big_integer(std::int64_t value);
    big_integer(std::string value, int radix = 10);

    virtual ~big_integer() = default;

public:
    static const big_integer zero_value;
    static const big_integer one_value;
    static const big_integer ten_value;
    static const std::string base_char_value;

    using size_type = std::size_t;

public:
    // Basic arithmetic.
    [[nodiscard]]
    big_integer add(const big_integer& value) const;

    [[nodiscard]]
    big_integer subtract(const big_integer& value) const;

    [[nodiscard]]
    big_integer multiply(const big_integer& value) const;

    [[nodiscard]]
    big_integer divide(const big_integer& value) const;

    // Complex arithmetic.
    [[nodiscard]]
    big_integer pow(const big_integer& value) const;

    [[nodiscard]]
    big_integer modulus(const big_integer& value) const;

    // Modification and checking.
    [[nodiscard]]
    size_type bit_length() const;

    [[nodiscard]]
    int compare(const big_integer& value) const;

    [[nodiscard]]
    big_integer negate() const;

    [[nodiscard]]
    big_integer absolute() const;

    [[nodiscard]]
    bool is_positive() const;

    [[nodiscard]]
    bool is_negative() const;

    void swap(big_integer& bi);

    // Operators.
    big_integer operator+(const big_integer& value);
    big_integer operator-(const big_integer& value);
    big_integer operator*(const big_integer& value);
    big_integer operator/(const big_integer& value);
    big_integer operator%(const big_integer& value);

    big_integer operator<<(const big_integer& value) const;
    big_integer operator>>(const big_integer& value) const;

    big_integer& operator+=(const big_integer& value);
    big_integer& operator-=(const big_integer& value);
    big_integer& operator*=(const big_integer& value);
    big_integer& operator/=(const big_integer& value);

    big_integer& operator--();
    const big_integer operator--(int);
    big_integer& operator++();
    const big_integer operator++(int);

    bool operator==(const big_integer& value) const;
    bool operator!=(const big_integer& value) const;
    bool operator<(const big_integer& value) const;
    bool operator>(const big_integer& value) const;
    bool operator<=(const big_integer& value) const;
    bool operator>=(const big_integer& value) const;

    friend std::ostream& operator<<(std::ostream& os, const big_integer& value);

    [[nodiscard]]
    std::string to_string(int radix = 10) const;
};

} // namespace wingmann::numerics

#endif // WINGMANN_BIGINTEGER_H
