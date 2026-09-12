#ifndef CPP_MODULE_09_RPN_HPP
#define CPP_MODULE_09_RPN_HPP

#include <string>
#include <stack>
#include <list>

class RPN {
private:
    std::stack<int, std::list<int> > _stack;
    bool applyOperator(const std::string& token);
public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    bool evaluate (const std::string& expr, int& result);
};

#endif
