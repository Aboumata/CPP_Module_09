#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, double> _db;
    bool isValidDate(const std::string& date) const;
    double getRate(const std::string& date) const;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& date);
    BitcoinExchange& operator=(const BitcoinExchange& date);
    ~BitcoinExchange();

    bool loadDatabase(const std::string& filename);
    void processInput(const std::string& filename);
};

#endif
