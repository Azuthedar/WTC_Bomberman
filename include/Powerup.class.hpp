#pragma once

#include "main.hpp"
#include "AEntity.class.hpp"

class Powerup : public AEntity
{
	public:

		Powerup();
		Powerup(int x, int y);
		~Powerup();

		void        randomPowerup();

		ePowerups &	getTypePowerup();
		Powerup	&	getPowerup();

	private:

		ePowerups	_typePowerup;

};
