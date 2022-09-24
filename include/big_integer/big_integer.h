/// @file   big_integer.h
/// @brief  Arbitrarily large integer implementation.
/// @author Alexander Shavrov

#ifndef WINGMANN_BIGINTEGER_H
#define WINGMANN_BIGINTEGER_H

#include <string>
#include <cmath>
#include <concepts>
#include <algorithm>
#include <optional>
#include <ostream>
#include <ranges>
#include <sstream>
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

    /// @brief Constructs from primitive integral.
    /// @param value Integral value.
    ///
    big_integer(int value) : signed_{value < 0} { *this = value; }

    /// @brief Constructs from primitive integral.
    /// @param value Integral value.
    ///
    big_integer(std::int64_t value) : signed_{value < 0} { *this = value; }

    /// @brief Constructs from primitive integral.
    /// @param value Integral value.
    ///
    big_integer(std::uint64_t value) : signed_{value < 0} { *this = value; }

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

    /// @brief Destructor.
    virtual ~big_integer() = default;

public:
    // Assignment operators ------------------------------------------------------------------------

    /// @brief Copy assignment operator.
    ///
    /// @param rhs Value to copy.
    /// @return    Constructed object.
    ///
    big_integer& operator=(const big_integer& rhs) noexcept {
        this->radix_ = rhs.radix_;
        this->value_ = rhs.value_;
        this->signed_ = rhs.signed_;
        return *this;
    }

    /// @brief Move assignment operator.
    ///
    /// @param rhs Value to move.
    /// @return    Constructed object.
    ///
    big_integer& operator=(const big_integer&& rhs) noexcept {
        this->radix_ = rhs.radix_;
        this->value_ = rhs.value_;
        this->signed_ = rhs.signed_;
        return *this;
    }

    /// @brief Assignment operator.
    ///
    /// @param rhs The value from which to construct.
    /// @return    Constructed object.
    ///
    big_integer& operator=(int rhs) {
        *this = std::to_string(rhs);
        return *this;
    }

    /// @brief Assignment operator.
    ///
    /// @param rhs The value from which to construct.
    /// @return    Constructed object.
    ///
    big_integer& operator=(std::int64_t rhs) {
        *this = std::to_string(rhs);
        return *this;
    }

    /// @brief Assignment operator.
    ///
    /// @param rhs The value from which to construct.
    /// @return    Constructed object.
    ///
    big_integer& operator=(std::uint64_t rhs) {
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
        if (this->signed_)
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

        big_integer pow{value_length - 1};
        big_integer converted_value{last};
        big_integer radix_value{this->radix_};

        for (int i = 0; i < value_length - 1; i++) {
            auto c = rhs.at(i);
            int current_value = ('0' <= c) && (c <= '9')
                ? (c - '0')
                : (tolower(c) - 'a') + 10;

            converted_value += big_integer{current_value}.multiply(radix_value.pow(pow--));
        }
        *this = this->signed_ ? converted_value.negate() : std::move(converted_value);
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
        *this = add(rhs);
        return *this;
    }

    /// @brief Subtraction assignment operator.
    /// Subtracts the value of the right operand from the current value and assigns the result.
    ///
    /// @param rhs The value to subtract from the current value.
    /// @return    Modified object.
    ///
    big_integer& operator-=(const big_integer& rhs) {
        *this = subtract(rhs);
        return *this;
    }

    /// @brief Multiplication assignment operator.
    /// Multiplies the current value by the value of the right operand and assigns the result.
    ///
    /// @param rhs The value to multiply by current value.
    /// @return    Modified object.
    ///
    big_integer& operator*=(const big_integer& rhs) {
        *this = multiply(rhs);
        return *this;
    }

    /// @brief Division assignment operator.
    /// Divides the current value by the value of the right operand and assigns the result.
    ///
    /// @param rhs The value by which to divide the current value.
    /// @return    Modified object.
    ///
    big_integer& operator/=(const big_integer& rhs) {
        *this = divide(rhs);
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
        *this = mod(rhs);
        return *this;
    }

    /// @brief Left shift assignment operator.
    /// Shifts the current value to left on right operand value and assigns the result.
    ///
    /// @param rhs The value to shift on.
    /// @return    Modified object.
    ///
    big_integer& operator<<=(const big_integer& rhs) {
        *this = operator<<(rhs);
        return *this;
    }

    /// @brief Left shift assignment operator.
    /// Shifts the current value to left on right operand value and assigns the result.
    ///
    /// @param rhs The value to shift on.
    /// @return    SModified object.
    ///
    big_integer& operator>>=(const big_integer& rhs) {
        *this = operator>>(rhs);
        return *this;
    }

    // Arithmetic operators ------------------------------------------------------------------------

    /// @brief Plus operator.
    ///
    /// @param rhs The right side operand for addition to current value.
    /// @return    Result of addition.
    ///
    big_integer operator+(const big_integer& rhs) const { return add(rhs); }

    /// @brief Minus operator.
    ///
    /// @param rhs The right side operand for subtract from current value.
    /// @return    Result of subtraction.
    ///
    big_integer operator-(const big_integer& rhs) const { return subtract(rhs); }

    /// @brief Multiply operator.
    ///
    /// @param rhs The right operand for multiplication by the current value.
    /// @return    Result of multiplication.
    ///
    big_integer operator*(const big_integer& rhs) const { return multiply(rhs); }

    /// @brief Division operator.
    ///
    /// @param rhs The right operand by which to divide the current value.
    /// @return    Result of division.
    ///
    big_integer operator/(const big_integer& rhs) const { return divide(rhs); }

    /// @brief Modulus operator.
    ///
    /// @param rhs The right operand for taking the remainder.
    /// @return    Remainder of division current value by right side value.
    ///
    big_integer operator%(const big_integer& rhs) const { return mod(rhs); }

    // Increment operators -------------------------------------------------------------------------

    /// @brief Prefix increment operator.
    /// Increments the current value.
    ///
    /// @return Modified object.
    ///
    big_integer& operator++() {
        *this = add(value_from<1>());
        return *this;
    }

    /// @brief Postfix increment operator.
    /// Increments the current value after returns copy.
    ///
    /// @return Copy of current value.
    ///
    const big_integer operator++(int) {
        auto before_plus{std::move(*this)};
        *this = add(value_from<1>());
        return before_plus;
    }

    // Decrement operators -------------------------------------------------------------------------

    /// @brief Prefix decrement operator.
    /// Decrements the current value.
    ///
    /// @return Modified object.
    ///
    big_integer& operator--() {
        *this = subtract(value_from<1>());
        return *this;
    }

    /// @brief Postfix decrement operator.
    /// Decrements the current value after returns copy.
    ///
    /// @return Copy of current value.
    ///
    const big_integer operator--(int) {
        auto before_minus{std::move(*this)};
        *this = subtract(value_from<1>());
        return before_minus;
    }

    // Shift operators -----------------------------------------------------------------------------

    /// @brief Left shift operator.
    /// Shifts the current value to left on right operand value.
    ///
    /// @param rhs The value to shift on.
    /// @return    Shifted current value.
    ///
    big_integer operator<<(const big_integer& rhs) const {
        auto bitwise_value = to_string(2);

        for (auto i = value_from<0>(); i < rhs; i++)
            bitwise_value.push_back('0');

        return {bitwise_value, 2};
    }

    /// @brief Right shift operator.
    /// Shifts the current value to right on right operand value.
    ///
    /// @param rhs The value to shift on.
    /// @return    Shifted current value.
    ///
    big_integer operator>>(const big_integer& rhs) const {
        auto bitwise_value = to_string(2);

        for (auto i = value_from<0>(); (i < rhs) && (bitwise_value.length() > 0); i++)
            bitwise_value.pop_back();

        if (bitwise_value.empty())
            bitwise_value.push_back('0');

        return {bitwise_value, 2};
    }

    // Comparison operators ------------------------------------------------------------------------

    /// @brief Three-way comparison operator.
    /// Compares the current value and right side operand.
    ///
    /// @param rhs The value to compere with the current value.
    /// @return    Result of comparison.
    ///
    std::strong_ordering operator<=>(const big_integer& rhs) const { return compare(rhs); }

    /// @brief Equal operator.
    /// Compares the current value and right side operand.
    ///
    /// @param rhs The value to compare with the current value.
    /// @return    Result of comparison.
    ///
    auto operator==(const big_integer& rhs) const {
        return compare(rhs) == std::strong_ordering::equivalent;
    }

    // Stream operators ----------------------------------------------------------------------------

    /// @brief Outputs the value to the output stream.
    ///
    /// @param os    The output stream.
    /// @param value The value to put to output.
    /// @return      Output stream.
    ///
    friend std::ostream& operator<<(std::ostream& os, const big_integer& value) {
        os << value.to_string();
        return os;
    }

    /// @brief Gets the value from input stream.
    ///
    /// @param is    Inputs stream.
    /// @param value The value for writing from input stream;
    /// @return      Input stream.
    ///
    friend std::istream& operator>>(std::istream& is, big_integer& value) {
        std::string input;
        is >> input;
        value = input;
        return is;
    }

