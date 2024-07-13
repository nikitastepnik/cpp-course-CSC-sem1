#pragma once

#include <iostream>
#include <unordered_map>
#include <stdexcept>

class Context {
private:
    std::unordered_map<std::string, int64_t> variables;
public:
    Context() = default;

    // бросает исключение, если переменной нет
    int64_t getVar(std::string const& name) const;

    // перезаписывает переменную, если она уже есть
    void setVar(std::string const& name, int64_t value);

    // проверяет, выставлено ли значение переменной в контексте
    bool varIsSet(std::string const& name) const;
};

class Expression {
public:
    virtual void print(std::ostream &os) const = 0;
    virtual int64_t eval() const = 0;
    virtual int64_t eval(Context const& context) const = 0;
    virtual ~Expression() = default;
};

class Val : public Expression {
private:
    int64_t value;

public:
    Val(int64_t val) {
        value=val;
    }

    void print(std::ostream &os) const override;
    int64_t eval() const override;
    int64_t eval(const Context& context) const override;

    void* operator new(size_t size);
    void operator delete(void* ptr);
};

class Add : public Expression {
private:
    Expression* left = nullptr;
    Expression* right = nullptr;
    Add& operator=(const Add& other);


public:
    Add(Expression* leftExpr, Expression* rightExpr) {
        left=leftExpr;
        right=rightExpr;
    }
    Add(const Add&) = delete;


    void print(std::ostream &os) const override;
    int64_t eval() const override;
    int64_t eval(const Context& context) const override;

    void* operator new(size_t size);
    void operator delete(void* ptr);
};

class Mul : public Expression {
private:
    Expression* left = nullptr;
    Expression* right = nullptr;
    Mul& operator=(const Mul& other);

public:
    Mul(Expression* leftExpr, Expression* rightExpr) {
        left=leftExpr;
        right=rightExpr;
    }
    Mul(const Mul&) = delete;

    void print(std::ostream &os) const override;
    int64_t eval() const override;
    int64_t eval(const Context& context) const override;

    void* operator new(size_t size);
    void operator delete(void* ptr);
};


class Var : public Expression {
private:
    std::string variable;
public:
    Var(std::string var) {
        variable=var;
    }
    int64_t eval() const override;
    int64_t eval(const Context& context) const override;
    void print(std::ostream &os) const override;
};

