#pragma once

#include <ctime>
#include <string>

class Robot {
public:
	Robot(const std::string& identifier, const std::string& classCode, std::tm manufactureDate);

	const std::string& identifier() const { return _identifier; }
	const std::string& classCode() const { return _classCode; }

protected:
	std::string _identifier;
	std::string _classCode;
	std::tm _manufactureDate;

};