public:
    // Basic arithmetic ----------------------------------------------------------------------------

    /// @brief Addition.
    ///
    /// @param rhs The right side operand for addition to current value.
    /// @return    Result of addition.
    ///
    [[nodiscard]]
    big_integer add(const big_integer& rhs) const {
        // (-a)+(+b)
        if (this->signed_ && !rhs.signed_)
            return rhs.subtract(negate());

        // (+a)+(-b)
        if (!this->signed_ && rhs.signed_)
            return subtract(rhs.negate());

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

        return this->signed_ ? big_integer{lhs_value}.negate() : lhs_value;
    }

    /// @brief Subtraction.
    ///
    /// @param rhs The right side operand for subtract from current value.
    /// @return    Result of subtraction.
    ///
    [[nodiscard]]
    big_integer subtract(const big_integer& rhs) const {
        // (-a)-(+b) or (+a)-(-b)
        if ((this->signed_ && !rhs.signed_) || (!this->signed_ && rhs.signed_))
            return add(rhs.negate());

        // (+a)-(+b) or (-a)-(-b)
        if (this->signed_)
            return add(rhs.negate());

        bool inverted_sign = (compare(rhs) == std::strong_ordering::less);

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

        auto positive = (this->signed_ && rhs.signed_) || (!this->signed_ && !rhs.signed_);
        if (!positive)
            return temp.negate();

        return temp;
    }

    /// @brief Division.
    ///
    /// @param rhs The right operand by which to divide the current value.
    /// @return    Result of division.
    ///
    [[nodiscard]]
    big_integer divide(const big_integer& rhs) const {
        if (rhs == value_from<0>())
            throw std::invalid_argument("divide by zero");

        if (rhs == value_from<1>())
            return *this;

        if (compare(rhs) == std::strong_ordering::equivalent)
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
            lhs_quotient = dividend_value
                .subtract(rhs_abs.multiply(number))
                .to_string();
        } while (!lhs_value.empty());

        bool positive = (this->signed_ && rhs.signed_) || (!this->signed_ && !rhs.signed_);
        if (!positive)
            return big_integer{rhs_quotient}.negate();

        return rhs_quotient;
    }

    /// @brief Modulus.
    ///
    /// @param rhs The right operand for taking the remainder.
    /// @return    Remainder of division current value by right side value.
    ///
    [[nodiscard]]
    big_integer mod(const big_integer& rhs) const {
        if (rhs == value_from<0>())
            throw std::invalid_argument("mod by zero");

        return subtract(rhs.multiply(divide(rhs)));
    }

    // Complex arithmetic --------------------------------------------------------------------------

    /// @brief Rises the current value to the power of the right operand.
    ///
    /// @param rhs Degree.
    /// @return    Result of power.
    ///
    [[nodiscard]]
    big_integer pow(const big_integer& rhs) const {
        if (rhs == value_from<0>())
            return std::move(value_from<1>());

        if (rhs == value_from<1>())
            return *this;

        auto init_value{*this};
        auto temp{*this};

        for (auto i = value_from<1>(); i < rhs; i++)
            temp *= init_value;

        return temp;
    }

    // Modification and checking -------------------------------------------------------------------

    /// @brief Gets the binary size of value.
    /// @return Bit length.
    ///
    [[nodiscard]]
    std::size_t bit_length() const { return to_string(2).length(); }

    /// @brief Compares current value with right side operand.
    ///
    /// @param rhs The value to compare with curren value.
    /// @return    If equals, 0 else if the current value less, -1, otherwise 1.
    ///
    [[nodiscard]]
    std::strong_ordering compare(const big_integer& rhs) const {
        // -a, +b
        if (this->signed_ && !rhs.signed_) return std::strong_ordering::less;

        // +a, -b
        if (!this->signed_ && rhs.signed_) return std::strong_ordering::greater;

        // +a, +b or -a, -b
        if (this->value_.length() < rhs.value_.length())
            return std::strong_ordering::less;

        if (this->value_.length() > rhs.value_.length())
            return std::strong_ordering::greater;

        bool positive = !this->signed_;

        if (this->value_ < rhs.value_)
            return positive ? std::strong_ordering::less : std::strong_ordering::greater;

        if (this->value_ > rhs.value_)
            return positive ? std::strong_ordering::greater : std::strong_ordering::less;

        return std::strong_ordering::equivalent;
    }

    /// @brief Negate the current value.
    ///
    /// @return If the value is already signed,
    /// the current value otherwise changes to the signed value.
    ///
    [[nodiscard]]
    big_integer negate() const {
        std::string value{this->value_};
        return this->signed_ ? value : value.insert(0, 1, '-');
    }

    /// @brief Absolutes the current value.
    /// @return Always unsigned current value.
    ///
    [[nodiscard]]
    big_integer abs() const { return is_positive() ? *this : negate(); }

    /// @brief Checks for value sign.
    /// @return true if value unsigned otherwise false.
    ///
    [[nodiscard]]
    bool is_positive() const { return !this->signed_; }

    /// @brief Checks for value sign.
    /// @return If value signed true otherwise false.
    ///
    [[nodiscard]]
    bool is_negative() const { return !is_positive(); }

    /// @brief Swaps left and right operands.
    /// @param rhs The value to swap with the current value.
    ///
    void swap(big_integer& rhs) { std::swap(*this, rhs); }

    /// @brief Big integer value from primitive integral types.
    ///
    /// @tparam value Integral value.
    /// @return       Converted value from integral.
    template<std::int64_t value>
    static big_integer value_from() { return std::to_string(value); }

    // Conversion methods --------------------------------------------------------------------------

    /// @brief Converts to primitive integral value.
    ///
    /// @tparam T Type of integral value to which to convert.
    /// @return   Integral value.
    ///
    template<std::integral T>
    [[nodiscard]]
    std::optional<T> to_integer(int radix = 10) const {
        try {
            return static_cast<T>(std::stoll(to_string(radix)));
        } catch (std::out_of_range&) {
        } catch (std::invalid_argument&) {
        }
        return std::nullopt;
    }

    /// @brief Converts to primitive floating point value.
    ///
    /// @tparam T Type of floating point value to which to convert.
    /// @return   Floating point value.
    ///

    template<std::floating_point T>
    [[nodiscard]]
    std::optional<T> to_floating(int radix = 10) const {
        try {
            return static_cast<T>(std::stold(to_string(radix)));
        } catch (std::out_of_range&) {
        } catch (std::invalid_argument&) {
        }
        return std::nullopt;
    }

    /// @brief Converts to string representation.
    ///
    /// @param radix The base of a system of numeration.
    /// @return      Converted string.
    ///
    [[nodiscard]]
    std::string to_string(int radix = 10) const {
        if (radix < 2 || radix > 16)
            throw std::invalid_argument("incorrect radix");

        std::stringstream ss;
        if (this->signed_) ss << '-';

        if (radix == 10) {
            ss << this->value_;
            return ss.str();
        }
        auto decimal_value{*this};
        big_integer modulo{radix};

        std::string value;

        while (decimal_value != value_from<0>()) {
            auto remainder= decimal_value.mod(modulo);
            decimal_value /= modulo;

            // Doesn't throw exception
            auto symbol = base_char_value().at(std::stoi(remainder.to_string()));
            value.push_back(symbol);
        }
        std::ranges::reverse(value);

        ss << value;
        return ss.str();
    }

private:
    // Returns the base char values of a system of numeration.
    // Allowed numeration systems from 2 to 16.
    static constexpr std::string base_char_value() { return "0123456789ABCDEF"; }
};

} // namespace wingmann::numerics

#endif // WINGMANN_BIGINTEGER_H
