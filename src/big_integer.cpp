#include "big_integer/big_integer.h"

using namespace wingmann::numerics;

const big_integer big_integer::zero_value{"0"};
const big_integer big_integer::one_value{"1"};
const big_integer big_integer::ten_value{"10"};
const std::string big_integer::base_char_value{"0123456789abcdefghijklmnopqrstuv"};

big_integer::big_integer(std::int32_t value) : signed_{value < 0} { *this = value; }

big_integer::big_integer(std::int64_t value) : signed_{value < 0} { *this = value; }

big_integer::big_integer(const char *value, int radix) : radix_{radix} { *this = value; }

big_integer::big_integer(const std::string& value, int radix) : radix_{radix} { *this = value; }

big_integer::big_integer(const big_integer &value) { *this = value; }

big_integer& big_integer::operator=(std::int32_t value) {
    *this = std::to_string(value);
    return *this;
}

big_integer& big_integer::operator=(std::int64_t value) {
    *this = std::to_string(value);
    return *this;
}

big_integer &big_integer::operator=(const char* value) {
    *this = std::string{value};
    return *this;
}

big_integer& big_integer::operator=(std::string value) {
    signed_ = value.starts_with('-');
    if (signed_)
        value.erase(0, 1);

    // Remove leading zero.
    while (value.starts_with('0') && (value.length() != 1))
        value.erase(0, 1);

    if (radix_ == 10) {
        value_ = value;
    } else {
        // Convert to base ten to use trivial algorithm.
        char last_char = value.back();
        int last = ('0' <= last_char) && (last_char <= '9')
            ? (last_char - '0')
            : (tolower(last_char) - 'a') + 10;

        auto value_length = static_cast<std::int64_t>(value.length());

        big_integer pow{value_length - 1};
        big_integer converted_value{last};
        big_integer bi_radix{radix_};

        for (int i = 0; i < value_length - 1; i++) {
            auto c = value.at(i);
            int current_value = ('0' <= c) && (c <= '9')
                ? (c - '0')
                : (tolower(c) - 'a') + 10;

            converted_value += big_integer(current_value).multiply(bi_radix.pow(pow--));
        }
        (*this) = signed_
            ? converted_value.negate()
            : converted_value;
    }
    return *this;
}

big_integer &big_integer::operator=(const big_integer &value) {
    this->radix_ = value.radix_;
    this->value_ = value.value_;
    this->signed_ = value.signed_;
    return *this;
}

