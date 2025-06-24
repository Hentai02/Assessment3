#include "Vitals.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const Vitals& p)
{
	os << p.POWER() << "," << p.PRESSURE() << "," << p.CONNECTION();
	return os;
}
