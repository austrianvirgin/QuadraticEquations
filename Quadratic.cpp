#include "Quadratic.h"
#include <cstring>
#include <cmath>

// class Error //

Error::Error(const char* m) {
    msg = new char[std::strlen(m) + 1];
    std::strcpy(msg, m);
}

Error::Error(const Error& other) {
    msg = new char[std::strlen(other.msg) + 1];
    std::strcpy(msg, other.msg);
}
Error::~Error() { delete[] msg; }
const char* Error::what() const { return msg; }

// class RealValue //

RealValue::RealValue(double v) : value(v) {}

ValueType RealValue::GetType() const { return ValueType::Real; }
Value* RealValue::CreateZeroValue() const { return new RealValue(0.0); }
Value* RealValue::Duplicate() const { return new RealValue(value); }

Value& RealValue::operator+=(const Value& other) {
    if (other.GetType() != ValueType::Real)
        throw Error("Нельзя складывать Real и Complex");
    const RealValue& r = static_cast<const RealValue&>(other);
    value += r.value;
    return *this;
}

Value& RealValue::operator-=(const Value& other) {
    if (other.GetType() != ValueType::Real)
        throw Error("Нельзя вычитать Real и Complex");
    const RealValue& r = static_cast<const RealValue&>(other);
    value -= r.value;
    return *this;
}

Value& RealValue::operator*=(const Value& other) {
    if (other.GetType() != ValueType::Real)
        throw Error("Нельзя перемножать Real и Complex");
    const RealValue& r = static_cast<const RealValue&>(other);
    value *= r.value;
    return *this;
}

Value& RealValue::operator/=(const Value& other) {
    if (other.GetType() != ValueType::Real)
        throw Error("Нельзя делить Real и Complex");
    const RealValue& r = static_cast<const RealValue&>(other);
    if ((r.value < 1e-20) && (r.value > -1e-20))
        throw Error("Нельзя делить на ноль");
    value /= r.value;
    return *this;
}

void RealValue::Sqrt() {
    if (value < 0)
        throw Error("Корень из отрицательного числа не определен в случае Real");
    value = std::sqrt(value);
}

void RealValue::Print() const { std::cout << value; }

// class ComplexValue //

ComplexValue::ComplexValue(double r, double i): re(r), im(i) {}

ValueType ComplexValue::GetType() const { return ValueType::Complex; }
Value* ComplexValue::CreateZeroValue() const { return new ComplexValue(0.0, 0.0); }
Value* ComplexValue::Duplicate() const { return new ComplexValue(re, im); }

Value& ComplexValue::operator+=(const Value& other) {
    if (other.GetType() != ValueType::Complex)
        throw Error("Нельзя складывать Real и Complex");
    const ComplexValue& c = static_cast<const ComplexValue&>(other);
    re += c.re; im += c.im;
    return *this;
}

Value& ComplexValue::operator-=(const Value& other) {
    if (other.GetType() != ValueType::Complex)
        throw Error("Нельзя вычитать Real и Complex");
    const ComplexValue& c = static_cast<const ComplexValue&>(other);
    re -= c.re; im -= c.im;
    return *this;
}

Value& ComplexValue::operator*=(const Value& other) {
    if (other.GetType() != ValueType::Complex)
        throw Error("Нельзя перемножать Real и Complex");
    const ComplexValue& c = static_cast<const ComplexValue&>(other);
    double new_re = re * c.re - im * c.im;
    double new_im = re * c.im + im * c.re;
    re = new_re; im = new_im;
    return *this;
}

Value& ComplexValue::operator/=(const Value& other) {
    if (other.GetType() != ValueType::Complex)
        throw Error("Нельзя делить Real и Complex");
    const ComplexValue& c = static_cast<const ComplexValue&>(other);
    double denom = c.re * c.re + c.im * c.im;
    if ((denom > -1e-20) && (denom < 1e-20))
        throw Error("Нельзя делить на ноль");
    double new_re = (re * c.re + im * c.im) / denom;
    double new_im = (re * c.im - im * c.re) / denom;
    re = new_re; im = new_im;
    return *this;
}

void ComplexValue::Sqrt() {
    double r = std::sqrt(re * re + im * im);
    double new_re = std::sqrt((r + re) / 2.0);
    double new_im = std::sqrt((r - re) / 2.0);
    if (im < 0) new_im = -new_im;
    re = new_re; im = new_im;
}

void ComplexValue::Print() const {
    if (std::abs(im) < 1e-20) { std::cout << re; }
    else if (std::abs(re) < 1e-20) { std::cout << (im > 0 ? "" : "- ") << std::abs(im) << "i"; }
    else { std::cout << re << (im > 0 ? " + " : " - ") << std::abs(im) << "i"; }
}

void Solve(Value& a, Value& b, Value& c, Value*& result1, Value*& result2) {

    Value* b_sqrt = nullptr;
    Value* ac = nullptr;
    Value* four_ac = nullptr;
    Value* D = nullptr;
    Value* neg_b = nullptr;
    Value* two_a = nullptr;

    try {
        b_sqrt = b.Duplicate();
        *b_sqrt *= b;

        ac = a.Duplicate();
        *ac *= c;

        four_ac = a.Duplicate();
        *four_ac *= c;
        *four_ac += *ac;
        *four_ac += *ac;
        *four_ac += *ac;

        D = b_sqrt -> Duplicate();
        *D -= *four_ac;
        D -> Sqrt();

        neg_b = b.CreateZeroValue();
        *neg_b -= b;

        two_a = a.Duplicate();
        *two_a += a;

        result1 = neg_b -> Duplicate();
        *result1 += *D;
        *result1 /= *two_a;

        result2 = neg_b -> Duplicate();
        *result2 -= *D;
        *result2 /= *two_a;

        delete b_sqrt; delete ac; delete two_a;
        delete four_ac; delete D; delete neg_b;
    }
    catch (...) {
        delete b_sqrt; delete ac; delete two_a;
        delete four_ac; delete D; delete neg_b;
    }
}
