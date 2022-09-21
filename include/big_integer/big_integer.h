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
    big_integer& operator=(const big_integer& value) noexcept {
        this->radix_ = value.radix_;
        this->value_ = value.value_;
        this->signed_ = value.signed_;
        return *this;
    }

    big_integer& operator=(const big_integer&& value) noexcept {
        this->radix_ = value.radix_;
        this->value_ = value.value_;
        this->signed_ = value.signed_;
        return *this;
    }

    big_integer& operator=(int value) {
        *this = std::to_string(value);
        return *this;
    }

    big_integer& operator=(std::int64_t value) {
        *this = std::to_string(value);
        return *this;
    }

    big_integer& operator=(const char* value) {
        *this = std::string{value};
        return *this;
    }

    big_integer& operator=(std::string value) {
        signed_ = value.starts_with('-');
        if (signed_)
            value.erase(0, 1);

        // Remove leading zero.
        while (value.starts_with('0') && (value.length() != 1))
            value.erase(0, 1);

        if (radix_ == 10) {
            value_ = value;
            return *this;
        }
        // Convert to base ten to use trivial algorithm.
        char last_char = value.back();
        int last = ('0' <= last_char) && (last_char <= '9')
            ? (last_char - '0')
            : (tolower(last_char) - 'a') + 10;

        auto value_length = static_cast<std::int64_t>(value.length());

        big_integer pow{value_length - 1};
        big_integer converted_value{last};
        big_integer radix_value{radix_};

        for (int i = 0; i < value_length - 1; i++) {
            auto c = value.at(i);
            int current_value = ('0' <= c) && (c <= '9')
                ? (c - '0')
                : (tolower(c) - 'a') + 10;

            converted_value += big_integer{current_value}.multiply(radix_value.pow(pow--));
        }
        *this = signed_
            ? converted_value.negate()
            : std::move(converted_value);

        return *this;
    }

    big_integer& operator+=(const big_integer& value) {
        *this = add(value);
        return *this;
    }

    big_integer& operator+=(const int& value) {
        *this = add(value);
        return *this;
    }

    big_integer& operator+=(const std::int64_t& value) {
        *this = add(value);
        return *this;
    }

    big_integer& operator-=(const big_integer& value) {
        *this = subtract(value);
        return *this;
    }

    big_integer& operator-=(const int& value) {
        *this = subtract(value);
        return *this;
    }

    big_integer& operator-=(const std::int64_t& value) {
        *this = subtract(value);
        return *this;
    }

    big_integer& operator*=(const big_integer& value) {
        *this = multiply(value);
        return *this;
    }

    big_integer& operator*=(const int& value) {
        *this = multiply(value);
        return *this;
    }

    big_integer& operator*=(const std::int64_t& value) {
        *this = multiply(value);
        return *this;
    }

    big_integer& operator/=(const big_integer& value) {
        *this = divide(value);
        return *this;
    }

    big_integer& operator/=(const int& value) {
        *this = divide(value);
        return *this;
    }

    big_integer& operator/=(const std::int64_t& value) {
        *this = divide(value);
        return *this;
    }

    // Arithmetic operators.
    big_integer operator+(const big_integer& value) const {
        return add(value);
    }

    big_integer operator+(const int& value) const {
        return add(value);
    }

    big_integer operator+(const std::int64_t& value) const {
        return add(value);
    }

    big_integer operator-(const big_integer& value) const {
        return subtract(value);
    }

    big_integer operator-(const int& value) const {
        return subtract(value);
    }

    big_integer operator-(const std::int64_t& value) const {
        return subtract(value);
    }

    big_integer operator*(const big_integer& value) const {
        return multiply(value);
    }

    big_integer operator*(const int& value) const {
        return multiply(value);
    }

    big_integer operator*(const std::int64_t& value) const {
        return multiply(value);
    }

    big_integer operator/(const big_integer& value) const {
        return divide(value);
    }

    big_integer operator/(const int& value) const {
        return divide(value);
    }

    big_integer operator/(const std::int64_t& value) const {
        return divide(value);
    }

    big_integer operator%(const big_integer& value) const {
        return modulus(value);
    }

    big_integer operator%(const int& value) const {
        return modulus(value);
    }

    big_integer operator%(const std::int64_t& value) const {
        return modulus(value);
    }

    // Increment operators.
    big_integer& operator++() {
        return *this = add(value_from<1>());
    }

    const big_integer operator++(int) {
        auto before_plus{std::move(*this)};
        *this = add(value_from<1>());
        return before_plus;
    }

    // Decrement operators.
    big_integer& operator--() {
        return *this = subtract(value_from<1>());
    }

    const big_integer operator--(int) {
        auto before_minus{std::move(*this)};
        *this = subtract(value_from<1>());
        return before_minus;
    }

    // Shift operators.
    big_integer operator<<(const big_integer& value) const {
        auto bitwise_value = to_string(2);
        for (auto i = value_from<0>(); i < value; i++)
            bitwise_value.push_back('0');

        return {bitwise_value, 2};
    }

    big_integer operator>>(const big_integer& value) const {
        auto bitwise_value = to_string(2);
        for (auto i = value_from<0>(); i < value && bitwise_value.length() > 0; i++)
            bitwise_value.pop_back();

        if (bitwise_value.empty())
            bitwise_value.push_back('0');

        return {bitwise_value, 2};
    }

    // Comparison operators.
    bool operator==(const big_integer& value) const {
        return compare(value) == 0;
    }

    bool operator==(const int& value) const {
        return compare(value) == 0;
    }

    bool operator==(const std::int64_t& value) const {
        return compare(value) == 0;
    }

    bool operator!=(const big_integer& value) const {
        return compare(value) != 0;
    }

    bool operator!=(const int& value) const {
        return compare(value) != 0;
    }

    bool operator!=(const std::int64_t& value) const {
        return compare(value) != 0;
    }

    bool operator<(const big_integer& value) const {
        return compare(value) == -1;
    }

    bool operator<(const int& value) const {
        return compare(value) == -1;
    }

    bool operator<(const std::int64_t& value) const {
        return compare(value) == -1;
    }

    bool operator>(const big_integer& value) const {
        return compare(value) == 1;
    }

    bool operator>(const int& value) const {
        return compare(value) == 1;
    }

    bool operator>(const std::int64_t& value) const {
        return compare(value) == 1;
    }

    bool operator<=(const big_integer& value) const {
        auto compared = compare(value);
        return (compared == -1) || (compared == 0);
    }

    bool operator<=(const int& value) const {
        auto compared = compare(value);
        return (compared == -1) || (compared == 0);
    }

    bool operator<=(const std::int64_t& value) const {
        auto compared = compare(value);
        return (compared == -1) || (compared == 0);
    }

    bool operator>=(const big_integer& value) const {
        auto compared = compare(value);
        return (compared == 0) || (compared == 1);
    }

    bool operator>=(const int& value) const {
        auto compared = compare(value);
        return (compared == 0) || (compared == 1);
    }

    bool operator>=(const std::int64_t& value) const {
        auto compared = compare(value);
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
    big_integer add(const big_integer& value) const {
        if (signed_ && !value.signed_)
            return value.subtract(negate()); // (-a)+(+b)
        else if (!signed_ && value.signed_)
            return subtract(value.negate()); // (+a)+(-b)

        // (+a)+(+b) or (-a)+(-b)
        auto sum = value_;
        auto added = value.value_;

        auto difference_length = std::abs(int(sum.length() - added.length()));

        if (sum.length() > added.length())
            added.insert(0, difference_length, '0');
        else
            sum.insert(0, difference_length, '0');

        std::ranges::reverse(sum);
        std::ranges::reverse(added);

        int index{};
        char carry{'0'};

        for (char& c : sum) {
            c = static_cast<char>((carry - '0') + (c - '0') + (added.at(index) - '0') + '0');
            if (c > '9') {
                c -= 10;
                carry = '1';
            } else {
                carry = '0';
            }
            index++;
        }
        if (carry > '0')
            sum.append(1, carry);

        std::ranges::reverse(sum);

        return signed_ ? big_integer{sum}.negate() : sum;
    }

    [[nodiscard]]
    big_integer subtract(const big_integer& value) const {
        // (-a)-(+b) or (+a)-(-b)
        if ((signed_ && !value.signed_) || !signed_ && value.signed_)
            return add(value.negate());

        // (+a)-(+b) or (-a)-(-b)
        if (signed_)
            return add(value.negate());

        bool invert_sign = (compare(value) == -1);

        std::string sub = invert_sign ? value.value_ : value_;
        std::string removed = invert_sign ? value_ : value.value_;

        auto difference_length = std::abs(int(sub.length() - removed.length()));

        if (sub.size() > removed.size())
            removed.insert(0, difference_length, '0');
        else
            sub.insert(0, difference_length, '0');

        std::ranges::reverse(sub);
        std::ranges::reverse(removed);

        int index{};

        for (char& c : sub) {
            if (c < removed.at(index)) {
                c += 10;
                sub[index + 1]--;
            }
            c = static_cast<char>((c - '0') - (removed.at(index) - '0') + '0');
            index++;
        }
        std::ranges::reverse(sub);

        while (sub.front() == '0' && sub.length() != 1)
            sub.erase(0, 1);

        return invert_sign ? big_integer{sub}.negate() : sub;
    }

    [[nodiscard]]
    big_integer multiply(const big_integer& value) const {
        big_integer temp;

        auto mul = value_;
        auto multiplied = value.value_;

        std::ranges::reverse(mul);
        std::ranges::reverse(multiplied);

        int step{};
        char carry{'0'};

        for (const char& c1 : mul) {
            auto current_operation = std::string{}.insert(0, step, '0');

            for (const char& c2 : multiplied) {
                unsigned char c_value = ((c1 - '0') * (c2 - '0')) + (carry - '0') + '0';
                carry = '0';

                if (c_value > '9') {
                    while (c_value > '9') {
                        c_value -= 10;
                        carry++;
                    }
                }
                current_operation.insert(0, 1, static_cast<char>(c_value));
            }

            if (carry > '0') {
                current_operation.insert(0, 1, carry);
                carry = '0';
            }
            temp += current_operation;
            step++;
        }

        if (auto positive = (signed_ && value.signed_) || (!signed_ && !value.signed_); !positive)
            temp = temp.negate();

        return temp;
    }

    [[nodiscard]]
    big_integer divide(const big_integer& value) const {
        if (value == value_from<0>())
            return {}; // todo: division by zero
        else if (value == value_from<1>())
            return *this;
        else if (compare(value) == 0)
            return 1;

        auto dividend = value_;
        std::ranges::reverse(dividend);

        auto absolute_value = value.absolute();

        std::string quotient;
        std::string current_quotient;

        do {
            current_quotient.push_back(dividend.back());
            dividend.pop_back();

            big_integer dividend_value{current_quotient};

            if (dividend_value >= absolute_value) {
                big_integer n{2};

                while (absolute_value.multiply(n) <= dividend_value)
                    n++;
                n--;
                quotient.append(n.to_string());
                current_quotient = dividend_value
                    .subtract(absolute_value.multiply(n))
                    .to_string();
            } else {
                quotient.push_back('0');
            }
        } while (!dividend.empty());

        if (bool positive = (signed_ && value.signed_) || (!signed_ && !value.signed_); !positive)
            return big_integer{quotient}.negate();

        return quotient;
    }

    // Complex arithmetic.
    [[nodiscard]]
    big_integer pow(const big_integer& value) const {
        if (value == value_from<0>())
            return std::move(value_from<1>());
        else if (value == value_from<1>())
            return *this;

        auto initial_value{*this};
        auto temp{*this};

        for (auto i = value_from<1>(); i < value; i++)
            temp *= initial_value;

        return temp;
    }

    [[nodiscard]]
    big_integer modulus(const big_integer& value) const {
        return subtract(value.multiply(divide(value)));
    }

    // Modification and checking.
    [[nodiscard]]
    std::size_t bit_length() const {
        return to_string(2).length();
    }

    [[nodiscard]]
    int compare(const big_integer& value) const {
        if (signed_ && !value.signed_)
            return -1; // -a, +b
        else if (!signed_ && value.signed_)
            return 1; // +a, -b

        // +a, +b or -a, -b
        if (value_.length() < value.value_.length())
            return -1;
        else if (value_.length() > value.value_.length())
            return 1;

        bool positive = !signed_;

        if (value_ < value.value_)
            return positive ? -1 : 1;
        else if (value_ > value.value_)
            return positive ? 1 : -1;

        return {};
    }

    [[nodiscard]]
    big_integer negate() const {
        std::string value{value_};
        return signed_ ? value : value.insert(0, 1, '-');
    }

    [[nodiscard]]
    big_integer absolute() const {
        return is_positive() ? *this : negate();
    }

    [[nodiscard]]
    bool is_positive() const {
        return !signed_;
    }

    [[nodiscard]]
    bool is_negative() const {
        return signed_;
    }

    void swap(big_integer& value) {
        std::swap(*this, value);
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
        if (signed_) ss << '-';

        if (radix == 10) {
            ss << value_;
            return ss.str();
        }
        auto decimal_value{*this};
        big_integer modulo{radix};

        std::string value;

        while (decimal_value != value_from<0>()) {
            auto remain{decimal_value.modulus(modulo)};
            decimal_value /= modulo;

            auto c = base_char_value().at(std::stoi(remain.to_string()));
            value.push_back(c);
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
