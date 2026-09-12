#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

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

bool BitcoinExchange::isValidDate(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    for (size_t i = 0; i < date.size(); i++) {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);

    int year, month, day;
    std::stringstream ssYear(yearStr);
    std::stringstream ssMonth (monthStr);
    std::stringstream ssDay(dayStr);

    if (!(ssYear >> year) || !(ssMonth >> month) || !(ssDay>> day))
        return false;

    if (month < 1 || month > 12)
        return false;

    int daysInMonth[12] = {
        31, 28, 31, 30,
        31, 30, 31, 31,
        30, 31, 30, 31
    };

    int max = daysInMonth[month - 1];
    if (month == 2) {
        bool leapYear = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
        if (leapYear)
            max = 29;
    }

    if (day < 1 || day > max)
        return false;

    return true;
}

bool BitcoinExchange::getRate(const std::string& date, double& rate) const {
    std::map<std::string, double>::const_iterator it = _db.upper_bound(date);
    if (it == _db.begin())
        return false;
    --it;
    rate = it->second;
    return true;
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

void BitcoinExchange::processLine(const std::string &line) const {
    std::size_t pos = line.find('|');
    if (pos == std::string::npos) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    std::string dateStr = line.substr(0, pos);
    std::string valueStr = line.substr(pos + 1);

    std::size_t a = dateStr.find_first_not_of(" \t");
    std::size_t b = dateStr.find_last_not_of(" \t");

    if (a == std::string::npos)
        dateStr = "";
    else
        dateStr = dateStr.substr(a, b - a + 1);

    std::size_t c = valueStr.find_first_not_of(" \t");
    std::size_t d = valueStr.find_last_not_of(" \t");
    if (c == std::string::npos)
        valueStr = "";
    else
        valueStr = valueStr.substr(c, d - c + 1);

    if (!isValidDate(dateStr)) {
        std::cerr << "Error: bad input => " << dateStr << std::endl;
        return;
    }

    double value;
    std::stringstream ss(valueStr);
    if (!(ss >> value) || !ss.eof()) {
        std::cerr << "Error: bad input => " << valueStr << std::endl;
        return;
    }

    if (value < 0 ) {
        std::cerr << "Error: not a positive number." << std::endl;
        return;
    }

    if (value > 1000) {
        std::cerr << "Error: too large a number." << std::endl;
        return;
    }

    double rate;
    if (!getRate(dateStr, rate)) {
        std::cerr << "Error: bad input => " << dateStr << std::endl;
        return;
    }
    std::cout << dateStr << " => " << value << " = " << value * rate <<  std::endl;
}

void BitcoinExchange::processInput(const std::string& filename) const {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;

        if (line == "date | value")
            continue;

        processLine(line);
    }
}
