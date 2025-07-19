#include "contacts.h"

Contact::Contact(const std::string& phone, const std::string& email) {
    setPhoneNumber(phone);
    setEmail(email);
}

void Contact::setPhoneNumber(const std::string& phone) {
    if (phone.empty()) {
        throw std::invalid_argument("������� �� ����� ���� ������!");
    }
    if (phone.length() != 11) {
        throw std::invalid_argument("����� �������� �������� 11 ����!");
    }
    _phoneNumber = phone;
}

void Contact::setEmail(const std::string& email) {
    if (email.empty()) {
        throw std::invalid_argument("����� �� ����� ���� ������!");
    }
    _email = email;
}

std::string Contact::getPhoneNumber() const { return _phoneNumber; }
std::string Contact::getEmail() const { return _email; }