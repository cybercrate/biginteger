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
#include <cctype>

namespace wingmann::numerics {

class big_integer {
    int radix_{10};
    bool signed_{};
    std::string value_{"0"};

public:
    big_integer() = default;
    big_integer(const big_integer& value) { *this = value; };
    big_integer(const big_integer&& value) noexcept { *this = value; };
    big_integer(int value) : signed_{value < 0} { *this = value; }
    big_integer(std::int64_t value) : signed_{value < 0} { *this = value; }
    big_integer(const char* value, int radix = 10) : radix_{radix} { *this = value; }
    big_integer(std::string value, int radix = 10) : radix_{radix} { *this = std::move(value); }

    virtual ~big_integer() = default;

public:
    // Assignment operators.
    big_integer& operator=(const big_integer& rhs) noexcept {
        this->radix_ = rhs.radix_;
        this->value_ = rhs.value_;
        this->signed_ = rhs.signed_;
        return *this;
    }

    big_integer& operator=(const big_integer&& rhs) noexcept {
        this->radix_ = rhs.radix_;
        this->value_ = rhs.value_;
        this->signed_ = rhs.signed_;
        return *this;
    }

    big_integer& operator=(int rhs) {
        *this = std::to_string(rhs);
        return *this;
    }

    big_integer& operator=(std::int64_t rhs) {
        *this = std::to_string(rhs);
        return *this;
    }

    big_integer& operator=(const char* rhs) {
        *this = std::string{rhs};
        return *this;
    }

    big_integer& operator=(std::string rhs) {
        this->signed_ = rhs.starts_with('-');
        if (this->signed_)
            rhs.erase(0, 1);

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
        *this = this->signed_
            ? converted_value.negate()
            : std::move(converted_value);

        return *this;
    }

    big_integer& operator+=(const big_integer& rhs) {
        *this = add(rhs);
        return *this;
    }

    big_integer& operator+=(const int& rhs) {
        *this = add(rhs);
        return *this;
    }

    big_integer& operator+=(const std::int64_t& rhs) {
        *this = add(rhs);
        return *this;
    }

    big_integer& operator-=(const big_integer& rhs) {
        *this = subtract(rhs);
        return *this;
    }

    big_integer& operator-=(const int& rhs) {
        *this = subtract(rhs);
        return *this;
    }

    big_integer& operator-=(const std::int64_t& rhs) {
        *this = subtract(rhs);
        return *this;
    }

    big_integer& operator*=(const big_integer& rhs) {
        *this = multiply(rhs);
        return *this;
    }

    big_integer& operator*=(const int& rhs) {
        *this = multiply(rhs);
        return *this;
    }

    big_integer& operator*=(const std::int64_t& rhs) {
        *this = multiply(rhs);
        return *this;
    }

    big_integer& operator/=(const big_integer& rhs) {
        *this = divide(rhs);
        return *this;
    }

    big_integer& operator/=(const int& rhs) {
        *this = divide(rhs);
        return *this;
    }

    big_integer& operator/=(const std::int64_t& rhs) {
        *this = divide(rhs);
        return *this;
    }

    // Arithmetic operators.
    big_integer operator+(const big_integer& rhs) const {
        return add(rhs);
    }

    big_integer operator+(const int& rhs) const {
        return add(rhs);
    }

    big_integer operator+(const std::int64_t& rhs) const {
        return add(rhs);
    }

    big_integer operator-(const big_integer& rhs) const {
        return subtract(rhs);
    }

    big_integer operator-(const int& rhs) const {
        return subtract(rhs);
    }

    big_integer operator-(const std::int64_t& rhs) const {
        return subtract(rhs);
    }

    big_integer operator*(const big_integer& rhs) const {
        return multiply(rhs);
    }

    big_integer operator*(const int& rhs) const {
        return multiply(rhs);
    }

    big_integer operator*(const std::int64_t& rhs) const {
        return multiply(rhs);
    }

    big_integer operator/(const big_integer& rhs) const {
        return divide(rhs);
    }

