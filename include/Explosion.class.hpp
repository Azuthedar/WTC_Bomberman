#pragma once

#include <main.hpp>
#include <AEntity.class.hpp>

class Explosion : public AEntity
{
	public:

		Explosion();
		Explosion(int x, int y);
		Explosion(Explosion const & src);
		~Explosion();

		sf::Texture texture__; //TEMP MOFO, DELETE IT!
		sf::Sprite	sprite__; //ALSO TEMP!

	private:
};