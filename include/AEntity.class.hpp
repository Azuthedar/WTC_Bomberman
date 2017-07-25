#pragma once

#include <main.hpp>

class AEntity
{
	public:

		AEntity();
		AEntity(AEntity const & src);
		~AEntity();

		virtual void	movement();
		virtual void	collision();

	protected:

		int		_dir;
		int		_xPos;
		int		_yPos;
		bool	_isCollide;
		bool	_isDead;

};