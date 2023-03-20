/// @file   biginteger.h
/// @author Alexander Shavrov (alexander.shavrov@outlook.com)
/// @brief  Arbitrary large integer library.
/// @date   2022-09-28
///
/// @copyright Copyright (c) 2022
///
/// This file is distributed under the GNU GPL v3 License.
/// See LICENSE file for details.
///

#ifndef ALEF_NUMERICS_BIG_INTEGER_BIG_INTEGER_H
#define ALEF_NUMERICS_BIG_INTEGER_BIG_INTEGER_H

#include "./utility.h"

#include "alef/alef.h"
#include "alef/cast.h"
#include "alef/char.h"
#include "alef/concepts.h"
#include "alef/math.h"
#include "alef/utility.h"

ALEF_GLOBAL_NAMESPACE_BEGIN

namespace num {

/// @brief Arbitrarily large integer.
class biginteger {
public:
    using radix_type = num::radix;
    using sign_type  = num::sign;
    using radix_flag = num::radix_flag;
    using sign_flag  = num::sign_flag;

protected:
    // The base of a system of number.
    radix_type radix_{radix_flag::decimal};

    // Sign flag.
    sign_type sign_{sign_flag::positive};

    // std::string representation of decimal value.
    std::string value_{"0"};

public:
    /// @brief Default constructor.
    biginteger() = default;

    /// @brief Destructor.
    virtual ~biginteger() = default;

    /// @brief Copy constructor.
    /// @param other Value to copy.
    ///
    biginteger(const biginteger& other) = default;

    /// @brief Move constructor.
    /// @param other Value to move.
    ///
    biginteger(biginteger&& other) noexcept
        : radix_{other.radix_},
          sign_{other.sign_},
          value_{std::move(other.value_)}
    {
        set_default(other);
    }

    /// @brief Constructs from integer.
    /// @param value Integral value.
    ///
    biginteger(integer auto value) { *this = std::to_string(value); }

    /// @brief Constructs from string literal.
    ///
    /// @param value std::string literal value.
    /// @param radix The base of a system of number.
    ///
    biginteger(const char* value, radix_type radix) : radix_{radix} { *this = std::string{value}; }

    /// @brief Constructs from string literal.
    /// @param value std::string literal value.
    ///
    biginteger(const char* value) : biginteger{value, radix_type{radix_flag::decimal}} { }

    /// @brief Constructs from string.
    ///
    /// @param value std::string value.
    /// @param radix The base of a system of number.
    ///
    biginteger(std::string value, radix_flag radix) : radix_{radix} { *this = std::move(value); }

    /// @brief Constructs from string.
    /// @param value std::string value.
    ///
    biginteger(std::string value) : biginteger{std::move(value), radix_flag::decimal} { }

    // Assignment operators ------------------------------------------------------------------------

    /// @brief Copy assignment operator.
    ///
    /// @param rhs Value to copy.
    /// @return    Constructed object.
    ///
    biginteger& operator=(const biginteger& rhs) = default;

    /// @brief Move assignment operator.
    ///
    /// @param rhs Value to move.
    /// @return    Constructed object.
    ///
    biginteger& operator=(biginteger&& rhs) noexcept {
        this->radix_ = rhs.radix_;
        this->sign_ = rhs.sign_;
        this->value_ = std::move(rhs.value_);

        set_default(rhs);

        return *this;
    }

    /// @brief Constructs from an integer rhs.
    ///
    /// @param rhs An integer rhs.
    /// @return    Constructed object.
    ///
    biginteger& operator=(integer auto rhs) {
        *this = std::to_string(rhs);
        return *this;
    }

    /// @brief Constructs from the string literal.
    ///
    /// @param rhs The string literal.
    /// @return    Constructed object.
    ///
    biginteger& operator=(const char* rhs) {
        *this = std::string{rhs};
        return *this;
    }

    /// @brief Constructs from the string value.
    ///
    /// @param value The value from which to construct.
    /// @return      Constructed object.
    ///
    biginteger& operator=(std::string value) {
        this->sign_.value = (value.starts_with('-') ? sign_flag::negative : sign_flag::positive);

        if (this->is_negative()) {
            __detail::num::remove_sign(value);
        }
        if (!__detail::num::is_valid_number(value, this->radix_.value)) {
            throw std::invalid_argument("value in not valid");
        }
        __detail::num::remove_leading_zeros(value);

        if (this->radix_.value == radix_flag::decimal) {
            this->value_ = std::move(value);
        } else {
            this->value_ = convert_to_base_ten(value, this->radix_.value);
        }
        return *this;
    }

