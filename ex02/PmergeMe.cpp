#include "PmergeMe.hpp"
#include <string>
#include <sstream>
#include <climits>
#include <iostream>
#include <sys/time.h>

PmergeMe::PmergeMe() {

}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq), _input(other._input){

}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != & other) {
        _vec = other._vec;
        _deq = other._deq;
        _input = other._input;
    }
    return *this;
}

PmergeMe::~PmergeMe() {

}

void PmergeMe::sortVector(std::vector<int>& v) {
    if (v.size() < 2)
        return;
    bool hasStraggler = (v.size() % 2 == 1);
    int  straggler = hasStraggler ? v[v.size() - 1] : 0;

    std::vector <std::pair<int, int> > pairs;
    for (std::size_t i = 0; i + 1 < v.size(); i += 2) {
        if (v[i] > v[i + 1])
            pairs.push_back(std::make_pair(v[i], v[i + 1 ]));
        else
            pairs.push_back(std::make_pair(v[i + 1], v[i]));
    }

    std::vector<int> winners;
    winners.reserve(pairs.size());
    for (std::size_t i = 0; i < pairs.size(); ++i)
        winners.push_back(pairs[i].first);
    sortVector(winners);

    std::vector<bool> used (pairs.size(), false);
    std::vector<int> pend;
    
    for (std::size_t i = 0; i < winners.size() ; ++i) {
        for (std::size_t j = 0; j < pairs.size(); ++j) {
            if (!used[j] && pairs[j].first == winners[i]) {
                used[j] = true;
                pend.push_back(pairs[j].second);
                break;
            }
        }
    }

    std::vector<int> main = winners;
    main.insert(main.begin(), pend[0]);
}

void PmergeMe::sortDeque(std::deque<int>& d) {
    (void) d;
}

bool PmergeMe::parse(int ac, char **av) {
    for (int i = 1; i < ac; i++) {
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

        _input.push_back(token);
    }

    return true;
}

void PmergeMe::run() {
    _vec.clear();
    _deq.clear();

    std::cout << "Before: ";
    for (std::size_t i = 0; i < _input.size(); i++)
        std::cout << _input[i] << " ";
    std::cout << std::endl;

    timeval s1 = {};
    timeval e1 = {};

    gettimeofday(&s1, NULL);
    for (std::size_t i = 0; i < _input.size(); ++i) {
        std::stringstream ss(_input[i]);
        int n;
        ss >> n;
        _vec.push_back(n);
    }

    sortVector(_vec);
    gettimeofday(&e1, NULL);

    long vectorTime = (e1.tv_sec - s1.tv_sec)  * 1000000L
                    + (e1.tv_usec - s1.tv_usec);

    timeval s2 = {};
    timeval e2 = {};
    gettimeofday(&s2, NULL);
    for (std::size_t i = 0; i < _input.size(); ++i) {
        std::stringstream ss(_input[i]);
        int n;
        ss >> n;
        _deq.push_back(n);
    }
    sortDeque(_deq);
    gettimeofday(&e2, NULL);

    long dequeTime = (e2.tv_sec - s2.tv_sec)  * 1000000L
                + (e2.tv_usec - s2.tv_usec);


    std::cout << "After: ";
    for (std::size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of "
              <<  _vec.size()
              << " elements with std::vector : "
              << vectorTime << " us" << std::endl;

    std::cout << "Time to process a range of "
          <<  _deq.size()
          << " elements with std::deque : "
          << dequeTime << " us" << std::endl;
}
