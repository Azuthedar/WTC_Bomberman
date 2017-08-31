#pragma once

#include "main.hpp"
#include "AEntity.class.hpp"

class Explosion : public AEntity
{
	public:

		Explosion();
		Explosion(int x, int y);
		Explosion(Explosion const & src);
		~Explosion();

		void		collisions(std::vector<Wall> & wallVector);

	private:
};
