/// @file   big_integer.h
/// @author Alexander Shavrov (alexander.shavrov@outlook.com)
/// @brief  Arbitrary large integer library.
/// @date   2022-09-28
/// 
/// @copyright Copyright (c) 2022
/// 
/// This file is distributed under the GNU GPL v3 License.
/// See LICENSE file for details.
///

#ifndef WINGMANN_BIGINTEGER_H
#define WINGMANN_BIGINTEGER_H

#include <algorithm>
#include <cmath>
#include <concepts>
#include <optional>
#include <ostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

namespace wingmann::numerics {

/// @brief Arbitrarily large integer.
class big_integer {
public:
    /// @brief The base of a system of number.
    enum class radix_type : std::uint8_t {
        binary = 2,
        octal = 8,
        decimal = 10,
        hexadecimal = 16
    };

protected:
    // The base of a system of number.
    radix_type radix_{radix_type::decimal};

    // Sign flag.
    bool signed_{};

    // String representation of decimal value.
    std::string value_{"0"};

public:
    /// @brief Default constructor.
    big_integer() = default;

    /// @brief Copy constructor.
    /// @param other Value to copy.
    ///
    big_integer(const big_integer& other) = default;

    /// @brief Move constructor.
    /// @param other Value to move.
    ///
    big_integer(big_integer&& other) noexcept
        : radix_{other.radix_}, signed_{other.signed_}, value_{std::move(other.value_)}
    {
        other.radix_ = radix_type::decimal;
        other.signed_ = false;
        other.value_ = "0";
    }

    /// @brief Destructor.
    virtual ~big_integer() = default;

    /// @brief Constructs from integral.
    /// @param value Integral value.
    ///
    template<typename T>
    requires std::integral<T> && (!std::same_as<T, bool>)
    big_integer(T value)
    {
        *this = std::to_string(value);
    }

    /// @brief Constructs from string literal.
    ///
    /// @param value String literal value.
    /// @param radix The base of a system of number.
    ///
    big_integer(const char* value, radix_type radix = radix_type::decimal) : radix_{radix}
    {
        *this = std::string{value};
    }

    /// @brief Constructs from string.
    ///
    /// @param value String value.
    /// @param radix The base of a system of number.
    ///
    big_integer(std::string value, radix_type radix = radix_type::decimal) : radix_{radix}
    {
        *this = std::move(value);
    }

    // Assignment operators ------------------------------------------------------------------------

    /// @brief Copy assignment operator.
    ///
    /// @param rhs Value to copy.
    /// @return    Constructed object.
    ///
    big_integer& operator=(const big_integer& rhs) & = default;

    /// @brief Move assignment operator.
    ///
    /// @param rhs Value to move.
    /// @return    Constructed object.
    ///
    big_integer& operator=(big_integer&& rhs) & noexcept
    {
        this->radix_ = rhs.radix_;
        this->signed_ = rhs.signed_;
        this->value_ = std::move(rhs.value_);

        rhs.radix_ = radix_type::decimal;
        rhs.signed_ = false;
        rhs.value_ = "0";

        return *this;
    }

    /// @brief Constructs from an integral rhs.
    ///
    /// @param rhs An integral rhs.
    /// @return    Constructed object.
    ///
    template<typename T>
    requires std::integral<T> && (!std::same_as<T, bool>)
    big_integer& operator=(T rhs) &
    {
        *this = std::to_string(rhs);
        return *this;
    }

    /// @brief Constructs from the string literal.
    ///
    /// @param rhs The string literal.
    /// @return    Constructed object.
    ///
    big_integer& operator=(const char* rhs) &
    {
        *this = std::string{rhs};
        return *this;
    }

    /// @brief Constructs from the string value.
    ///
    /// @param value The value from which to construct.
    /// @return      Constructed object.
    ///
    big_integer& operator=(std::string value) &
    {
        this->signed_ = value.starts_with('-');

        if (this->is_negative())
            remove_sign(value);

        if (!is_valid_number(value, this->radix_))
            throw std::invalid_argument("value in not valid");

        remove_leading_zeros(value);

        if (this->radix_ == radix_type::decimal)
            this->value_ = value;
        else
            this->value_ = convert_to_base_ten(value, this->radix_);

        return *this;
    }

