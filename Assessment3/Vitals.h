#pragma once

#include <iostream>

class Vitals
{
public:
	Vitals(float power, int pressure, int connection) :
		_powerSupply(power),
		_pneumaticsPressure(pressure),
		_connectionStrength(connection)
	{ }

	float POWER() const { return _powerSupply; }
	int PRESSURE() const { return _pneumaticsPressure; }
	int CONNECTION() const { return _connectionStrength; }

	friend std::ostream& operator<<(std::ostream& os, const Vitals& p);

protected:
	float _powerSupply;
	int _pneumaticsPressure;
	int _connectionStrength;
};

