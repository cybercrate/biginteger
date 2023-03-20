#ifndef ALEF_NUMERICS_BIGINTEGER_OPERATORS_H
#define ALEF_NUMERICS_BIGINTEGER_OPERATORS_H

#include "./biginteger.h"

ALEF_GLOBAL_NAMESPACE_BEGIN

namespace num {

// Arithmetic operators ----------------------------------------------------------------------------

/// @brief Adds value.
///
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return    Result of addition.
///
static biginteger operator+(const biginteger& lhs, const biginteger& rhs) {
    return lhs.add(rhs);
}

/// @brief Subtracts value.
///
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return    Result of subtraction.
///
static biginteger operator-(const biginteger& lhs, const biginteger& rhs) {
    return lhs.subtract(rhs);
}

/// @brief Multiples value.
///
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return    Result of multiplication.
///
static biginteger operator*(const biginteger& lhs, const biginteger& rhs) {
    return lhs.multiply(rhs);
}

/// @brief Divides value.
///
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return    Result of division.
///
static biginteger operator/(const biginteger& lhs, const biginteger& rhs) {
    return lhs.divide(rhs);
}

/// @brief Computes remainder.
///
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return    Remainder of division current value by right side value.
///
static biginteger operator%(const biginteger& lhs, const biginteger& rhs) {
    return lhs.mod(rhs);
}

/// @brief Adds the right operand to the current value and assigns the result.
///
/// @param rhs The value to add to the current value.
/// @return    Modified object.
///
static biginteger& operator+=(biginteger& lhs, const biginteger& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

/// @brief Subtracts the right operand from the current value and assigns the result.
///
/// @param rhs The value to subtract from the current value.
/// @return    Modified object.
///
static biginteger& operator-=(biginteger& lhs, const biginteger& rhs) {
    lhs = lhs - rhs;
    return lhs;
}

/// @brief Multiplies the current value by the right operand and assigns the result.
///
/// @param rhs The value to multiply by current value.
/// @return    Modified object.
///
static biginteger& operator*=(biginteger& lhs, const biginteger& rhs) {
    lhs = lhs * rhs;
    return lhs;
}

/// @brief Divides the current value by the right operand and assigns the result.
///
/// @param rhs The value by which to divide the current value.
/// @return    Modified object.
///
static biginteger& operator/=(biginteger& lhs, const biginteger& rhs) {
    lhs = lhs / rhs;
    return lhs;
}

/// @brief Gets the remainder of the current value divided by the right operand
/// and assigns the result.
///
/// @param rhs The right operand for taking the remainder.
/// @return    Modified object.
///
static biginteger& operator%=(biginteger& lhs, const biginteger& rhs) {
    lhs = lhs % rhs;
    return lhs;
}

// Shift operators ---------------------------------------------------------------------------------

/// @brief Shifts the current value to left on right operand value.
///
/// @param lhs The value to be moved to the right.
/// @param rhs The value to shift right on.
/// @return    Shifted current value.
///
static biginteger operator<<(const biginteger& lhs, const biginteger& rhs) {
    return lhs.shift_left(rhs);
}

/// @brief Shifts the current value to right on right operand value.
///
/// @param lhs The value to be moved to the left.
/// @param rhs The value to shift left on.
/// @return    Shifted current value.
///
static biginteger operator>>(const biginteger& lhs, const biginteger& rhs) {
    return lhs.shift_right(rhs);
}

/// @brief Shifts the current value to left on right operand value and assigns the result.
///
/// @param rhs The value to shift_right on.
/// @return    Modified object.
///
static biginteger& operator<<=(biginteger& lhs, const biginteger& rhs) {
    lhs = lhs << rhs;
    return lhs;
}

/// @brief Shifts the current value to left on right operand value and assigns the result.
///
/// @param rhs The value to shift_right on.
/// @return    Modified object.
///
static biginteger& operator>>=(biginteger& lhs, const biginteger& rhs) {
    lhs = lhs >> rhs;
    return lhs;
}

// Comparison operators ----------------------------------------------------------------------------

/// @brief Three way compares the current value and right side operand.
///
/// @param rhs The value to compere with the current value.
/// @return    Result of comparison.
///
static std::strong_ordering operator<=>(const biginteger& lhs, const biginteger& rhs){
    return lhs.compare(rhs);
}

/// @brief Compares the current value and right side operand.
///
/// @param rhs The value to compare with the current value.
/// @return    Result of comparison.
///
static auto operator==(const biginteger& lhs, const biginteger& rhs) {
    return lhs.equal(rhs);
}

// Stream operators --------------------------------------------------------------------------------

/// @brief Puts the value to the output stream.
///
/// @param os    The output stream.
/// @param value The value to put to output.
/// @return      Output stream.
///
static std::ostream& operator<<(std::ostream& os, const biginteger& value) {
    os << value.to_string();
    return os;
}

/// @brief Gets the value from input stream.
///
/// @param is    Input stream.
/// @param value The value for writing from input stream.
/// @return      Input stream.
///
static std::istream& operator>>(std::istream& is, biginteger& value) {
    std::string input;
    is >> input;
    value = input;
    return is;
}

} // namespace num

ALEF_GLOBAL_NAMESPACE_END

#endif // ALEF_NUMERICS_BIGINTEGER_OPERATORS_H