    // Additional assignment operators -------------------------------------------------------------

    /// @brief Adds the right operand to the current value and assigns the result.
    ///
    /// @param rhs The value to add to the current value.
    /// @return    Modified object.
    ///
    big_integer& operator+=(const big_integer& rhs) &
    {
        *this = this->add(rhs);
        return *this;
    }

    /// @brief Subtracts the right operand from the current value and assigns the result.
    ///
    /// @param rhs The value to subtract from the current value.
    /// @return    Modified object.
    ///
    big_integer& operator-=(const big_integer& rhs) &
    {
        *this = this->subtract(rhs);
        return *this;
    }

    /// @brief Multiplies the current value by the right operand and assigns the result.
    ///
    /// @param rhs The value to multiply by current value.
    /// @return    Modified object.
    ///
    big_integer& operator*=(const big_integer& rhs) &
    {
        *this = this->multiply(rhs);
        return *this;
    }

    /// @brief Divides the current value by the right operand and assigns the result.
    ///
    /// @param rhs The value by which to divide the current value.
    /// @return    Modified object.
    ///
    big_integer& operator/=(const big_integer& rhs) &
    {
        *this = this->divide(rhs);
        return *this;
    }

    /// @brief Gets the remainder of the current value divided by the right operand
    /// and assigns the result.
    ///
    /// @param rhs The right operand for taking the remainder.
    /// @return    Modified object.
    ///
    big_integer& operator%=(const big_integer& rhs) &
    {
        *this = this->mod(rhs);
        return *this;
    }

    /// @brief Shifts the current value to left on right operand value and assigns the result.
    ///
    /// @param rhs The value to shift_right on.
    /// @return    Modified object.
    ///
    big_integer& operator<<=(const big_integer& rhs) &
    {
        *this = this->shift_left(rhs);
        return *this;
    }

    /// @brief Shifts the current value to left on right operand value and assigns the result.
    ///
    /// @param rhs The value to shift_right on.
    /// @return    Modified object.
    ///
    big_integer& operator>>=(const big_integer& rhs) &
    {
        *this = this->shift_right(rhs);
        return *this;
    }

    // Increment and decrement operators -----------------------------------------------------------

    /// @brief Increments the current value.
    /// @return Modified object.
    ///
    big_integer& operator++() &
    {
        *this = this->add(1);
        return *this;
    }

    /// @brief Increments the current value after returns copy.
    /// @return Copy of current value.
    ///
    big_integer operator++(int) &
    {
        auto temp{*this};
        ++(*this);
        return temp;
    }

    /// @brief Decrements the current value.
    /// @return Modified object.
    ///
    big_integer& operator--() &
    {
        *this = this->subtract(1);
        return *this;
    }

    /// @brief Decrements the current value after returns copy.
    /// @return Copy of current value.
    ///
    big_integer operator--(int) &
    {
        auto temp{*this};
        --(*this);
        return temp;
    }

    // Shift operations -----------------------------------------------------------------------------

    /// @brief Shifts the current value to left on right operand value.
    ///
    /// @param rhs The value to shift_right on.
    /// @return    Shifted current value.
    ///
    [[nodiscard]]
    big_integer shift_left(const big_integer& rhs) const
    {
        if (rhs.is_negative())
            throw std::invalid_argument("negative value");

        auto bitwise_value = this->to_string(radix_type::binary);

        for (auto i = 0; i < rhs; ++i)
            bitwise_value.push_back('0');

        return {std::move(bitwise_value), radix_type::binary};
    }

    /// @brief Shifts the current value to right on right operand value.
    ///
    /// @param rhs The value to shift_right on.
    /// @return    Shifted current value.
    ///
    [[nodiscard]]
    big_integer shift_right(const big_integer& rhs) const
    {
        if (rhs.is_negative())
            throw std::invalid_argument("negative value");

        auto bitwise_value = this->to_string(radix_type::binary);

        for (auto i = 0; (i < rhs) && (bitwise_value.length() > 0); ++i)
            bitwise_value.pop_back();

        if (bitwise_value.empty())
            bitwise_value.push_back('0');

        return {std::move(bitwise_value), radix_type::binary};
    }

    // Shift operators -----------------------------------------------------------------------------

