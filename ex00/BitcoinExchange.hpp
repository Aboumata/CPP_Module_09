#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, double> _db;

    static bool isValidDate(const std::string& date);
    bool getRate(const std::string& date, double& rate) const;
    void processLine(const std::string& line) const;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    bool loadDatabase(const std::string& filename);
    void processInput(const std::string& filename) const;
};

#endif