    big_integer operator/(const int& rhs) const {
        return divide(rhs);
    }

    big_integer operator/(const std::int64_t& rhs) const {
        return divide(rhs);
    }

    big_integer operator%(const big_integer& rhs) const {
        return mod(rhs);
    }

    big_integer operator%(const int& rhs) const {
        return mod(rhs);
    }

    big_integer operator%(const std::int64_t& rhs) const {
        return mod(rhs);
    }

    // Increment operators.
    big_integer& operator++() {
        *this = add(value_from<1>());
        return *this;
    }

    const big_integer operator++(int) {
        auto before_plus{std::move(*this)};
        *this = add(value_from<1>());
        return before_plus;
    }

    // Decrement operators.
    big_integer& operator--() {
        *this = subtract(value_from<1>());
        return *this;
    }

    const big_integer operator--(int) {
        auto before_minus{std::move(*this)};
        *this = subtract(value_from<1>());
        return before_minus;
    }

    // Shift operators.
    big_integer operator<<(const big_integer& rhs) const {
        auto bitwise_value = to_string(2);
        for (auto i = value_from<0>(); i < rhs; i++)
            bitwise_value.push_back('0');

        return {bitwise_value, 2};
    }

    big_integer operator>>(const big_integer& rhs) const {
        auto bitwise_value = to_string(2);
        for (auto i = value_from<0>(); i < rhs && bitwise_value.length() > 0; i++)
            bitwise_value.pop_back();

        if (bitwise_value.empty())
            bitwise_value.push_back('0');

        return {bitwise_value, 2};
    }

    // Comparison operators.
    bool operator==(const big_integer& rhs) const {
        return compare(rhs) == 0;
    }

    bool operator==(const int& rhs) const {
        return compare(rhs) == 0;
    }

    bool operator==(const std::int64_t& rhs) const {
        return compare(rhs) == 0;
    }

    bool operator!=(const big_integer& rhs) const {
        return compare(rhs) != 0;
    }

    bool operator!=(const int& rhs) const {
        return compare(rhs) != 0;
    }

    bool operator!=(const std::int64_t& rhs) const {
        return compare(rhs) != 0;
    }

    bool operator<(const big_integer& rhs) const {
        return compare(rhs) == -1;
    }

    bool operator<(const int& rhs) const {
        return compare(rhs) == -1;
    }

    bool operator<(const std::int64_t& rhs) const {
        return compare(rhs) == -1;
    }

    bool operator>(const big_integer& rhs) const {
        return compare(rhs) == 1;
    }

    bool operator>(const int& rhs) const {
        return compare(rhs) == 1;
    }

    bool operator>(const std::int64_t& rhs) const {
        return compare(rhs) == 1;
    }

    bool operator<=(const big_integer& rhs) const {
        auto compared = compare(rhs);
        return (compared == -1) || (compared == 0);
    }

    bool operator<=(const int& rhs) const {
        auto compared = compare(rhs);
        return (compared == -1) || (compared == 0);
    }

    bool operator<=(const std::int64_t& rhs) const {
        auto compared = compare(rhs);
        return (compared == -1) || (compared == 0);
    }

    bool operator>=(const big_integer& rhs) const {
        auto compared = compare(rhs);
        return (compared == 0) || (compared == 1);
    }

    bool operator>=(const int& rhs) const {
        auto compared = compare(rhs);
        return (compared == 0) || (compared == 1);
    }

    bool operator>=(const std::int64_t& rhs) const {
        auto compared = compare(rhs);
        return (compared == 0) || (compared == 1);
    }

