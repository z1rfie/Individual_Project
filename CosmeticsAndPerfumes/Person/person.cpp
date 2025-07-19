#include <iostream>
#include "person.h"

Person::Person(const FIO& name, const Date& date, const Contact& contacts) : fio(name), birthDate(date) {}

FIO Person::getFIO() const { return fio; }
Date Person::getBirthDate() const { return birthDate; }
Contact Person::getContacts() const { return contacts; }