#include "Robot.h"

Robot::Robot(const std::string& identifier, const std::string& classCode, std::tm manufactureDate) :
	_identifier(identifier),
	_classCode(classCode),
	_manufactureDate(manufactureDate)
{
}
