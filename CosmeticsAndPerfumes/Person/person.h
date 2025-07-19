#include "fio.h"
#include "date.h"
#include "contacts.h"
#pragma once

class Person {
protected:
    FIO fio;  
    Date birthDate;   
    Contact contacts;  

public:
    Person(const FIO&, const Date&, const Contact&);

    FIO getFIO() const;
    Date getBirthDate() const;
    Contact getContacts() const;
};