#ifndef ALEF_NUMERICS_BIG_INTEGER_BIG_INTEGER_H
#define ALEF_NUMERICS_BIG_INTEGER_BIG_INTEGER_H

#include "utility.h"
#include "radix.h"

#include <concepts>
#include <optional>
#include <stdexcept>
#include <sstream>

namespace wingmann::numerics {

/**
 * @brief Arbitrarily large integer.
 */
class BigInteger {
public:
    using RadixType = Radix;
    using SignType  = Sign;
    using RadixFlag = RadixFlag;
    using SignFlag  = SignFlag;

protected:
    // The base of a system of number.
    RadixType radix_{RadixFlag::Decimal};

    // Sign flag.
    SignType sign_{SignFlag::positive};

    // std::string representation of Decimal value.
    std::string value_{"0"};

public:
    /**
     * @brief Default constructor.
     */
    BigInteger() = default;

    /**
     * @brief Destructor.
     */
    virtual ~BigInteger() = default;

    /**
     * @brief Copy constructor.
     * @param other Value to copy.
     */
    BigInteger(const BigInteger& other) = default;

    /**
     * @brief Move constructor.
     * @param other Value to move.
     */
    BigInteger(BigInteger&& other) noexcept
        : radix_{other.radix_},
          sign_{other.sign_},
          value_{std::move(other.value_)}
    {
        setDefault(other);
    }

    /**
     * @brief Constructs from integer.
     * @param value Integral value.
     */
    template<typename T>
    requires std::integral<T> && (!std::same_as<T, bool>)
    BigInteger(T value) { *this = std::to_string(value); }

    /**
     * @brief Constructs from string literal.
     *
     * @param value std::string literal value.
     * @param radix The base of a system of number.
     */
    BigInteger(const char* value, RadixType radix) : radix_{radix} { *this = std::string{value}; }

    /**
     * @brief Constructs from string literal.
     * @param value std::string literal value.
     */
    BigInteger(const char* value) : BigInteger{value, RadixType{RadixFlag::Decimal}} { }

    /**
     * @brief Constructs from string.
     *
     * @param value std::string value.
     * @param radix The base of a system of number.
     */
    BigInteger(std::string value, RadixFlag radix) : radix_{radix} { *this = std::move(value); }

    /**
     * @brief Constructs from string.
     * @param value std::string value.
     */
    BigInteger(std::string value) : BigInteger{std::move(value), RadixFlag::Decimal} { }

    // Assignment operators ------------------------------------------------------------------------

    /**
     * @brief Copy assignment operator.
     *
     * @param rhs Value to copy.
     * @return Constructed object.
     */
    BigInteger& operator=(const BigInteger& rhs) = default;

    /**
     * @brief Move assignment operator.
     *
     * @param rhs Value to move.
     * @return Constructed object.
     */
    BigInteger& operator=(BigInteger&& rhs) noexcept {
        this->radix_ = rhs.radix_;
        this->sign_ = rhs.sign_;
        this->value_ = std::move(rhs.value_);

        setDefault(rhs);
        return *this;
    }

    /**
     * @brief Constructs from an integer rhs.
     *
     * @param rhs An integer rhs.
     * @return Constructed object.
     */
    template<typename T>
    requires std::integral<T> && (!std::same_as<T, bool>)
    BigInteger& operator=(T rhs) {
        *this = std::to_string(rhs);
        return *this;
    }

    /**
     * @brief Constructs from the string literal.
     *
     * @param rhs The string literal.
     * @return Constructed object.
     */
    BigInteger& operator=(const char* rhs) {
        *this = std::string{rhs};
        return *this;
    }

    /**
     * @brief Constructs from the string value.
     *
     * @param value The value from which to construct.
     * @return Constructed object.
     */
    BigInteger& operator=(std::string value) {
        this->sign_.value = (value.starts_with('-') ? SignFlag::negative : SignFlag::positive);

        if (this->isNegative()) {
            __detail::removeSign(value);
        }
        if (!__detail::isValidNumber(value, this->radix_.value)) {
            throw std::invalid_argument("value in not valid");
        }
        __detail::removeLeadingZeros(value);

        if (this->radix_.value == RadixFlag::Decimal) {
            this->value_ = std::move(value);
        } else {
            this->value_ = convertToBaseTen(value, this->radix_.value);
        }
        return *this;
    }

    // Increment and decrement operators -----------------------------------------------------------

    /**
     * @brief Increments the current value.
     * @return Modified object.
     */
    BigInteger& operator++() {
        *this = this->add(1);
        return *this;
    }

