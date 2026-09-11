#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>

BitcoinExchange::BitcoinExchange() {

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &date) : _db(date._db) {

}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &date) {
    if (this != &date)
        _db = date._db;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {

}

bool BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file((filename.data()));
    if (!file.is_open())
        return false;

    std::string line;
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
        ss >> value;
        _db[date] = value;
    }

    return true;
}
