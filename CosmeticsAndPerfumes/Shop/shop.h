#include <string>
#include <iostream>
#include "time.h"
#pragma once

class Shop {
private:
    std::string address;
    Time openingTime;  
    Time closingTime; 

public:
    Shop(const std::string& addr, const Time& open, const Time& close);

    std::string getAddress() const;
    Time getOpeningTime() const;
    Time getClosingTime() const;

    void setAddress(const std::string& addr);
    void setOpeningTime(const Time& time);
    void setClosingTime(const Time& time);
};