    /**
     * @brief Increments the current value after returns copy.
     * @return Copy of current value.
     */
    BigInteger operator++(int) {
        auto temp{*this};
        ++(*this);
        return temp;
    }

    /**
     * @brief Decrements the current value.
     * @return Modified object.
     */
    BigInteger& operator--() {
        *this = this->subtract(1);
        return *this;
    }

    /**
     * @brief Decrements the current value after returns copy.
     * @return Copy of current value.
     */
    BigInteger operator--(int) {
        auto temp{*this};
        --(*this);
        return temp;
    }

    // Shift operations -----------------------------------------------------------------------------

    /**
     * @brief Shifts the current value to left on right operand value.
     *
     * @param rhs The value to shiftRight on.
     * @return Shifted current value.
     */
    [[nodiscard]]
    BigInteger shiftLeft(const BigInteger& rhs) const {
        if (rhs.isNegative()) {
            throw std::invalid_argument{"negative value"};
        }
        auto bitwiseValue = this->to_string(RadixFlag::Binary);
        auto i = valueFrom(0);

        while (i.compare(rhs) == std::strong_ordering::less) {
            bitwiseValue.push_back('0');
            ++i;
        }
        return {std::move(bitwiseValue), RadixFlag::Binary};
    }

    /**
     * @brief Shifts the current value to right on right operand value.
     *
     * @param rhs The value to shiftRight on.
     * @return Shifted current value.
     */
    [[nodiscard]]
    BigInteger shiftRight(const BigInteger& rhs) const {
        if (rhs.isNegative()) {
            throw std::invalid_argument{"negative value"};
        }
        auto bitwiseValue = this->to_string(RadixFlag::Binary);
        auto i = valueFrom(0);

        while ((i.compare(rhs) == std::strong_ordering::less) && (bitwiseValue.length() > 0)) {
            bitwiseValue.pop_back();
            ++i;
        }
        if (bitwiseValue.empty()) {
            bitwiseValue.push_back('0');
        }
        return {std::move(bitwiseValue), RadixFlag::Binary};
    }

    // Comparison ----------------------------------------------------------------------------------

