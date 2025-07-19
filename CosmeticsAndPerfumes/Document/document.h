#include <string>
#include <iostream>
#include <stdexcept>

class Document {
private:
    std::string name;       
    unsigned int series;   
    unsigned int number;   
public:
    Document();
    Document(const std::string&, unsigned int, unsigned int);

    std::string getName() const;
    unsigned int getSeries() const;
    unsigned int getNumber() const;

    void setName(const std::string& newName);
    void setSeries(unsigned int newSeries);
    void setNumber(unsigned int newNumber);

    bool isValid() const;
private:
    bool isValidSeries(unsigned int series) const;
    bool isValidNumber(unsigned int number) const;
};
