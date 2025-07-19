#include <iostream>
#include <stdexcept>
#include <string>
#pragma once

class Contact {
    std::string _phoneNumber;
    std::string _email;
public:
    Contact() = default;
    Contact(const std::string& phone, const std::string& email);
    Contact(const Contact&);

    void setPhoneNumber(const std::string& phone);
    void setEmail(const std::string& email);

    std::string getPhoneNumber() const;
    std::string getEmail() const;
};