    /// @brief Shifts the current value to left on right operand value.
    ///
    /// @param rhs The value to shift_right on.
    /// @return    Shifted current value.
    ///
    big_integer operator<<(const big_integer& rhs) const
    {
        return this->shift_left(rhs);
    }

    /// @brief Shifts the current value to right on right operand value.
    ///
    /// @param rhs The value to shift_right on.
    /// @return    Shifted current value.
    ///
    big_integer operator>>(const big_integer& rhs) const
    {
        return this->shift_right(rhs);
    }

    // Comparison ----------------------------------------------------------------------------------

    /// @brief Three way compares the current value and right side operand.
    ///
    /// @param rhs The value to compere with the current value.
    /// @return    Result of comparison.
    ///
    [[nodiscard]]
    std::strong_ordering compare(const big_integer& rhs) const
    {
        // -a, +b
        if (this->is_negative() && rhs.is_positive())
            return std::strong_ordering::less;

        // +a, -b
        if (this->is_positive() && rhs.is_negative())
            return std::strong_ordering::greater;

        // -a, -b
        if (this->is_negative() && rhs.is_negative()) {
            if (this->value_.length() == rhs.value_.length()) {
                if (this->value_ > rhs.value_)
                    return std::strong_ordering::less;

                return (this->value_ == rhs.value_)
                    ? std::strong_ordering::equivalent
                    : std::strong_ordering::greater;
            }
            return (this->value_.length() < rhs.value_.length())
                ? std::strong_ordering::greater
                : std::strong_ordering::less;
        }

        // +a, +b
        if (this->value_.length() == rhs.value_.length()) {
            if (this->value_ > rhs.value_)
                return std::strong_ordering::greater;

            return (this->value_ == rhs.value_)
                ? std::strong_ordering::equivalent
                : std::strong_ordering::less;
        }
        return (this->value_.length() < rhs.value_.length())
            ? std::strong_ordering::less
            : std::strong_ordering::greater;
    }

    /// @brief Compares the current value and right side operand.
    ///
    /// @param rhs The value to compare with the current value.
    /// @return    Result of comparison.
    ///
    [[nodiscard]]
    bool equal(const big_integer& rhs) const
    {
        return this->compare(rhs) == std::strong_ordering::equivalent;
    }

    // Comparison operators ------------------------------------------------------------------------

    /// @brief Three way compares the current value and right side operand.
    ///
    /// @param rhs The value to compere with the current value.
    /// @return    Result of comparison.
    ///
    std::strong_ordering operator<=>(const big_integer& rhs) const
    {
        return this->compare(rhs);
    }

    /// @brief Compares the current value and right side operand.
    ///
    /// @param rhs The value to compare with the current value.
    /// @return    Result of comparison.
    ///
    auto operator==(const big_integer& rhs) const
    {
        return this->equal(rhs);
    }

    // Basic arithmetic ----------------------------------------------------------------------------

    /// @brief Adds value.
    ///
    /// @param rhs The right side operand for addition to current value.
    /// @return    Result of addition.
    ///
    [[nodiscard]]
    big_integer add(const big_integer& rhs) const
    {
        // (-a)+(+b)
        if (this->is_negative() && rhs.is_positive())
            return rhs.subtract(this->negate());

        // (+a)+(-b)
        if (this->is_positive() && rhs.is_negative())
            return this->subtract(rhs.negate());

        // (+a)+(+b) or (-a)+(-b)
        auto lhs_value = this->value_;
        auto rhs_value = rhs.value_;

        auto diff_length = std::abs(static_cast<int>(lhs_value.length() - rhs_value.length()));

        const auto min_value{'0'};
        const auto max_value{'9'};

        if (lhs_value.length() > rhs_value.length())
            rhs_value.insert(0, diff_length, min_value);
        else
            lhs_value.insert(0, diff_length, min_value);

        std::ranges::reverse(lhs_value);
        std::ranges::reverse(rhs_value);

        std::size_t index{};
        char carry{min_value};

        for (char& lhs_char : lhs_value) {
            lhs_char = static_cast<char>(
                (carry - min_value) + (lhs_char - min_value) + (rhs_value.at(index) - min_value) +
                min_value);

            if (lhs_char > max_value) {
                lhs_char -= 10;
                carry = (min_value + 1);
            }
            else {
                carry = min_value;
            }
            ++index;
        }

        if (carry > min_value)
            lhs_value.append(1, carry);

        std::ranges::reverse(lhs_value);

        return this->is_negative() ? value_from(lhs_value).negate() : std::move(lhs_value);
    }

