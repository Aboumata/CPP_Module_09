#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, double> _db;
    bool isValidDate(const std::string& date) const;
    bool getRate(const std::string& date, double& rate) const;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    bool loadDatabase(const std::string& filename);
    void processInput(const std::string& filename);
};

#endif