    // Increment and decrement operators -----------------------------------------------------------

    /// @brief Increments the current value.
    /// @return Modified object.
    ///
    biginteger& operator++() {
        *this = this->add(1);
        return *this;
    }

    /// @brief Increments the current value after returns copy.
    /// @return Copy of current value.
    ///
    biginteger operator++(int) {
        auto temp{*this};
        ++(*this);
        return temp;
    }

    /// @brief Decrements the current value.
    /// @return Modified object.
    ///
    biginteger& operator--() {
        *this = this->subtract(1);
        return *this;
    }

    /// @brief Decrements the current value after returns copy.
    /// @return Copy of current value.
    ///
    biginteger operator--(int) {
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
    biginteger shift_left(const biginteger& rhs) const {
        if (rhs.is_negative()) {
            throw std::invalid_argument{"negative value"};
        }
        auto bitwise_value = this->to_string(radix_flag::binary);
        auto i = value_from(0);

        while (i.compare(rhs) == std::strong_ordering::less) {
            bitwise_value.push_back('0');
            ++i;
        }
        return {std::move(bitwise_value), radix_flag::binary};
    }

    /// @brief Shifts the current value to right on right operand value.
    ///
    /// @param rhs The value to shift_right on.
    /// @return    Shifted current value.
    ///
    [[nodiscard]]
    biginteger shift_right(const biginteger& rhs) const {
        if (rhs.is_negative()) {
            throw std::invalid_argument{"negative value"};
        }
        auto bitwise_value = this->to_string(radix_flag::binary);
        auto i = value_from(0);

        while ((i.compare(rhs) == std::strong_ordering::less) && (bitwise_value.length() > 0)) {
            bitwise_value.pop_back();
            ++i;
        }
        if (bitwise_value.empty()) {
            bitwise_value.push_back('0');
        }
        return {std::move(bitwise_value), radix_flag::binary};
    }

    // Comparison ----------------------------------------------------------------------------------

    /// @brief Three way compares the current value and right side operand.
    ///
    /// @param rhs The value to compere with the current value.
    /// @return    Result of comparison.
    ///
    [[nodiscard]]
    std::strong_ordering compare(const biginteger& rhs) const {
        // -a, +b
        if (this->is_negative() && rhs.is_positive()) {
            return std::strong_ordering::less;
        }

        // +a, -b
        if (this->is_positive() && rhs.is_negative()) {
            return std::strong_ordering::greater;
        }

        // -a, -b
        if (this->is_negative() && rhs.is_negative()) {
            if (this->value_.length() == rhs.value_.length()) {
                if (this->value_ > rhs.value_) {
                    return std::strong_ordering::less;
                }
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
            if (this->value_ > rhs.value_) {
                return std::strong_ordering::greater;
            }
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
    bool equal(const biginteger& rhs) const {
        return this->compare(rhs) == std::strong_ordering::equivalent;
    }

    // Basic arithmetic ----------------------------------------------------------------------------

    /// @brief Adds value.
    ///
    /// @param rhs The right side operand for addition to current value.
    /// @return    Result of addition.
    ///
    [[nodiscard]]
    biginteger add(const biginteger& rhs) const {
        // (-a)+(+b)
        if (this->is_negative() && rhs.is_positive()) {
            return rhs.subtract(this->negate());
        }

        // (+a)+(-b)
        if (this->is_positive() && rhs.is_negative()) {
            return this->subtract(rhs.negate());
        }

        // (+a)+(+b) or (-a)+(-b)
        auto lhs_value = this->value_;
        auto rhs_value = rhs.value_;

        auto diff_length = std::abs(
            static_cast<int>(lhs_value.length() - rhs_value.length()));

        const auto min_value{'0'};
        const auto max_value{'9'};

        if (lhs_value.length() > rhs_value.length()) {
            rhs_value.insert(0, diff_length, min_value);
        } else {
            lhs_value.insert(0, diff_length, min_value);
        }
        std::ranges::reverse(lhs_value);
        std::ranges::reverse(rhs_value);

        usize index{};
        char carry{min_value};

        for (char& lhs_char : lhs_value) {
            lhs_char = static_cast<char>(
                (carry - min_value) +
                (lhs_char - min_value) +
                (rhs_value.at(index) - min_value) +
                min_value);

            if (lhs_char > max_value) {
                lhs_char -= 10;
                carry = (min_value + 1);
            } else {
                carry = min_value;
            }
            ++index;
        }

        if (carry > min_value) {
            lhs_value.append(1, carry);
        }
        std::ranges::reverse(lhs_value);

        return this->is_negative() ? value_from(lhs_value).negate() : std::move(lhs_value);
    }

    /// @brief Subtracts value.
    ///
    /// @param rhs The right side operand for subtract from current value.
    /// @return    Result of subtraction.
    ///
    [[nodiscard]]
    biginteger subtract(const biginteger& rhs) const {
        // (-a)-(+b) or (+a)-(-b)
        if ((this->is_negative() && rhs.is_positive()) ||
            (this->is_positive() && rhs.is_negative()))
        {
            return this->add(rhs.negate());
        }

        // (+a)-(+b) or (-a)-(-b)
        if (this->is_negative()) {
            return this->add(rhs.negate());
        }
        bool inverted_sign = (this->compare(rhs) == std::strong_ordering::less);

        std::string subtracted = inverted_sign ? rhs.value_ : this->value_;
        std::string removed = inverted_sign ? this->value_ : rhs.value_;

        auto diff_length = std::abs(
            static_cast<int>(subtracted.length() - removed.length()));

        const auto min_value{'0'};

        if (subtracted.size() > removed.size()) {
            removed.insert(0, diff_length, min_value);
        } else {
            subtracted.insert(0, diff_length, min_value);
        }
        std::ranges::reverse(subtracted);
        std::ranges::reverse(removed);

        usize index{};

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

        while (subtracted.front() == min_value && subtracted.length() != 1) {
            subtracted.erase(0, 1);
        }
        return inverted_sign ? value_from(subtracted).negate() : std::move(subtracted);
    }

    /// @brief Multiplies value.
    ///
    /// @param rhs The right operand for multiplication by the current value.
    /// @return    Result of multiplication.
    ///
    [[nodiscard]]
    biginteger multiply(const biginteger& rhs) const {
        auto lhs_value = this->value_;
        auto rhs_value = rhs.value_;

        std::ranges::reverse(lhs_value);
        std::ranges::reverse(rhs_value);

        const auto min_value{'0'};
        const auto max_value{'9'};

        int index{};
        char carry{min_value};

        auto temp = value_from(0);
        uint8 result;

        for (const auto& lhs_char : lhs_value) {
            auto operation = std::string{}.insert(0, index, min_value);

            for (const auto& rhs_char : rhs_value) {
                result =
                    ((lhs_char - min_value) * (rhs_char - min_value)) +
                    (carry - min_value) +
                    min_value;

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
            temp = temp.add(operation);
            ++index;
        }
        auto positive =
            (this->is_negative() && rhs.is_negative()) ||
            (this->is_positive() && rhs.is_positive());

        return positive ? std::move(temp) : temp.negate();
    }

    /// @brief Divides value.
    ///
    /// @param rhs The right operand by which to divide the current value.
    /// @return    Result of division.
    ///
    [[nodiscard]]
    biginteger divide(const biginteger& rhs) const {
        if (rhs.equal(0)) {
            throw std::invalid_argument("divide by zero");
        }
        if (rhs.equal(1)) {
            return *this;
        }
        if (this->equal(rhs)) {
            return 1;
        }
        auto lhs_value = this->value_;
        std::ranges::reverse(lhs_value);

        auto rhs_abs = rhs.abs();

        std::string lhs_quotient;
        std::string rhs_quotient;

        do {
            lhs_quotient.push_back(lhs_value.back());
            lhs_value.pop_back();

            biginteger dividend_value{lhs_quotient};

            if (dividend_value.compare(rhs_abs) == std::strong_ordering::less) {
                rhs_quotient.push_back('0');
                continue;
            }
            auto number = value_from(2);
            auto mul = rhs_abs.multiply(number).compare(dividend_value);

            while (mul == std::strong_ordering::less || mul == std::strong_ordering::equal) {
                ++number;
                mul = rhs_abs.multiply(number).compare(dividend_value);
            }
            --number;
            rhs_quotient.append(number.to_string());
            lhs_quotient = dividend_value.subtract(rhs_abs.multiply(number)).to_string();
        } while (!lhs_value.empty());

        auto positive =
            (this->is_negative() && rhs.is_negative()) ||
            (this->is_positive() && rhs.is_positive());

        return positive ? std::move(rhs_quotient) : value_from(rhs_quotient).negate();
    }

    /// @brief Computes remainder.
    ///
    /// @param rhs The right operand for taking the remainder.
    /// @return    Remainder of division current value by right side value.
    ///
    [[nodiscard]]
    biginteger mod(const biginteger& rhs) const {
        if (rhs.equal(0)) {
            throw std::invalid_argument("mod by zero");
        }
        return this->subtract(rhs.multiply(this->divide(rhs)));
    }

    // Complex arithmetic --------------------------------------------------------------------------

    /// @brief Reverses the sign.
    /// @return If current value signed then current value otherwise sign reversed.
    ///
    [[nodiscard]]
    biginteger negate() const {
        if (this->equal(0)) {
            return *this;
        }
        if (this->is_negative()) {
            return this->value_;
        }
        std::stringstream ss;
        ss << '-' << this->value_;

        return ss.str();
    }

    /// @brief Absolutes the current value.
    /// @return Unsigned current value.
    ///
    [[nodiscard]]
    biginteger abs() const {
        return this->is_positive() ? *this : this->negate();
    }

    /// @brief Rises the current value to the power of the right operand.
    ///
    /// @param rhs Degree.
    /// @return    Current value raised to the power.
    ///
    [[nodiscard]]
    biginteger pow(const biginteger& rhs) const {
        if (rhs.equal(0)) {
            return 1;
        }
        if (this->equal(0)) {
            return 0;
        }
        if (rhs.compare(0) == std::strong_ordering::less) {
            return this->abs().equal(1) ? *this : 0;
        }
        auto init_exp{rhs};
        auto result{*this};
        auto result_odd = value_from(1);

        while (init_exp.compare(1) == std::strong_ordering::greater) {
            if (init_exp.mod(2)) {
                result_odd = result_odd.multiply(result);
            }
            result = result.multiply(result);
            init_exp = init_exp.divide(2);
        }
        return result.multiply(result_odd);
    }

    /// @brief Rises the exponent value to the power of 10
    /// @return Current value raised to the power.
    ///
    [[nodiscard]]
    biginteger pow10() const {
        return value_from(10).pow(*this);
    }

    /// @brief Computes square root.
    /// @return Square root of current value.
    ///
    [[nodiscard]]
    biginteger sqrt() const {
        if (this->compare(0) == std::strong_ordering::less) {
            throw std::invalid_argument("sqrt of a negative value");
        }

        // Small numbers optimisation.
        if (this->equal(0)) {
            return 0;
        }
        if (this->compare(4) == std::strong_ordering::less) {
            return 1;
        }
        if (this->compare(9) == std::strong_ordering::less) {
            return 2;
        }
        if (this->compare(16) == std::strong_ordering::less) {
            return 3;
        }
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
    biginteger gcd(const biginteger& rhs) const {
        auto lhs_abs = this->abs();
        auto rhs_abs = rhs.abs();

        if (rhs_abs.equal(0) || lhs_abs.equal(0)) {
            return 0;
        }
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
    biginteger lcm(const biginteger& rhs) const {
        if (this->equal(0) || rhs.equal(0)) {
            return 0;
        }
        return this->multiply(rhs).abs().divide(this->gcd(rhs));
    }

    // Modification and checking -------------------------------------------------------------------

    /// @brief Checks for current value is power of 10.
    /// @return If is power of 10 true otherwise false.
    ///
    bool is_pow10() {
        return (this->value_.at(0) == '1') && std::ranges::all_of(
            this->value_.cbegin() + 1,
            this->value_.cend(),
            [](const auto c) { return c == '0'; });
    }

    /// @brief Gets the binary usize.
    /// @return Bit length of current value.
    ///
    [[nodiscard]]
    usize bit_length() const {
        return to_string(radix_flag::binary).length();
    }

    /// @brief Checks for value sign.
    /// @return If value unsigned then true otherwise false.
    ///
    [[nodiscard]]
    bool is_positive() const {
        return this->sign_.is_positive();
    }

    /// @brief Checks for value sign.
    /// @return If value signed true otherwise false.
    ///
    [[nodiscard]]
    bool is_negative() const {
        return !is_positive();
    }

    /// @brief Swaps values.
    /// @param rhs The value to swap with the current value.
    ///
    void swap(biginteger& rhs) {
        if (this->equal(rhs)) {
            return;
        }
        std::swap(*this, rhs);
    }

    // Conversion methods --------------------------------------------------------------------------

    /// @brief Creates value from integer value.
    ///
    /// @tparam value Integral value.
    /// @return       Constructed value.
    ///
    static biginteger value_from(integer auto value) {
        return std::to_string(value);
    }

    /// @brief Creates value from string value.
    ///
    /// @tparam value std::string value.
    /// @return       Constructed value.
    ///
    static biginteger value_from(std::string value) {
        return std::move(value);
    }

    /// @brief Converts to boolean representation.
    /// @return Boolean representation of current value.
    ///
    explicit operator bool() const {
        return !this->equal(0);
    }

public:
    /// @brief Converts to 32 bit integer value.
    ///
    /// @param radix The base of a system of number.
    /// @return      If converted, then integer value otherwise std::nullopt
    ///
    [[nodiscard]]
    std::optional<int32> to_int32(radix_flag radix = radix_flag::decimal) const {
        return string_to<int32>(to_string(), radix);
    }

    /// @brief Converts to 64 bit integer value.
    ///
    /// @param radix The base of a system of number.
    /// @return      If converted, then integer value otherwise std::nullopt
    ///
    [[nodiscard]]
    std::optional<int64> to_int64(radix_flag radix = radix_flag::decimal) const {
        return string_to<int64>(to_string(), radix);
    }

public:
    /// @brief Converts to string representation.
    ///
    /// @param radix The base of a system of number.
    /// @return      std::string representation of current value.
    ///
    [[nodiscard]]
    std::string to_string(radix_flag radix = radix_flag::decimal) const {
        std::stringstream ss;

        if (is_negative()) {
            ss << '-';
        }
        if (radix == radix_flag::decimal) {
            ss << value_;
        } else {
            ss << convert_from_base_ten(*this, radix);
        }
        return ss.str();
    }

private:
    // Sets the default value for an object whose state has been moved.
    static void set_default(biginteger& moved) {
        moved.radix_.value = radix_flag::decimal;
        moved.sign_.value = sign_flag::positive;
        moved.value_ = "0";
    }

    // Converts not base ten value to string.
    static std::string convert_from_base_ten(const biginteger& value, const radix_flag radix) {
        auto decimal_value{value};
        auto modulo = value_from(static_cast<uint8>(radix));

        std::string result;

        while (!decimal_value.equal(0)) {
            auto remainder = decimal_value.mod(modulo);
            decimal_value = decimal_value.divide(modulo);

            auto c = base_chars(radix_flag::hexadecimal).at(std::stoi(remainder.to_string()));
            result.push_back(c);
        }
        std::ranges::reverse(result);

        return result;
    }

    // Converts string value to base ten.
    static std::string convert_to_base_ten(const std::string& value, radix_flag radix) {
        auto last = char_to_int32(value.back());
        auto length = value.length();

        auto power = value_from(length - 1);
        auto converted_value = value_from(last);
        auto radix_value = value_from(static_cast<uint8>(radix));

        int current;

        for (usize i = 0; i < length - 1; ++i) {
            current = char_to_int32(value.at(i));
            converted_value = converted_value
                .add(value_from(current).multiply(radix_value.pow(power--)));
        }
        return std::move(converted_value.value_);
    }
};

} // namespace num

ALEF_GLOBAL_NAMESPACE_END

#endif // ALEF_NUMERICS_BIG_INTEGER_BIG_INTEGER_H