    /// @brief Subtracts value.
    ///
    /// @param rhs The right side operand for subtract from current value.
    /// @return    Result of subtraction.
    ///
    [[nodiscard]]
    big_integer subtract(const big_integer& rhs) const
    {
        // (-a)-(+b) or (+a)-(-b)
        if ((this->is_negative() && rhs.is_positive()) ||
            (this->is_positive() && rhs.is_negative()))
        {
            return this->add(rhs.negate());
        }

        // (+a)-(+b) or (-a)-(-b)
        if (this->is_negative())
            return this->add(rhs.negate());

        bool inverted_sign = (this->compare(rhs) == std::strong_ordering::less);

        std::string subtracted = inverted_sign ? rhs.value_ : this->value_;
        std::string removed = inverted_sign ? this->value_ : rhs.value_;

        auto diff_length = std::abs(static_cast<int>(subtracted.length() - removed.length()));

        const auto min_value{'0'};

        if (subtracted.size() > removed.size())
            removed.insert(0, diff_length, min_value);
        else
            subtracted.insert(0, diff_length, min_value);

        std::ranges::reverse(subtracted);
        std::ranges::reverse(removed);

        std::size_t index{};

        for (char& symbol : subtracted) {
            if (symbol < removed.at(index)) {
                symbol += 10;
                --subtracted.at(index + 1);
            }
            symbol = static_cast<char>(
                (symbol - min_value) - (removed.at(index) - min_value) + min_value);

            ++index;
        }
        std::ranges::reverse(subtracted);

        while (subtracted.front() == min_value && subtracted.length() != 1)
            subtracted.erase(0, 1);

        return inverted_sign ? value_from(subtracted).negate() : std::move(subtracted);
    }

    /// @brief Multiplies value.
    ///
    /// @param rhs The right operand for multiplication by the current value.
    /// @return    Result of multiplication.
    ///
    [[nodiscard]]
    big_integer multiply(const big_integer& rhs) const
    {
        auto lhs_value = this->value_;
        auto rhs_value = rhs.value_;

        std::ranges::reverse(lhs_value);
        std::ranges::reverse(rhs_value);

        const auto min_value{'0'};
        const auto max_value{'9'};

        int index{};
        char carry{min_value};

        auto temp = value_from(0);

        for (const auto& lhs_char : lhs_value) {
            auto operation = std::string{}.insert(0, index, min_value);

            for (const auto& rhs_char : rhs_value) {
                std::uint8_t result = ((lhs_char - min_value) * (rhs_char - min_value)) +
                                      (carry - min_value) + min_value;
                carry = min_value;

                if (result > max_value) {
                    while (result > max_value) {
                        result -= 10;
                        ++carry;
                    }
                }
                operation.insert(0, 1, static_cast<char>(result));
            }

            if (carry > min_value) {
                operation.insert(0, 1, carry);
                carry = min_value;
            }
            temp += operation;
            ++index;
        }
        auto positive = (this->is_negative() && rhs.is_negative()) ||
                        (this->is_positive() && rhs.is_positive());

        return positive ? std::move(temp) : temp.negate();
    }

    /// @brief Divides value.
    ///
    /// @param rhs The right operand by which to divide the current value.
    /// @return    Result of division.
    ///
    [[nodiscard]]
    big_integer divide(const big_integer& rhs) const
    {
        if (rhs.equal(0))
            throw std::invalid_argument("divide by zero");

        if (rhs.equal(1))
            return *this;

        if (this->equal(rhs))
            return 1;

        auto lhs_value = this->value_;
        std::ranges::reverse(lhs_value);

        auto rhs_abs = rhs.abs();

        std::string lhs_quotient;
        std::string rhs_quotient;

        do {
            lhs_quotient.push_back(lhs_value.back());
            lhs_value.pop_back();

            big_integer dividend_value{lhs_quotient};

            if (dividend_value < rhs_abs) {
                rhs_quotient.push_back('0');
                continue;
            }
            auto number= value_from(2);

            while (rhs_abs.multiply(number) <= dividend_value)
                ++number;

            --number;
            rhs_quotient.append(number.to_string());
            lhs_quotient = dividend_value.subtract(rhs_abs.multiply(number)).to_string();
        } while (!lhs_value.empty());

        bool positive = (this->is_negative() && rhs.is_negative()) ||
                        (this->is_positive() && rhs.is_positive());

        return positive ? std::move(rhs_quotient) : value_from(rhs_quotient).negate();
    }

