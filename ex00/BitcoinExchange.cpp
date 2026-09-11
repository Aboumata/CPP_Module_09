#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>

BitcoinExchange::BitcoinExchange() {

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _db(other._db) {

}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other)
        _db = other._db;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {

}

bool BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        return false;

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        std::size_t pos = line.find(',');
        if (pos == std::string::npos)
            continue;

        std::string date = line.substr(0, pos);
        std::string rate = line.substr(pos + 1);

        double value;
        std::stringstream ss(rate);
        if (!(ss >> value))
            continue;
        _db[date] = value;
    }

    return true;
}

void BitcoinExchange::processInput(const std::string& filename) {

}
