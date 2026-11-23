#ifndef QUADRATIC_H
#define QUADRATIC_H
#include <iostream>

enum class ValueType {
    Real,
    Complex
};

class Error {
private:
    char* msg;
public:
    Error(const char* m);
    Error(const Error& other);
    ~Error();
    const char* what() const;
};

class Value {
public:
    virtual ~Value() {};
    
    virtual Value* CreateZeroValue() const = 0;
    virtual Value* Duplicate() const = 0;
    virtual ValueType GetType() const = 0;
    
    virtual Value& operator+=(const Value& other) = 0;
    virtual Value& operator-=(const Value& other) = 0;
    virtual Value& operator*=(const Value& other) = 0;
    virtual Value& operator/=(const Value& other) = 0;
    
    virtual void Sqrt() = 0;
    virtual void Print() const = 0;
};

class RealValue: public Value {
private:
    double value;
public:
    RealValue(double v = 0.0);
    
    ValueType GetType() const override;
    Value* CreateZeroValue() const override;
    Value* Duplicate() const override;
        
    Value& operator+=(const Value& other) override;
    Value& operator-=(const Value& other) override;
    Value& operator*=(const Value& other) override;
    Value& operator/=(const Value& other) override;
    
    void Sqrt() override;
    void Print() const override;
};

class ComplexValue: public Value {
private:
    double re, im;
public:
    ComplexValue(double r = 0.0, double i = 0.0);
    
    ValueType GetType() const override;
    Value* CreateZeroValue() const override;
    Value* Duplicate() const override;

    Value& operator+=(const Value& other) override;
    Value& operator-=(const Value& other) override;
    Value& operator*=(const Value& other) override;
    Value& operator/=(const Value& other) override;
    
    void Sqrt() override;
    void Print() const override;
};

void Solve(Value& a, Value& b, Value& c, Value*& result1, Value*& result2);

#endif