    /// @brief Computes remainder.
    ///
    /// @param rhs The right operand for taking the remainder.
    /// @return    Remainder of division current value by right side value.
    ///
    [[nodiscard]]
    big_integer mod(const big_integer& rhs) const
    {
        if (rhs.equal(0))
            throw std::invalid_argument("mod by zero");

        return this->subtract(rhs.multiply(this->divide(rhs)));
    }

    // Arithmetic operators ------------------------------------------------------------------------

    /// @brief Adds value.
    ///
    /// @param rhs The right operand.
    /// @return    Result of addition.
    ///
    big_integer operator+(const big_integer& rhs) const
    {
        return this->add(rhs);
    }

    /// @brief Subtracts value.
    ///
    /// @param rhs The right operand.
    /// @return    Result of subtraction.
    ///
    big_integer operator-(const big_integer& rhs) const
    {
        return this->subtract(rhs);
    }

    /// @brief Multiples value.
    ///
    /// @param rhs The right operand.
    /// @return    Result of multiplication.
    ///
    big_integer operator*(const big_integer& rhs) const
    {
        return this->multiply(rhs);
    }

    /// @brief Divides value.
    ///
    /// @param rhs The right operand.
    /// @return    Result of division.
    ///
    big_integer operator/(const big_integer& rhs) const
    {
        return this->divide(rhs);
    }

    /// @brief Computes remainder.
    ///
    /// @param rhs The right operand.
    /// @return    Remainder of division current value by right side value.
    ///
    big_integer operator%(const big_integer& rhs) const
    {
        return this->mod(rhs);
    }

    // Complex arithmetic --------------------------------------------------------------------------

    /// @brief Reverses the sign.
    /// @return If current value signed then current value otherwise sign reversed.
    ///
    [[nodiscard]]
    big_integer negate() const
    {
        if (this->equal(0))
            return *this;

        if (this->is_negative())
            return this->value_;

        std::stringstream ss;
        ss << '-' << this->value_;
        
        return ss.str();
    }

    /// @brief Absolutes the current value.
    /// @return Unsigned current value.
    ///
    [[nodiscard]]
    big_integer abs() const
    {
        return this->is_positive() ? *this : this->negate();
    }

    /// @brief Rises the current value to the power of the right operand.
    ///
    /// @param rhs Degree.
    /// @return    Current value raised to the power.
    ///
    [[nodiscard]]
    big_integer pow(const big_integer& rhs) const
    {
        if (rhs.equal(0))
            return 1;

        if (this->equal(0))
            return 0;

        if (rhs.compare(0) == std::strong_ordering::less)
            return this->abs().equal(1) ? *this : 0;

        auto init_exp{rhs};
        auto result{*this};
        auto result_odd = value_from(1);

        while (init_exp.compare(1) == std::strong_ordering::greater) {
            if (init_exp.mod(2))
                result_odd *= result;

            result *= result;
            init_exp /= 2;
        }
        return result.multiply(result_odd);
    }

    /// @brief Rises the exponent value to the power of 10
    /// @return Current value raised to the power.
    ///
    [[nodiscard]]
    big_integer pow10() const
    {
        return value_from(10).pow(*this);
    }

    /// @brief Computes square root.
    /// @return Square root of current value.
    ///
    [[nodiscard]]
    big_integer sqrt() const
    {
        if (this->compare(0) == std::strong_ordering::less)
            throw std::invalid_argument("sqrt of a negative value");

        // Small numbers optimisation.
        if (this->equal(0))
            return 0;

        if (this->compare(4) == std::strong_ordering::less)
            return 1;

        if (this->compare(9) == std::strong_ordering::less)
            return 2;

        if (this->compare(16) == std::strong_ordering::less)
            return 3;

        auto previous = value_from(-1);
        auto current = value_from(this->to_string().size() / 2 - 1).pow10();

        while (current.subtract(previous).abs().compare(1) == std::strong_ordering::greater) {
            previous = current;
            current = this->divide(previous).add(previous).divide(2);
        }
        return current;
    }

