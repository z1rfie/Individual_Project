#include "shop.h"

Shop::Shop(const std::string& addr, const Time& open, const Time& close)
    : address(addr), openingTime(open), closingTime(close) {}

std::string Shop::getAddress() const { return address; }
Time Shop::getOpeningTime() const { return openingTime; }
Time Shop::getClosingTime() const { return closingTime; }

void Shop::setAddress(const std::string& addr) { address = addr; }
void Shop::setOpeningTime(const Time& time) { openingTime = time; }
void Shop::setClosingTime(const Time& time) { closingTime = time; }