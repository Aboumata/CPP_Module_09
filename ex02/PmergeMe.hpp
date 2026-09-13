#ifndef CPP_MODULE_09_PMERGEME_HPP
#define CPP_MODULE_09_PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe {
private:
    std::vector<int> _vec;
    std::deque<int> _deq;
    std::vector<std::string> _input;

    void sortVector(std::vector<int>& v);
    void sortDeque(std::deque<int>& d);
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    bool parse(int ac, char **av);
    void run();
};

#endif
