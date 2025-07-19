#include "document.h"

bool Document::isValidSeries(unsigned int series) const {
    return series <= 9999;
}

bool Document::isValidNumber(unsigned int number) const {
    return number <= 999999;
}

Document::Document() : name(""), series(0), number(0) {}
Document::Document(const std::string& name, unsigned int series, unsigned int number)
    : name(name) {
    setSeries(series);
    setNumber(number);
}
std::string Document::getName() const { return name; }
unsigned int Document::getSeries() const { return series; }
unsigned int Document::getNumber() const { return number; }

void Document::setName(const std::string& newName) { name = newName; }

void Document::setSeries(unsigned int newSeries) {
    if (!isValidSeries(newSeries)) {
        throw std::invalid_argument("Серия должна быть не более 4 цифр");
    }
    series = newSeries;
}

void Document::setNumber(unsigned int newNumber) {
    if (!isValidNumber(newNumber)) {
        throw std::invalid_argument("Номер должен быть не более 6 цифр");
    }
    number = newNumber;
}

bool Document::isValid() const {
    return !name.empty() && series != 0 && number != 0;
}