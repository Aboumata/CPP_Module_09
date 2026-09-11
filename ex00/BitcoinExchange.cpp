#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _db() {

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &date) {
    _db = date._db;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &date) {
    if (this != &date)
        _db = date._db;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {

}
