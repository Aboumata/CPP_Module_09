#include "PmergeMe.hpp"
#include <string>
#include <sstream>
#include <climits>

PmergeMe::PmergeMe() {

}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq) {

}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != & other) {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {

}

bool PmergeMe::parse(int ac, char **av) {
    for (int i = 0; i < ac; i++) {
        std::string token = av[i];

        if (token.empty())
            return false;

        for (int j = 0; token[j] != '\0'; j++) {
            char c = token[j];
            if (!isdigit(static_cast<unsigned char> (c)))
                return false;
        }

        std::stringstream ss(token);
        long n;
        if (!(ss >> n) || !ss.eof())
            return false;
        if (n > INT_MAX)
            return false;
    }

    return true;
}