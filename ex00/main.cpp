#include "BitcoinExchange.hpp"
#include <iostream>

int main (int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Error: invalid arguments." << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    if (!btc.loadDatabase("data.csv")) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    btc.processInput(av[1]);

    return 0;
}