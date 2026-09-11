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

bool BitcoinExchange::isValidDate(const std::string& date) const {
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
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    getline(file, line);
    while (getline(file, line)) {
        if (line.empty())
            return;
        std::size_t pos = line.find('|');
        if (pos == std::string::npos)
            std::cerr << "Error: bad input =>" << line << std::endl;

        std::string dateStr = line.substr(0, pos);
        std::string valueStr = line.substr(pos + 1);

        if (!isValidDate(dateStr)) {
            std::cerr << "Error: bad input =>" << dateStr << std::endl;
            return;
        }

    }
}