    /// @brief Computes the greatest common divisor.
    ///
    /// @param rhs The right operand.
    /// @return    Greatest common divisor of the current value and right operand.
    ///
    [[nodiscard]]
    big_integer gcd(const big_integer& rhs) const
    {
        auto lhs_abs = this->abs();
        auto rhs_abs = rhs.abs();

        if (rhs_abs.equal(0) || lhs_abs.equal(0))
            return 0;

        auto remainder{rhs_abs};

        while (!remainder.equal(0)) {
            remainder = lhs_abs.mod(rhs_abs);
            lhs_abs = rhs_abs;
            rhs_abs = remainder;
        }
        return lhs_abs;
    }

    /// @brief Computes the least common multiple.
    ///
    /// @param rhs The right operand.
    /// @return    Least common multiple of the current value and right operand.
    ///
    [[nodiscard]]
    big_integer lcm(const big_integer& rhs) const
    {
        if (this->equal(0) || rhs.equal(0))
            return 0;

        return this->multiply(rhs).abs().divide(this->gcd(rhs));
    }

    // Modification and checking -------------------------------------------------------------------

    /// @brief Checks for current value is power of 10.
    /// @return If is power of 10 true otherwise false.
    ///
    bool is_pow10()
    {
        return (this->value_.at(0) == '1') && std::ranges::all_of(
                this->value_.cbegin() + 1,
                this->value_.cend(),
                [](const auto c) { return c == '0'; });
    }

    /// @brief Gets the binary size.
    /// @return Bit length of current value.
    ///
    [[nodiscard]]
    std::size_t bit_length() const
    {
        return to_string(radix_type::binary).length();
    }

    /// @brief Checks for value sign.
    /// @return If value unsigned then true otherwise false.
    ///
    [[nodiscard]]
    bool is_positive() const
    {
        return !this->signed_;
    }

    /// @brief Checks for value sign.
    /// @return If value signed true otherwise false.
    ///
    [[nodiscard]]
    bool is_negative() const
    {
        return this->signed_;
    }

    /// @brief Swaps values.
    /// @param rhs The value to swap with the current value.
    ///
    void swap(big_integer& rhs)
    {
        if (this->equal(rhs))
            return;

        std::swap(*this, rhs);
    }

    // Stream operators ----------------------------------------------------------------------------

    /// @brief Puts the value to the output stream.
    ///
    /// @param os    The output stream.
    /// @param value The value to put to output.
    /// @return      Output stream.
    ///
    friend std::ostream& operator<<(std::ostream& os, const big_integer& value)
    {
        os << value.to_string();
        return os;
    }

    /// @brief Gets the value from input stream.
    ///
    /// @param is    Input stream.
    /// @param value The value for writing from input stream.
    /// @return      Input stream.
    ///
    friend std::istream& operator>>(std::istream& is, big_integer& value)
    {
        std::string input;
        is >> input;
        value = input;
        return is;
    }

    // Conversion methods --------------------------------------------------------------------------

    /// @brief Creates value from integral value.
    ///
    /// @tparam value Integral value.
    /// @return       Constructed value.
    ///
    template<typename T>
    requires std::integral<T> && (!std::same_as<T, bool>)
    static big_integer value_from(T value)
    {
        return std::to_string(value);
    }

    /// @brief Creates value from string value.
    ///
    /// @tparam value String value.
    /// @return       Constructed value.
    ///
    static big_integer value_from(std::string value)
    {
        return std::move(value);
    }

    /// @brief Converts to boolean representation.
    /// @return Boolean representation of current value.
    ///
    explicit operator bool() const
    {
        return !this->equal(0);
    }

protected:
    // Safely converts to integral value.
    template<typename T>
    requires std::signed_integral<T> && (!std::same_as<T, bool>)
    std::optional<T> safe_convert(
            radix_type radix,
            T (* func)(const std::string&, std::size_t*, int)) const
    {
        try {
            return func(this->to_string(radix), nullptr, static_cast<int>(radix));
        }
        catch (std::invalid_argument&) { }
        catch (std::out_of_range&) { }

        return std::nullopt;
    }

public:
    /// @brief Converts to integral value.
    ///
    /// @tparam T    An integral type.
    /// @param radix The base of a system of number.
    /// @return      If converted, then integral value otherwise std::nullopt
    ///
    template<typename T>
    requires std::signed_integral<T> && (!std::same_as<T, bool>)
    std::optional<T> to_integer(radix_type radix = radix_type::decimal) const;

