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
protected:
    // The base of a system of numeration.
    int radix_{10};

    // Sign flag.
    bool signed_{};

    // String representation of decimal value.
    std::string value_{"0"};

public:
    /// @brief Default constructor.
    big_integer() = default;

    /// @brief Copy constructor.
    /// @param value Value to copy.
    ///
    big_integer(const big_integer& value) { *this = value; };

    /// @brief Move constructor.
    /// @param value Value to move.
    ///
    big_integer(const big_integer&& value) noexcept { *this = value; };

    /// @brief Destructor.
    virtual ~big_integer() = default;

    /// @brief Constructs from primitive integral.
    /// @param value Integral value.
    ///
    template<typename T>
    requires std::integral<T> && (!std::is_same<T, bool>::value)
    big_integer(T value) : signed_{value < 0} { *this = value; }

    /// @brief Constructs from string literal.
    ///
    /// @param value String literal value.
    /// @param radix The base of a system of numeration.
    ///
    big_integer(const char* value, int radix = 10)
        : radix_{radix}, signed_{*value == '-'} { *this = value; }

    /// @brief Constructs from string.
    ///
    /// @param value String value.
    /// @param radix The base of a system of numeration.
    ///
    big_integer(std::string value, int radix = 10)
        : radix_{radix}, signed_{value.starts_with('-')} { *this = std::move(value); }

    // Assignment operators ------------------------------------------------------------------------

    /// @brief Copy assignment operator.
    ///
    /// @param rhs Value to copy.
    /// @return    Constructed object.
    ///
    big_integer& operator=(const big_integer& rhs) noexcept = default;

    /// @brief Move assignment operator.
    ///
    /// @param rhs Value to move.
    /// @return    Constructed object.
    ///
    big_integer& operator=(const big_integer&& rhs) noexcept {
        this->value_ = rhs.value_;
        return *this;
    }

    /// @brief Assignment operator.
    ///
    /// @param rhs The value from which to construct.
    /// @return    Constructed object.
    ///
    template<typename T>
    requires std::integral<T> && (!std::is_same<T, bool>::value)
    big_integer& operator=(T rhs) {
        *this = std::to_string(rhs);
        return *this;
    }

    /// @brief Assignment operator.
    ///
    /// @param rhs The value from which to construct.
    /// @return    Constructed object.
    ///
    big_integer& operator=(const char* rhs) {
        *this = std::string{rhs};
        return *this;
    }

    /// @brief Assignment operator.
    ///
    /// @param rhs The value from which to construct.
    /// @return    Constructed object.
    ///
    big_integer& operator=(std::string rhs) {
        if (this->is_negative())
            rhs.erase(0, 1);

        if (radix_ < 2 || radix_ > 16 )
            throw std::invalid_argument("incorrect radix");

        // Remove leading zero.
        while (rhs.starts_with('0') && (rhs.length() != 1))
            rhs.erase(0, 1);

        if (this->radix_ == 10) {
            this->value_ = rhs;
            return *this;
        }
        // Convert to base ten to use trivial algorithm.
        char last_char = rhs.back();
        int last = ('0' <= last_char) && (last_char <= '9')
            ? (last_char - '0')
            : (tolower(last_char) - 'a') + 10;

        auto value_length = static_cast<std::int64_t>(rhs.length());

        big_integer power{value_length - 1};
        big_integer converted_value{last};
        big_integer radix_value{this->radix_};

        for (int i = 0; i < value_length - 1; i++) {
            auto c = rhs.at(i);
            int current_value = ('0' <= c) && (c <= '9')
                ? (c - '0')
                : (std::tolower(c) - 'a') + 10;

            converted_value += big_integer{current_value}.multiply(radix_value.pow(power--));
        }
        *this = this->is_negative()
            ? converted_value.negate()
            : std::move(converted_value);
        return *this;
    }

    // Additional assignment operators -------------------------------------------------------------

    /// @brief Addition assignment operator.
    /// Adds the value to the current value and assigns the result.
    ///
    /// @param rhs The value to add to the current value.
    /// @return    Modified object.
    ///
    big_integer& operator+=(const big_integer& rhs) {
        *this = this->add(rhs);
        return *this;
    }

    /// @brief Subtraction assignment operator.
    /// Subtracts the value of the right operand from the current value and assigns the result.
    ///
    /// @param rhs The value to subtract from the current value.
    /// @return    Modified object.
    ///
    big_integer& operator-=(const big_integer& rhs) {
        *this = this->subtract(rhs);
        return *this;
    }

    /// @brief Multiplication assignment operator.
    /// Multiplies the current value by the value of the right operand and assigns the result.
    ///
    /// @param rhs The value to multiply by current value.
    /// @return    Modified object.
    ///
    big_integer& operator*=(const big_integer& rhs) {
        *this = this->multiply(rhs);
        return *this;
    }

    /// @brief Division assignment operator.
    /// Divides the current value by the value of the right operand and assigns the result.
    ///
    /// @param rhs The value by which to divide the current value.
    /// @return    Modified object.
    ///
    big_integer& operator/=(const big_integer& rhs) {
        *this = this->divide(rhs);
        return *this;
    }

    /// @brief Modulus assignment operator.
    /// Gets the remainder of the current value divided by the value of the right operand and
    /// assigns the result.
    ///
    /// @param rhs The right operand for taking the remainder.
    /// @return    Modified object.
    ///
    big_integer& operator%=(const big_integer& rhs) {
        *this = this->mod(rhs);
        return *this;
    }

    /// @brief Left shift assignment operator.
    /// Shifts the current value to left on right operand value and assigns the result.
    ///
    /// @param rhs The value to shift on.
    /// @return    Modified object.
    ///
    big_integer& operator<<=(const big_integer& rhs) {
        *this = this->left_shift(rhs);
        return *this;
    }

    /// @brief Left shift assignment operator.
    /// Shifts the current value to left on right operand value and assigns the result.
    ///
    /// @param rhs The value to shift on.
    /// @return    SModified object.
    ///
    big_integer& operator>>=(const big_integer& rhs) {
        *this = this->right_shift(rhs);
        return *this;
    }

    // Increment and decrement operators -----------------------------------------------------------

    /// @brief Prefix increment operator.
    /// Increments the current value.
    ///
    /// @return Modified object.
    ///
    big_integer& operator++() {
        *this = this->add(1);
        return *this;
    }

    /// @brief Postfix increment operator.
    /// Increments the current value after returns copy.
    ///
    /// @return Copy of current value.
    ///
    const big_integer operator++(int) {
        auto temp{*this};
        ++(*this);
        return std::move(temp);
    }

    /// @brief Prefix decrement operator.
    /// Decrements the current value.
    ///
    /// @return Modified object.
    ///
    big_integer& operator--() {
        *this = this->subtract(1);
        return *this;
    }

    /// @brief Postfix decrement operator.
    /// Decrements the current value after returns copy.
    ///
    /// @return Copy of current value.
    ///
    const big_integer operator--(int) {
        auto temp{*this};
        --(*this);
        return std::move(temp);
    }

    // Shift operations -----------------------------------------------------------------------------

    /// @brief Shifts the current value to left on right operand value.
    ///
    /// @param rhs The value to shift on.
    /// @return    Shifted current value.
    ///
    [[nodiscard]]
    big_integer left_shift(const big_integer& rhs) const {
        if (rhs.is_negative())
            throw std::invalid_argument("negative value");

        auto bitwise_value = this->to_string(2);

        for (auto i = 0; i < rhs; i++)
            bitwise_value.push_back('0');

        return {bitwise_value, 2};
    }

    /// @brief Shifts the current value to right on right operand value.
    ///
    /// @param rhs The value to shift on.
    /// @return    Shifted current value.
    ///
    [[nodiscard]]
    big_integer right_shift(const big_integer& rhs) const {
        if (rhs.is_negative())
            throw std::invalid_argument("negative value");

        auto bitwise_value = this->to_string(2);

        for (auto i = 0; (i < rhs) && (bitwise_value.length() > 0); i++)
            bitwise_value.pop_back();

        if (bitwise_value.empty())
            bitwise_value.push_back('0');

        return {bitwise_value, 2};
    }

    // Shift operators -----------------------------------------------------------------------------

    /// @brief Left shift operator.
    /// Shifts the current value to left on right operand value.
    ///
    /// @param rhs The value to shift on.
    /// @return    Shifted current value.
    ///
    big_integer operator<<(const big_integer& rhs) const { return this->left_shift(rhs); }

    /// @brief Right shift operator.
    /// Shifts the current value to right on right operand value.
    ///
    /// @param rhs The value to shift on.
    /// @return    Shifted current value.
    ///
    big_integer operator>>(const big_integer& rhs) const { return this->right_shift(rhs); }


    // Basic arithmetic ----------------------------------------------------------------------------

    /// @brief Addition.
    ///
    /// @param rhs The right side operand for addition to current value.
    /// @return    Result of addition.
    ///
    [[nodiscard]]
    big_integer add(const big_integer& rhs) const {
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

        if (lhs_value.length() > rhs_value.length())
            rhs_value.insert(0, diff_length, '0');
        else
            lhs_value.insert(0, diff_length, '0');

        std::ranges::reverse(lhs_value);
        std::ranges::reverse(rhs_value);

        int index{};
        char carry{'0'};

        for (char& lhs_char : lhs_value) {
            lhs_char = static_cast<char>(
                (carry - '0') + (lhs_char - '0') + (rhs_value.at(index) - '0') + '0');

            if (lhs_char > '9') {
                lhs_char -= 10;
                carry = '1';
            } else {
                carry = '0';
            }
            index++;
        }
        if (carry > '0')
            lhs_value.append(1, carry);

        std::ranges::reverse(lhs_value);

        return this->is_negative() ? big_integer{lhs_value}.negate() : lhs_value;
    }

    /// @brief Subtraction.
    ///
    /// @param rhs The right side operand for subtract from current value.
    /// @return    Result of subtraction.
    ///
    [[nodiscard]]
    big_integer subtract(const big_integer& rhs) const {
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

        if (subtracted.size() > removed.size())
            removed.insert(0, diff_length, '0');
        else
            subtracted.insert(0, diff_length, '0');

        std::ranges::reverse(subtracted);
        std::ranges::reverse(removed);

        int index{};

        for (char& symbol : subtracted) {
            if (symbol < removed.at(index)) {
                symbol += 10;
                subtracted[index + 1]--;
            }
            symbol = static_cast<char>((symbol - '0') - (removed.at(index) - '0') + '0');
            index++;
        }
        std::ranges::reverse(subtracted);

        while (subtracted.front() == '0' && subtracted.length() != 1)
            subtracted.erase(0, 1);

        return inverted_sign ? big_integer{subtracted}.negate() : subtracted;
    }

    /// @brief Multiplication.
    ///
    /// @param rhs The right operand for multiplication by the current value.
    /// @return    Result of multiplication.
    ///
    [[nodiscard]]
    big_integer multiply(const big_integer& rhs) const {
        auto lhs_value = this->value_;
        auto rhs_value = rhs.value_;

        std::ranges::reverse(lhs_value);
        std::ranges::reverse(rhs_value);

        int step{};
        char carry{'0'};

        big_integer temp;

        for (const auto& lhs_char : lhs_value) {
            auto operation = std::string{}.insert(0, step, '0');

            for (const auto& rhs_char : rhs_value) {
                std::uint8_t result = ((lhs_char - '0') * (rhs_char - '0')) + (carry - '0') + '0';
                carry = '0';

                if (result > '9') {
                    while (result > '9') {
                        result -= 10;
                        carry++;
                    }
                }
                operation.insert(0, 1, static_cast<char>(result));
            }
            if (carry > '0') {
                operation.insert(0, 1, carry);
                carry = '0';
            }
            temp += operation;
            step++;
        }
        auto positive = (this->is_negative() && rhs.is_negative()) ||
                        (this->is_positive() && rhs.is_positive());
        return positive ? temp :temp.negate();
    }

    /// @brief Division.
    ///
    /// @param rhs The right operand by which to divide the current value.
    /// @return    Result of division.
    ///
    [[nodiscard]]
    big_integer divide(const big_integer& rhs) const {
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
            auto number{value_from<2>()};

            while (rhs_abs.multiply(number) <= dividend_value)
                number++;

            number--;
            rhs_quotient.append(number.to_string());
            lhs_quotient = dividend_value.subtract(rhs_abs.multiply(number)).to_string();
        } while (!lhs_value.empty());

        bool positive = (this->is_negative() && rhs.is_negative()) ||
            (this->is_positive() && rhs.is_positive());
        return positive ? rhs_quotient : big_integer{rhs_quotient}.negate();
    }

    /// @brief Modulus.
    ///
    /// @param rhs The right operand for taking the remainder.
    /// @return    Remainder of division current value by right side value.
    ///
    [[nodiscard]]
    big_integer mod(const big_integer& rhs) const {
        if (rhs.equal(0))
            throw std::invalid_argument("mod by zero");

        return this->subtract(rhs.multiply(this->divide(rhs)));
    }

    // Arithmetic operators ------------------------------------------------------------------------

    /// @brief Plus operator.
    ///
    /// @param rhs The right side operand for addition to current value.
    /// @return    Result of addition.
    ///
    big_integer operator+(const big_integer& rhs) const { return this->add(rhs); }

    /// @brief Minus operator.
    ///
    /// @param rhs The right side operand for subtract from current value.
    /// @return    Result of subtraction.
    ///
    big_integer operator-(const big_integer& rhs) const { return this->subtract(rhs); }

    /// @brief Multiply operator.
    ///
    /// @param rhs The right operand for multiplication by the current value.
    /// @return    Result of multiplication.
    ///
    big_integer operator*(const big_integer& rhs) const { return this->multiply(rhs); }

    /// @brief Division operator.
    ///
    /// @param rhs The right operand by which to divide the current value.
    /// @return    Result of division.
    ///
    big_integer operator/(const big_integer& rhs) const { return this->divide(rhs); }

    /// @brief Modulus operator.
    ///
    /// @param rhs The right operand for taking the remainder.
    /// @return    Remainder of division current value by right side value.
    ///
    big_integer operator%(const big_integer& rhs) const { return this->mod(rhs); }

    // Complex arithmetic --------------------------------------------------------------------------

    /// @brief Operator tilde. Reverses the sign.
    /// @return If the value is already signed,
    /// the current value otherwise changes to the signed value.
    ///
    [[nodiscard]]
    big_integer negate() const {
        if (this->equal(0)) return *this;
        if (this->is_negative()) return this->value_;

        std::stringstream ss;
        ss << '-' << this->value_;
        return ss.str();
    }

    /// @brief Absolutes the current value.
    /// @return Always unsigned current value.
    ///
    [[nodiscard]]
    big_integer abs() const { return this->is_positive() ? *this : this->negate(); }

    /// @brief Rises the current value to the power of the right operand.
    ///
    /// @param rhs Degree.
    /// @return    Result of multiplying the number by itself.
    ///
    [[nodiscard]]
    big_integer pow(const big_integer& rhs) const {
        if (rhs.equal(0))
            return 1;

        if (rhs.compare(0) == std::strong_ordering::less) {
            if (this->equal(0))
                throw std::logic_error("");

            return this->abs().equal(1) ? *this : value_from<0>();
        }
        auto init_exp{rhs};
        auto result{*this};
        auto result_odd{value_from<1>()};

        while (init_exp.compare(1) == std::strong_ordering::greater) {
            if (init_exp.mod(2)) result_odd *= result;
            result *= result;
            init_exp /= 2;
        }
        return result.multiply(result_odd);
    }

    /// @brief Rises the exponent value to the power of base-10 power
    ///
    /// @param exp The exponent value
    /// @return    Result of power.
    ///
    [[nodiscard]]
    big_integer pow10() const { return big_integer{10}.pow(*this); }

    /// @brief Computes the greatest common divisor of the left and right operand.
    ///
    /// @param lhs Left operand.
    /// @param rhs Right operand.
    /// @return    Greatest common divisor.
    ///
    [[nodiscard]]
    big_integer gcd(const big_integer& rhs) const {
        big_integer abs_lhs = this->abs();
        big_integer abs_rhs = rhs.abs();

        if (abs_rhs.equal(0) || abs_lhs.equal(0))
            return 0;

        auto remainder{abs_rhs};

        while (!remainder.equal(0)) {
            remainder = abs_lhs.mod(abs_rhs);
            abs_lhs = abs_rhs; // previous remainder
            abs_rhs = remainder; // current remainder
        }
        return std::move(abs_lhs);
    }

    /// @brief Computes the least common multiple of the left and right operand.
    ///
    /// @param lhs Left operand.
    /// @param rhs Right operand.
    /// @return    Least common multiple.
    ///
    [[nodiscard]]
    big_integer lcm(const big_integer& rhs) const {
        if (this->equal(0) || rhs.equal(0))
            return 0;
        return this->multiply(rhs).abs().divide(this->gcd(rhs));
    }

    // Comparison ----------------------------------------------------------------------------------

    /// @brief Compares current value with right side operand.
    ///
    /// @param rhs The value to compare with current value.
    /// @return    Result of comparison.
    ///
    [[nodiscard]]
    std::strong_ordering compare(const big_integer& rhs) const {
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
        if (this->is_positive() && rhs.is_positive()) {
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

        return std::strong_ordering::equivalent;
    }

    /// @brief Compares the current value and right side operand.
    ///
    /// @param rhs The value to compare with the current value.
    /// @return    Result of comparison.
    ///
    [[nodiscard]]
    bool equal(const big_integer& rhs) const {
        return this->compare(rhs) == std::strong_ordering::equivalent;
    }

    // Comparison operators ------------------------------------------------------------------------

    /// @brief Three-way comparison operator.
    /// Compares the current value and right side operand.
    ///
    /// @param rhs The value to compere with the current value.
    /// @return    Result of comparison.
    ///
    std::strong_ordering operator<=>(const big_integer& rhs) const { return this->compare(rhs); }

    /// @brief Equal operator.
    /// Compares the current value and right side operand.
    ///
    /// @param rhs The value to compare with the current value.
    /// @return    Result of comparison.
    ///
    auto operator==(const big_integer& rhs) const { return this->equal(rhs); }

    // Modification and checking -------------------------------------------------------------------

    /// @brief Gets the binary size of value.
    /// @return Bit length.
    ///
    [[nodiscard]]
    std::size_t bit_length() const { return to_string(2).length(); }

    /// @brief Checks for value sign.
    /// @return true if value unsigned otherwise false.
    ///
    [[nodiscard]]
    bool is_positive() const { return !this->signed_; }

    /// @brief Checks for value sign.
    /// @return If value signed true otherwise false.
    ///
    [[nodiscard]]
    bool is_negative() const { return this->signed_; }

    /// @brief Swaps left and right operands.
    /// @param rhs The value to swap with the current value.
    ///
    void swap(big_integer& rhs) {
        if (this->equal(rhs))
            return;
        std::swap(*this, rhs);
    }

    // Stream operators ----------------------------------------------------------------------------

    /// @brief Outputs the value to the output stream.
    ///
    /// @param os    The output stream.
    /// @param value The value to put to output.
    /// @return      Output stream.
    ///
    std::ostream& operator<<(std::ostream& os) const & {
        os << this->to_string();
        return os;
    }

    /// @brief Gets the value from input stream.
    ///
    /// @param is    Inputs stream.
    /// @param value The value for writing from input stream;
    /// @return      Input stream.
    ///
    std::istream& operator>>(std::istream& is) & {
        std::string input;
        is >> input;
        *this = input;
        return is;
    }

    // Conversion methods --------------------------------------------------------------------------

    /// @brief Big integer value from primitive integral types.
    ///
    /// @tparam value Integral value.
    /// @return       Converted value from integral.
    template<std::int64_t value>
    static big_integer value_from() { return std::to_string(value); }

    /// @brief Bool operator. Converts current value to boolean representation.
    /// @return Boolean representation of current value.
    ///
    explicit operator bool() const { return !this->equal(0); }

    /// @brief Safe convert to primitive integral.
    ///
    /// @tparam T    The type convert to.
    /// @param f     Pointer to converter function.
    /// @param radix The base of a system of numeration.
    /// @return      Converted integral value.
    ///
    template<typename T>
    requires std::integral<T>
    std::optional<T> safe_convert(int radix, T (*f)(const std::string&, std::size_t*, int)) const {
        try {
            return f(this->to_string(radix), nullptr, radix);
        } catch (std::out_of_range&) {
        } catch (std::invalid_argument&) {
        }
        return std::nullopt;
    }

    /// @brief Converts to primitive integral value.
    ///
    /// @tparam T Type of integral value to which to convert.
    /// @return   If converted, then integral value otherwise std::nullopt
    ///
    template<std::integral T>
    std::optional<T> to_integer(int radix = 10) const;

    /// @brief Converts to primitive integral value.
    ///
    /// @tparam T Type of integral value to which to convert.
    /// @return   If converted, then integral value otherwise std::nullopt
    ///
    template<>
    [[nodiscard]]
    std::optional<int> to_integer<int>(int radix) const {
        return this->safe_convert(radix, std::stoi);
    }

    /// @brief Converts to primitive integral value.
    ///
    /// @tparam T Type of integral value to which to convert.
    /// @return   If converted, then integral value otherwise std::nullopt
    ///
    template<>
    [[nodiscard]]
    std::optional<std::int64_t> to_integer<std::int64_t>(int radix) const {
        return this->safe_convert(radix, std::stoll);
    }

    /// @brief Converts to primitive integral value.
    ///
    /// @tparam T Type of integral value to which to convert.
    /// @return   If converted, then integral value otherwise std::nullopt
    ///
    template<>
    [[nodiscard]]
    std::optional<std::uint64_t> to_integer<std::uint64_t>(int radix) const {
        return this->safe_convert(radix, std::stoull);
    }

    /// @brief Converts to string representation.
    ///
    /// @param radix The base of a system of numeration.
    /// @return      Converted string.
    ///
    [[nodiscard]]
    std::string to_string(int radix = 10) const {
        if ((radix < 2) || (radix > 16))
            throw std::invalid_argument("incorrect radix");

        std::stringstream ss;
        if (this->is_negative()) ss << '-';

        if (radix == 10) {
            ss << this->value_;
            return ss.str();
        }
        auto decimal_value{*this};
        big_integer modulo{radix};

        std::string value;

        while (!decimal_value.equal(0)) {
            auto remainder = decimal_value.mod(modulo);
            decimal_value /= modulo;

            // Doesn't throw exception
            auto symbol = base_chars().at(std::stoi(remainder.to_string()));
            value.push_back(symbol);
        }
        std::ranges::reverse(value);

        ss << value;
        return ss.str();
    }

private:
    // Returns the base char values of a system of numeration.
    // Allowed numeration systems from 2 to 16.
    static constexpr std::string base_chars() { return "0123456789ABCDEF"; }
};

} // namespace wingmann::numerics

#endif // WINGMANN_BIGINTEGER_H