big_integer big_integer::add(const big_integer& value) const {
    big_integer addition;

    if (signed_ && !value.signed_) {
        // (-a)+(+b)
        addition = value.subtract(negate());
    } else if (!signed_ && value.signed_) {
        // (+a)+(-b)
        addition = subtract(value.negate());
    } else {
        // (+a)+(+b) or (-a)+(-b)
        auto sum = value_;
        auto added = value.value_;

        auto difference_length = std::abs(int(sum.length() - added.length()));

        if (sum.length() > added.length())
            added.insert(0, difference_length, '0');
        else
            sum.insert(0, difference_length, '0');

        std::reverse(sum.begin(), sum.end());
        std::reverse(added.begin(), added.end());

        int index{};
        char carry{'0'};

        for (char& c : sum) {
            c = (carry - '0') + (c - '0') + (added.at(index) - '0') + '0';
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

        std::reverse(sum.begin(), sum.end());

        addition = signed_
            ? big_integer(sum).negate()
            : big_integer(sum);
    }
    return addition;
}

big_integer big_integer::subtract(const big_integer& value) const {
    big_integer subtraction;

    if ((signed_ && !value.signed_) || !signed_ && value.signed_) {
        // (-a)-(+b) or (+a)-(-b)
        subtraction = add(value.negate());
    } else {
        // (+a)-(+b) or (-a)-(-b)
        if (signed_) {
            subtraction = add(value.negate());
        } else {
            bool invert_sign = (compare(value) == -1);

            std::string sub = invert_sign ? value.value_ : value_;
            std::string removed = invert_sign ? value_ : value.value_;

            auto difference_length = std::abs(int(sub.length() - removed.length()));

            if (sub.size() > removed.size())
                removed.insert(0, difference_length, '0');
            else
                sub.insert(0, difference_length, '0');

            std::reverse(sub.begin(), sub.end());
            std::reverse(removed.begin(), removed.end());

            int index{};

            for (char& c : sub) {
                if (c < removed.at(index)) {
                    c += 10;
                    sub[index + 1]--;
                }
                c = (c - '0') - (removed.at(index) - '0') + '0';
                index++;
            }
            std::reverse(sub.begin(), sub.end());

            while (sub.front() == '0' && sub.length() != 1)
                sub.erase(0, 1);

            subtraction = (invert_sign ? big_integer(sub).negate() : big_integer(sub));
        }
    }
    return subtraction;
}

big_integer big_integer::multiply(const big_integer& value) const {
    big_integer multiplication;

    auto mul = value_;
    auto multiplied = value.value_;

    std::reverse(mul.begin(), mul.end());
    std::reverse(multiplied.begin(), multiplied.end());

    int step{};
    char carry{'0'};

    for (const char& c1 : mul) {
        auto current_operation = std::string{}.insert(0, step, '0');

        for (const char& c2 : multiplied) {
            unsigned char value = ((c1 - '0') * (c2 - '0')) + (carry - '0') + '0';
            carry = '0';

            if (value > '9') {
                while (value > '9') {
                    value -= 10;
                    carry++;
                }
            }
            current_operation.insert(0, 1, static_cast<char>(value));
        }

        if (carry > '0') {
            current_operation.insert(0, 1, carry);
            carry = '0';
        }
        multiplication += big_integer(current_operation);
        step++;
    }

    if (bool positive = (signed_ && value.signed_) || (!signed_ && !value.signed_); !positive)
        multiplication = multiplication.negate();

    return multiplication;
}

big_integer big_integer::divide(const big_integer& value) const {
    big_integer division;

    if (value == zero_value) {
        // Division by zero.
    } else if (value == one_value) {
        division = (*this);
    } else if (compare(value) == 0) {
        division = 1;
    } else {
        std::string dividend = value_;
        std::string quotient;
        std::string current_quotient;

        std::reverse(dividend.begin(), dividend.end());

        big_integer bi_abs = value.absolute();

        do {
            current_quotient.push_back(dividend.back());
            dividend.pop_back();

            big_integer bi_dividend(current_quotient);

            if (bi_dividend >= bi_abs) {
                big_integer n{2};

                while (bi_abs.multiply(n) <= bi_dividend)
                    n++;

                n--;
                quotient.append(n.to_string());
                current_quotient = bi_dividend.subtract(bi_abs.multiply(n)).to_string();
            } else {
                quotient.push_back('0');
            }
        } while (!dividend.empty());

        division = big_integer{quotient};
    }

    if (bool positive = (signed_ && value.signed_) || (!signed_ && !value.signed_); !positive)
        division = division.negate();

    return division;
}

big_integer big_integer::pow(const big_integer& value) const {
    big_integer temp;

    if (value == zero_value) {
        temp = one_value;
    } else if (value == one_value) {
        temp = (*this);
    } else {
        big_integer initial_value{*this};
        temp = (*this);

        for (big_integer i = one_value; i < value; i++)
            temp *= initial_value;
    }
    return temp;
}

big_integer big_integer::modulus(const big_integer& value) const {
    return subtract(value.multiply(divide(value)));
}

big_integer::size_type big_integer::bit_length() const {
    return to_string(2).length();
}

int big_integer::compare(const big_integer& value) const {
    int comparison;

    if (signed_ && !value.signed_) {
        // -a, +b
        comparison = -1;
    } else if (!signed_ && value.signed_) {
        // +a, -b
        comparison = 1;
    } else {
        // +a, +b or -a, -b
        if (value_.length() < value.value_.length()) {
            comparison = -1;
        } else if (value_.length() > value.value_.length()) {
            comparison = 1;
        } else {
            bool positive = !signed_;

            if (value_ < value.value_)
                comparison = (positive ? -1 : 1);
            else if (value_ > value.value_)
                comparison = (positive ? 1 : -1);
            else
                comparison = 0;
        }
    }
    return comparison;
}

big_integer big_integer::negate() const {
    std::string value = value_;
    return {(signed_ ? value : value.insert(0, 1, '-'))};
}

big_integer big_integer::absolute() const {
    return {is_positive() ? (*this) : negate()};
}

bool big_integer::is_positive() const {
    return !signed_;
}

bool big_integer::is_negative() const {
    return signed_;
}

void big_integer::swap(big_integer &value) {
    big_integer tmp = (*this);
    (*this) = value;
    value = tmp;
}

big_integer big_integer::operator+(const big_integer& value) {
    return add(value);
}

big_integer big_integer::operator+(const std::int32_t& value) {
    return add(big_integer{value});
}

big_integer big_integer::operator+(const std::int64_t& value) {
    return add(big_integer{value});
}

big_integer big_integer::operator-(const big_integer& value) {
    return subtract(value);
}

big_integer big_integer::operator-(const std::int32_t& value) {
    return subtract(value);
}

big_integer big_integer::operator-(const std::int64_t& value) {
    return subtract(value);
}

big_integer big_integer::operator*(const big_integer& value) {
    return multiply(value);
}

big_integer big_integer::operator*(const std::int32_t& value) {
    return multiply(value);
}

big_integer big_integer::operator*(const std::int64_t& value) {
    return multiply(value);
}

big_integer big_integer::operator/(const big_integer& value) {
    return divide(value);
}

big_integer big_integer::operator/(const std::int32_t& value) {
    return divide(value);
}

big_integer big_integer::operator/(const std::int64_t& value) {
    return divide(value);
}

big_integer big_integer::operator%(const big_integer& value) {
    return modulus(value);
}

big_integer big_integer::operator%(const std::int32_t& value) {
    return modulus(value);
}

big_integer big_integer::operator%(const std::int64_t& value) {
    return modulus(value);
}

big_integer big_integer::operator<<(const big_integer& value) const {
    auto bitwise_value = to_string(2);
    for (big_integer i = zero_value; i < value; i++)
        bitwise_value.push_back('0');

    return {bitwise_value, 2};
}

big_integer big_integer::operator>>(const big_integer& value) const {
    auto bitwise_value = to_string(2);
    for (big_integer i = zero_value; i < value && bitwise_value.length() > 0; i++)
        bitwise_value.pop_back();

    if (bitwise_value.empty())
        bitwise_value.push_back('0');

    return {bitwise_value, 2};
}

big_integer& big_integer::operator+=(const big_integer& value) {
    *this = add(value);
    return (*this);
}

big_integer& big_integer::operator+=(const std::int32_t& value) {
    *this = add(value);
    return (*this);
}

big_integer& big_integer::operator+=(const std::int64_t& value) {
    *this = add(value);
    return (*this);
}

big_integer& big_integer::operator-=(const big_integer& value) {
    *this = subtract(value);
    return *this;
}

big_integer& big_integer::operator-=(const std::int32_t& value) {
    *this = subtract(value);
    return *this;
}

big_integer& big_integer::operator-=(const std::int64_t& value) {
    *this = subtract(value);
    return *this;
}

big_integer& big_integer::operator*=(const big_integer& value) {
    *this = multiply(value);
    return *this;
}

big_integer& big_integer::operator*=(const std::int32_t& value) {
    *this = multiply(value);
    return *this;
}

big_integer& big_integer::operator*=(const std::int64_t& value) {
    *this = multiply(value);
    return *this;
}

big_integer& big_integer::operator/=(const big_integer& value) {
    *this = divide(value);
    return *this;
}

big_integer& big_integer::operator/=(const std::int32_t& value) {
    *this = divide(value);
    return *this;
}

big_integer& big_integer::operator/=(const std::int64_t& value) {
    *this = divide(value);
    return *this;
}

big_integer& big_integer::operator++() {
    *this = add(one_value);
    return *this;
}

const big_integer big_integer::operator++(int) {
    big_integer before_plus{*this};
    *this = add(one_value);
    return before_plus;
}

big_integer& big_integer::operator--() {
    *this = subtract(one_value);
    return *this;
}

const big_integer big_integer::operator--(int) {
    big_integer before_minus = (*this);
    *this = subtract(one_value);
    return before_minus;
}

bool big_integer::operator==(const big_integer& value) const {
    return compare(value) == 0;
}

bool big_integer::operator==(const std::int32_t& value) const {
    return compare(value) == 0;
}

bool big_integer::operator==(const std::int64_t& value) const {
    return compare(value) == 0;
}

bool big_integer::operator!=(const big_integer& value) const {
    return compare(value) != 0;
}

bool big_integer::operator!=(const std::int32_t& value) const {
    return compare(value) != 0;
}

bool big_integer::operator!=(const std::int64_t& value) const {
    return compare(value) != 0;
}

bool big_integer::operator<(const big_integer& value) const {
    return compare(value) == -1;
}

bool big_integer::operator<(const std::int32_t& value) const {
    return compare(value) == -1;
}

bool big_integer::operator<(const std::int64_t& value) const {
    return compare(value) == -1;
}

bool big_integer::operator>(const big_integer& value) const {
    return compare(value) == 1;
}

bool big_integer::operator>(const std::int32_t& value) const {
    return compare(value) == 1;
}

bool big_integer::operator>(const std::int64_t& value) const {
    return compare(value) == 1;
}

bool big_integer::operator<=(const big_integer& value) const {
    int cmp = compare(value);
    return (cmp == -1) || (cmp == 0);
}

bool big_integer::operator<=(const std::int32_t& value) const {
    int cmp = compare(value);
    return (cmp == -1) || (cmp == 0);
}

bool big_integer::operator<=(const std::int64_t& value) const {
    int cmp = compare(value);
    return (cmp == -1) || (cmp == 0);
}

bool big_integer::operator>=(const big_integer& value) const {
    auto cmp = compare(value);
    return (cmp == 0) || (cmp == 1);
}

bool big_integer::operator>=(const std::int32_t& value) const {
    auto cmp = compare(value);
    return (cmp == 0) || (cmp == 1);
}

bool big_integer::operator>=(const std::int64_t& value) const {
    auto cmp = compare(value);
    return (cmp == 0) || (cmp == 1);
}

std::ostream &wingmann::numerics::operator<<(std::ostream& os, const big_integer& value) {
    os << value.to_string();
    return os;
}

std::istream &wingmann::numerics::operator>>(std::istream& is, big_integer& value) {
    std::string input;
    is >> input;
    value = input;
    return is;
}

std::string big_integer::to_string(int radix) const {
    std::stringstream ss;
    if (signed_) ss << '-';

    if (radix == 10) {
        ss << value_;
    } else {
        big_integer decimal_value{*this};
        big_integer modulo{radix};

        std::string value;

        while (decimal_value != zero_value) {
            big_integer remain = decimal_value.modulus(modulo);
            decimal_value /= modulo;

            auto c = base_char_value.at(std::stoi(remain.to_string()));
            value.push_back(c);
        }
        std::reverse(value.begin(), value.end());
        ss << value;
    }
    return ss.str();
}