    template<>
    [[nodiscard]]
    std::optional<std::int8_t> to_integer(radix_type radix) const = delete;

    template<>
    [[nodiscard]]
    std::optional<std::int16_t> to_integer(radix_type radix) const = delete;

    /// @brief Converts to integral value.
    ///
    /// @tparam T    An integral type.
    /// @param radix The base of a system of number.
    /// @return      If converted, then integral value otherwise std::nullopt
    ///
    template<>
    [[nodiscard]]
    std::optional<int> to_integer(radix_type radix) const
    {
        return safe_convert(radix, std::stoi);
    }

    /// @brief Converts to integral value.
    ///
    /// @tparam T    An integral type.
    /// @param radix The base of a system of number.
    /// @return      If converted, then integral value otherwise std::nullopt
    ///
    template<>
    [[nodiscard]]
    std::optional<std::int64_t> to_integer(radix_type radix) const
    {
#if defined(__WORDSIZE) && __WORDSIZE == 64
        return safe_convert(radix, std::stol);
#else
        return safe_convert(radix, std::stoll);
#endif
    }

public:
    /// @brief Converts to string representation.
    ///
    /// @param radix The base of a system of number.
    /// @return      String representation of current value.
    ///
    [[nodiscard]]
    std::string to_string(radix_type radix = radix_type::decimal) const
    {
        std::stringstream ss;

        if (this->is_negative())
            ss << '-';

        if (radix == radix_type::decimal)
            ss << this->value_;
        else
            ss << convert_from_base_ten(*this, radix);

        return ss.str();
    }

private:
    // Checks for value is valid.
    static bool is_valid_number(const std::string& value, radix_type radix)
    {
        std::pair range{'0', '9'};

        if (radix == radix_type::binary)
            range.second = '1';
        else if (radix == radix_type::octal)
            range.second = '7';
        else if (radix == radix_type::hexadecimal)
            range.second = 'F';

        return std::ranges::all_of(value, [=](const auto c) {
            return c >= range.first && c <= range.second;
        });
    }

    // Removes first char if its sign.
    static void remove_sign(std::string& value)
    {
        value.erase(0, 1);
    }

    // Removes leading not significant zeros.
    static void remove_leading_zeros(std::string& value)
    {
        while (value.starts_with('0') && (value.length() != 1))
            value.erase(0, 1);
    }

    // Converts char to digit.
    static int char_to_digit(const char value)
    {
        return ('0' <= value) && (value <= '9')
            ? (value - '0')
            : (std::tolower(value) - 'a') + 10;
    }

    // Returns the base char values of a system of number.
    static std::string base_chars()
    {
        return "0123456789ABCDEF";
    }

    // Converts not base ten value to string.
    static std::string convert_from_base_ten(const big_integer& value, const radix_type radix)
    {
        auto decimal_value{value};
        auto modulo = value_from(static_cast<std::uint8_t>(radix));

        std::string result;

        while (!decimal_value.equal(0)) {
            auto remainder = decimal_value.mod(modulo);
            decimal_value /= modulo;

            auto c = base_chars().at(std::stoi(remainder.to_string()));
            result.push_back(c);
        }
        std::ranges::reverse(result);

        return result;
    }

    // Converts string value to base ten.
    static std::string convert_to_base_ten(const std::string& value, radix_type radix)
    {
        auto last = char_to_digit(value.back());
        auto length = value.length();

        auto power = value_from(length - 1);
        auto converted_value = value_from(last);
        auto radix_value = value_from(static_cast<std::uint8_t>(radix));

        int current;

        for (std::size_t i = 0; i < length - 1; ++i) {
            current = char_to_digit(value.at(i));
            converted_value += value_from(current).multiply(radix_value.pow(power--));
        }
        return std::move(converted_value.value_);
    }
};

} // namespace wingmann::numerics

#endif // WINGMANN_BIGINTEGER_H