    // Stream operators.
    friend std::ostream& operator<<(std::ostream& os, const big_integer& value) {
        os << value.to_string();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, big_integer& value) {
        std::string input;
        is >> input;
        value = input;
        return is;
    }

public:
    // Basic arithmetic.
    [[nodiscard]]
    big_integer add(const big_integer& rhs) const {
        if (this->signed_ && !rhs.signed_)
            return rhs.subtract(negate()); // (-a)+(+b)
        else if (!this->signed_ && rhs.signed_)
            return subtract(rhs.negate()); // (+a)+(-b)

        // (+a)+(+b) or (-a)+(-b)
        auto lhs_value = this->value_;
        auto rhs_value = rhs.value_;

        auto difference_length = std::abs(
            static_cast<int>(lhs_value.length() - rhs_value.length()));

        if (lhs_value.length() > rhs_value.length())
            rhs_value.insert(0, difference_length, '0');
        else
            lhs_value.insert(0, difference_length, '0');

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

    [[nodiscard]]
    big_integer subtract(const big_integer& rhs) const {
        // (-a)-(+b) or (+a)-(-b)
        if ((this->signed_ && !rhs.signed_) || !this->signed_ && rhs.signed_)
            return add(rhs.negate());

        // (+a)-(+b) or (-a)-(-b)
        if (this->signed_)
            return add(rhs.negate());

        bool inverted_sign = (compare(rhs) == -1);

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
        if (auto positive = (this->signed_ && rhs.signed_) || (!this->signed_ && !rhs.signed_); !positive)
            temp = temp.negate();

        return temp;
    }

    [[nodiscard]]
    big_integer divide(const big_integer& rhs) const {
        if (rhs == value_from<0>())
            return {};
        else if (rhs == value_from<1>())
            return *this;
        else if (compare(rhs) == 0)
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
            big_integer number{2};

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

    // Complex arithmetic.
    [[nodiscard]]
    big_integer pow(const big_integer& rhs) const {
        if (rhs == value_from<0>())
            return std::move(value_from<1>());
        else if (rhs == value_from<1>())
            return *this;

        auto init_value{*this};
        auto temp{*this};

        for (auto i = value_from<1>(); i < rhs; i++)
            temp *= init_value;

        return temp;
    }

    [[nodiscard]]
    big_integer mod(const big_integer& rhs) const {
        return subtract(rhs.multiply(divide(rhs)));
    }

    // Modification and checking.
    [[nodiscard]]
    std::size_t bit_length() const {
        return to_string(2).length();
    }

    [[nodiscard]]
    int compare(const big_integer& rhs) const {
        if (this->signed_ && !rhs.signed_)
            return -1; // -a, +b
        else if (!this->signed_ && rhs.signed_)
            return 1; // +a, -b

        // +a, +b or -a, -b
        if (this->value_.length() < rhs.value_.length())
            return -1;
        else if (this->value_.length() > rhs.value_.length())
            return 1;

        bool positive = !this->signed_;

        if (this->value_ < rhs.value_)
            return positive ? -1 : 1;
        else if (this->value_ > rhs.value_)
            return positive ? 1 : -1;

        return {};
    }

    [[nodiscard]]
    big_integer negate() const {
        std::string value{this->value_};
        return this->signed_ ? value : value.insert(0, 1, '-');
    }

    [[nodiscard]]
    big_integer abs() const {
        return is_positive() ? *this : negate();
    }

    [[nodiscard]]
    bool is_positive() const {
        return !this->signed_;
    }

    [[nodiscard]]
    bool is_negative() const {
        return !is_positive();
    }

    void swap(big_integer& rhs) {
        std::swap(*this, rhs);
    }

    template<std::int64_t value>
    static big_integer value_from() {
        return std::to_string(value);
    }

    template<std::integral T>
    std::optional<T> to_integer() {
        try {
            return static_cast<T>(std::stoll(to_string()));
        } catch (std::out_of_range&) {
        } catch (std::invalid_argument&) {
        }
        return std::nullopt;
    }

    template<std::floating_point T>
    std::optional<T> to_floating() {
        try {
            return static_cast<T>(std::stod(to_string()));
        } catch (std::out_of_range&) {
        } catch (std::invalid_argument&) {
        }
        return std::nullopt;
    }

    [[nodiscard]]
    std::string to_string(int radix = 10) const {
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
    static std::string base_char_value() {
        return "0123456789abcdefghijklmnopqrstuv";
    }
};

} // namespace wingmann::numerics

#endif // WINGMANN_BIGINTEGER_H
