#include "person.h"
#include "date.h"
#pragma once

class Buyer : Person {
	Date registration;
	unsigned int ID;
public:
	Buyer();
};