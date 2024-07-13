#include "expression.hpp"

void Val::print(std::ostream &os) const {
    os << value;
}

int64_t Val::eval() const {
    return value;
}

int64_t Val::eval(const Context& context) const {
    return value;
}

void Add::print(std::ostream &os) const {
    os << "(";
    left->print(os);
    os << " + ";
    right->print(os);
    os << ")";
}

int64_t Add::eval() const {
    return left->eval() + right->eval();
}

int64_t Add::eval(const Context& context) const {
    return left->eval(context) + right->eval(context);
}

void Mul::print(std::ostream &os) const{
    left->print(os);
    os << " * ";
    right->print(os);
}

int64_t Mul::eval() const {
    return left->eval() * right->eval();
}

int64_t Mul::eval(const Context& context) const {
    return left->eval(context) * right->eval(context);
}

void Var::print(std::ostream &os) const {
    os << variable;
}

int64_t Var::eval() const {
    throw std::runtime_error("Context is not setted!");
}

int64_t Var::eval(const Context& context) const {
    return context.getVar(variable);
}

int64_t Context::getVar(std::string const& name) const {
    if (!varIsSet(name)) {
        throw std::runtime_error("Variable with name: " + name + "is not found!");
    }
    return variables.at(name);
}

void Context::setVar(std::string const& name, int64_t value)  {
    variables[name] = value;
}

bool Context::varIsSet(std::string const& name) const {
    return variables.count(name) > 0;
}