    /**
     * @brief Three way compares the current value and right side operand.
     *
     * @param rhs The value to compere with the current value.
     * @return Result of comparison.
     */
    [[nodiscard]]
    std::strong_ordering compare(const BigInteger& rhs) const {
        // -a, +b
        if (this->isNegative() && rhs.isPositive()) {
            return std::strong_ordering::less;
        }

        // +a, -b
        if (this->isPositive() && rhs.isNegative()) {
            return std::strong_ordering::greater;
        }

        // -a, -b
        if (this->isNegative() && rhs.isNegative()) {
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

    /**
     * @brief Compares the current value and right side operand.
     *
     * @param rhs The value to compare with the current value.
     * @return Result of comparison.
     */
    [[nodiscard]]
    bool equal(const BigInteger& rhs) const {
        return this->compare(rhs) == std::strong_ordering::equivalent;
    }

    // Basic arithmetic ----------------------------------------------------------------------------

    /**
     * @brief Adds value.
     *
     * @param rhs The right side operand for addition to current value.
     * @return Result of addition.
     */
    [[nodiscard]]
    BigInteger add(const BigInteger& rhs) const {
        // (-a)+(+b)
        if (this->isNegative() && rhs.isPositive()) {
            return rhs.subtract(this->negate());
        }

        // (+a)+(-b)
        if (this->isPositive() && rhs.isNegative()) {
            return this->subtract(rhs.negate());
        }

        // (+a)+(+b) or (-a)+(-b)
        auto lhsValue = this->value_;
        auto rhsValue = rhs.value_;

        auto diffLength = std::abs(static_cast<int>(lhsValue.length() - rhsValue.length()));

        const auto minValue{'0'};
        const auto maxValue{'9'};

        if (lhsValue.length() > rhsValue.length()) {
            rhsValue.insert(0, diffLength, minValue);
        } else {
            lhsValue.insert(0, diffLength, minValue);
        }
        std::ranges::reverse(lhsValue);
        std::ranges::reverse(rhsValue);

        std::size_t index{};
        char carry{minValue};

        for (char& lhsChar : lhsValue) {
            lhsChar = static_cast<char>(
                    (carry - minValue) +
                    (lhsChar - minValue) +
                    (rhsValue.at(index) - minValue) +
                    minValue);

            if (lhsChar > maxValue) {
                lhsChar -= 10;
                carry = (minValue + 1);
            } else {
                carry = minValue;
            }
            ++index;
        }
        if (carry > minValue) {
            lhsValue.append(1, carry);
        }
        std::ranges::reverse(lhsValue);

        return this->isNegative() ? valueFrom(lhsValue).negate() : std::move(lhsValue);
    }

    /**
     * @brief Subtracts value.
     *
     * @param rhs The right side operand for subtract from current value.
     * @return Result of subtraction.
     */
    [[nodiscard]]
    BigInteger subtract(const BigInteger& rhs) const {
        // (-a)-(+b) or (+a)-(-b)
        if ((this->isNegative() && rhs.isPositive()) ||
            (this->isPositive() && rhs.isNegative()))
        {
            return this->add(rhs.negate());
        }

        // (+a)-(+b) or (-a)-(-b)
        if (this->isNegative()) {
            return this->add(rhs.negate());
        }
        bool inverted_sign = (this->compare(rhs) == std::strong_ordering::less);

        std::string subtracted = inverted_sign ? rhs.value_ : this->value_;
        std::string removed = inverted_sign ? this->value_ : rhs.value_;

        auto diffLength = std::abs(static_cast<int>(subtracted.length() - removed.length()));

        const auto minValue{'0'};

        if (subtracted.size() > removed.size()) {
            removed.insert(0, diffLength, minValue);
        } else {
            subtracted.insert(0, diffLength, minValue);
        }
        std::ranges::reverse(subtracted);
        std::ranges::reverse(removed);

        std::size_t index{};

        for (char& symbol : subtracted) {
            if (symbol < removed.at(index)) {
                symbol += 10;
                --subtracted.at(index + 1);
            }
            symbol = static_cast<char>(
                    (symbol - minValue) - (removed.at(index) - minValue) + minValue);

            ++index;
        }
        std::ranges::reverse(subtracted);

        while (subtracted.front() == minValue && subtracted.length() != 1) {
            subtracted.erase(0, 1);
        }
        return inverted_sign ? valueFrom(subtracted).negate() : std::move(subtracted);
    }

    /**
     * @brief Multiplies value.
     *
     * @param rhs The right operand for multiplication by the current value.
     * @return Result of multiplication.
     */
    [[nodiscard]]
    BigInteger multiply(const BigInteger& rhs) const {
        auto lhsValue = this->value_;
        auto rhsValue = rhs.value_;

        std::ranges::reverse(lhsValue);
        std::ranges::reverse(rhsValue);

        const auto minValue{'0'};
        const auto maxValue{'9'};

        int index{};
        char carry{minValue};

        auto temp = valueFrom(0);
        std::uint8_t result;

        for (const auto& lhsChar : lhsValue) {
            auto operation = std::string{}.insert(0, index, minValue);

            for (const auto& rhsChar : rhsValue) {
                result = ((lhsChar - minValue) * (rhsChar - minValue)) + (carry - minValue) + minValue;
                carry = minValue;

                if (result > maxValue) {
                    while (result > maxValue) {
                        result -= 10;
                        ++carry;
                    }
                }
                operation.insert(0, 1, static_cast<char>(result));
            }
            if (carry > minValue) {
                operation.insert(0, 1, carry);
                carry = minValue;
            }
            temp = temp.add(operation);
            ++index;
        }
        auto positive = (this->isNegative() && rhs.isNegative()) || (this->isPositive() && rhs.isPositive());

        return positive ? std::move(temp) : temp.negate();
    }

    /**
     * @brief Divides value.
     *
     * @param rhs The right operand by which to divide the current value.
     * @return Result of division.
     */
    [[nodiscard]]
    BigInteger divide(const BigInteger& rhs) const {
        if (rhs.equal(0)) {
            throw std::invalid_argument("divide by zero");
        }
        if (rhs.equal(1)) {
            return *this;
        }
        if (this->equal(rhs)) {
            return 1;
        }
        auto lhsValue = this->value_;
        std::ranges::reverse(lhsValue);

        auto rhsAbs = rhs.abs();

        std::string lhsQuotient;
        std::string rhsQuotient;

        do {
            lhsQuotient.push_back(lhsValue.back());
            lhsValue.pop_back();

            BigInteger dividend_value{lhsQuotient};

            if (dividend_value.compare(rhsAbs) == std::strong_ordering::less) {
                rhsQuotient.push_back('0');
                continue;
            }
            auto number = valueFrom(2);
            auto mul = rhsAbs.multiply(number).compare(dividend_value);

            while (mul == std::strong_ordering::less || mul == std::strong_ordering::equal) {
                ++number;
                mul = rhsAbs.multiply(number).compare(dividend_value);
            }
            --number;
            rhsQuotient.append(number.to_string());
            lhsQuotient = dividend_value.subtract(rhsAbs.multiply(number)).to_string();
        } while (!lhsValue.empty());

        auto positive = (this->isNegative() && rhs.isNegative()) || (this->isPositive() && rhs.isPositive());

        return positive ? std::move(rhsQuotient) : valueFrom(rhsQuotient).negate();
    }

    /**
     * @brief Computes remainder.
     *
     * @param rhs The right operand for taking the remainder.
     * @return Remainder of division current value by right side value.
     */
    [[nodiscard]]
    BigInteger mod(const BigInteger& rhs) const {
        if (rhs.equal(0)) {
            throw std::invalid_argument("mod by zero");
        }
        return this->subtract(rhs.multiply(this->divide(rhs)));
    }

    // Complex arithmetic --------------------------------------------------------------------------

    /**
     * @brief Reverses the sign.
     * @return If current value signed then current value otherwise sign reversed.
     */
    [[nodiscard]]
    BigInteger negate() const {
        if (this->equal(0)) {
            return *this;
        }
        if (this->isNegative()) {
            return this->value_;
        }
        std::stringstream ss;
        ss << '-' << this->value_;

        return ss.str();
    }

    /**
     * @brief Absolutes the current value.
     * @return Unsigned current value.
     */
    [[nodiscard]]
    BigInteger abs() const {
        return this->isPositive() ? *this : this->negate();
    }

    /**
     * @brief Rises the current value to the power of the right operand.
     *
     * @param rhs Degree.
     * @return Current value raised to the power.
     */
    [[nodiscard]]
    BigInteger pow(const BigInteger& rhs) const {
        if (rhs.equal(0)) {
            return 1;
        }
        if (this->equal(0)) {
            return 0;
        }
        if (rhs.compare(0) == std::strong_ordering::less) {
            return this->abs().equal(1) ? *this : 0;
        }
        auto initExp{rhs};
        auto result{*this};
        auto resultOdd = valueFrom(1);

        while (initExp.compare(1) == std::strong_ordering::greater) {
            if (initExp.mod(2)) {
                resultOdd = resultOdd.multiply(result);
            }
            result = result.multiply(result);
            initExp = initExp.divide(2);
        }
        return result.multiply(resultOdd);
    }

    /**
     * @brief Rises the exponent value to the power of 10.
     * @return Current value raised to the power.
     */
    [[nodiscard]]
    BigInteger pow10() const {
        return valueFrom(10).pow(*this);
    }

    /**
     * @brief Computes square root.
     * @return Square root of current value.
     */
    [[nodiscard]]
    BigInteger sqrt() const {
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
        auto previous = valueFrom(-1);
        auto current = valueFrom(this->to_string().size() / 2 - 1).pow10();

        while (current.subtract(previous).abs().compare(1) == std::strong_ordering::greater) {
            previous = current;
            current = this->divide(previous).add(previous).divide(2);
        }
        return current;
    }

    /**
     * @brief Computes the greatest common divisor.
     *
     * @param rhs The right operand.
     * @return Greatest common divisor of the current value and right operand.
     */
    [[nodiscard]]
    BigInteger gcd(const BigInteger& rhs) const {
        auto lhsAbs = this->abs();
        auto rhsAbs = rhs.abs();

        if (rhsAbs.equal(0) || lhsAbs.equal(0)) {
            return 0;
        }
        auto remainder{rhsAbs};

        while (!remainder.equal(0)) {
            remainder = lhsAbs.mod(rhsAbs);
            lhsAbs = rhsAbs;
            rhsAbs = remainder;
        }
        return lhsAbs;
    }

    /**
     * @brief Computes the least common multiple.
     *
     * @param rhs The right operand.
     * @return Least common multiple of the current value and right operand.
     */
    [[nodiscard]]
    BigInteger lcm(const BigInteger& rhs) const {
        if (this->equal(0) || rhs.equal(0)) {
            return 0;
        }
        return this->multiply(rhs).abs().divide(this->gcd(rhs));
    }

    // Modification and checking -------------------------------------------------------------------

    /**
     * @brief Checks for current value is power of 10.
     * @return If is power of 10 true otherwise false.
     */
    bool isPow10() {
        return (this->value_.at(0) == '1') && std::ranges::all_of(
            this->value_.cbegin() + 1,
            this->value_.cend(),
            [](const auto c) { return c == '0'; });
    }

    /**
     * @brief Gets the Binary usize.
     * @return Bit length of current value.
     */
    [[nodiscard]]
    std::size_t bitLength() const {
        return to_string(RadixFlag::Binary).length();
    }

    /**
     * @brief Checks for value sign.
     * @return If value unsigned then true otherwise false.
     */
    [[nodiscard]]
    bool isPositive() const {
        return this->sign_.isPositive();
    }

    /**
     * @brief Checks for value sign.
     * @return If value signed true otherwise false.
     */
    [[nodiscard]]
    bool isNegative() const {
        return !isPositive();
    }

    /**
     * @brief Swaps values.
     * @param rhs The value to swap with the current value.
     */
    void swap(BigInteger& rhs) {
        if (this->equal(rhs)) {
            return;
        }
        std::swap(*this, rhs);
    }

    // Conversion methods --------------------------------------------------------------------------

    /**
     * @brief Creates value from integer value.
     *
     * @param value Integral value.
     * @return Constructed value.
     */
    template<typename T>
    requires std::integral<T> && (!std::same_as<T, bool>)
    static BigInteger valueFrom(T value) {
        return std::to_string(value);
    }

    /**
     * @brief Creates value from string value.
     *
     * @param value std::string value.
     * @return Constructed value.
     */
    static BigInteger valueFrom(std::string value) {
        return std::move(value);
    }

    /**
     * @brief Converts to boolean representation.
     * @return Boolean representation of current value.
     */
    explicit operator bool() const {
        return !this->equal(0);
    }

public:
    std::optional<std::int32_t> to_int32() {
        try {
            return std::stoi(value_, nullptr, static_cast<int>(radix_.value));
        } catch (std::invalid_argument&) {
        } catch (std::out_of_range&) { }

        return std::nullopt;
    }

    std::optional<std::int64_t> to_int64() {
        try {
#if defined(__WORDSIZE) && (__WORDSIZE == 64)
            return std::stol(value_, nullptr, static_cast<int>(radix_.value));
#else
            return std::stoll(value_, nullptr, static_cast<int>(radix_.value));
#endif
        } catch (std::invalid_argument&) {
        } catch (std::out_of_range&) { }

        return std::nullopt;
    }

public:
    /**
     * @brief Converts to string representation.
     *
     * @param radix The base of a system of number.
     * @return std::string representation of current value.
     */
    [[nodiscard]]
    std::string to_string(RadixFlag radix = RadixFlag::Decimal) const {
        std::stringstream ss;

        if (isNegative()) {
            ss << '-';
        }
        if (radix == RadixFlag::Decimal) {
            ss << value_;
        } else {
            ss << convertFromBaseTen(*this, radix);
        }
        return ss.str();
    }

private:
    // Sets the default value for an object whose state has been moved.
    static void setDefault(BigInteger& moved) {
        moved.radix_.value = RadixFlag::Decimal;
        moved.sign_.value = SignFlag::positive;
        moved.value_ = "0";
    }

    // Converts not base ten value to string.
    static std::string convertFromBaseTen(const BigInteger& value, const RadixFlag radix) {
        auto decimalValue{value};
        auto modulo = valueFrom(static_cast<std::uint8_t>(radix));

        std::string result;

        while (!decimalValue.equal(0)) {
            auto remainder = decimalValue.mod(modulo);
            decimalValue = decimalValue.divide(modulo);

            auto c = baseChars(RadixFlag::Hexadecimal).at(std::stoi(remainder.to_string()));
            result.push_back(c);
        }
        std::ranges::reverse(result);

        return result;
    }

    // Converts string value to base ten.
    static std::string convertToBaseTen(const std::string& value, RadixFlag radix) {
        auto last = __detail::charToInt32(value.back());
        auto length = value.length();

        auto power = valueFrom(length - 1);
        auto convertedValue = valueFrom(last);
        auto radixValue = valueFrom(static_cast<std::uint8_t>(radix));

        int current;

        for (std::size_t i = 0; i < length - 1; ++i) {
            current = __detail::charToInt32(value.at(i));
            convertedValue = convertedValue
                .add(valueFrom(current).multiply(radixValue.pow(power--)));
        }
        return std::move(convertedValue.value_);
    }
};

} // namespace wingmann::numerics

#endif // ALEF_NUMERICS_BIG_INTEGER_BIG_INTEGER_H

#include "operators.h"