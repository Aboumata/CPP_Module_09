#include "RPN.hpp"
#include <sstream>
#include <cctype>


RPN::RPN() {

}

RPN::RPN(const RPN& other) : _stack(other._stack){

}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _stack = other._stack;
    }
    return *this;
}

RPN::~RPN() {

}

bool RPN::applyOperator(const std::string& token) {
    if (_stack.size() < 2)
        return false;
    int b = _stack.top(); _stack.pop();
    int a = _stack.top(); _stack.pop();

    switch (token[0]) {
        case '+':
            _stack.push(a + b);
            break;
        case '-':
            _stack.push(a - b);
            break;
        case '*':
            _stack.push(a * b);
            break;
        case '/':
            if (b == 0)
                return false;
            _stack.push(a / b);
            break;
        default:
            return false;
    }

    return true;
}

bool RPN::evaluate(const std::string& expr, int& result) {
    std::stringstream ss(expr);
    std::string token;

    while (ss >> token) {
        if (token.size() == 1 && isdigit(token[0]))
            _stack.push(token[0] - '0');
        else if (token.size() == 1 &&
        (token[0] == '+' ||
         token[0] == '-' ||
         token[0] == '*' ||
         token[0] == '/')) {
            if (!applyOperator(token))
                return false;
        }
        else
            return false;
    }

    if (_stack.size() != 1)
        return false;

    result = _stack.top();
    return true;
}
