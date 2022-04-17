#ifndef WINGMANN_BIG_INTEGER_H
#define WINGMANN_BIG_INTEGER_H

#include <string>
#include <cmath>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <vector>
#include <cctype>

/**
* big_integer C++ implementation
*/
class big_integer {
    int radix_{10};
    bool signed_{};
    std::string value_{"0"};

public:
    big_integer() = default;
    big_integer(int value);
    big_integer(long long value);
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
    [[nodiscard]] big_integer add(const big_integer& bi) const;
    [[nodiscard]] big_integer subtract(const big_integer& bi) const;
    [[nodiscard]] big_integer multiply(const big_integer& bi) const;
    [[nodiscard]] big_integer divide(const big_integer& bi) const;

    // Complex arithmetic.
    [[nodiscard]] big_integer pow(const big_integer& bi) const;
    [[nodiscard]] big_integer modulus(const big_integer& bi) const;

    // Modification and checking.
    [[nodiscard]] size_type bit_length() const;
    [[nodiscard]] int compare(const big_integer& bi) const;

    [[nodiscard]] big_integer negate() const;
    [[nodiscard]] big_integer absolute() const;

    [[nodiscard]] bool is_positive() const;
    [[nodiscard]] bool is_negative() const;

    void swap(big_integer& bi);

    // Operators.
    big_integer operator+(const big_integer& bi);
    big_integer operator-(const big_integer& bi);
    big_integer operator*(const big_integer& bi);
    big_integer operator/(const big_integer& bi);
    big_integer operator%(const big_integer& bi);

    big_integer operator<<(const big_integer& bi) const;
    big_integer operator>>(const big_integer& bi) const;

    big_integer& operator+=(const big_integer& bi);
    big_integer& operator-=(const big_integer& bi);
    big_integer& operator*=(const big_integer& bi);
    big_integer& operator/=(const big_integer& bi);

    big_integer& operator--();
    const big_integer operator--(int);
    big_integer& operator++();
    const big_integer operator++(int);

    bool operator==(const big_integer& bi) const;
    bool operator!=(const big_integer& bi) const;
    bool operator<(const big_integer& bi) const;
    bool operator>(const big_integer& bi) const;
    bool operator<=(const big_integer& bi) const;
    bool operator>=(const big_integer& bi) const;

    friend std::ostream& operator<<(std::ostream& stream, const big_integer& bi)
    {
        stream << bi.to_string();
        return stream;
    }

    [[nodiscard]] std::string to_string(int radix = 10) const;
};

#endif // WINGMANN_BIG_INTEGER_H
