#pragma once

#include <main.hpp>
#include <Wall.class.hpp>

class AEntity
{
	public:

		AEntity();
		AEntity(AEntity const & src);
		~AEntity();

		virtual void			movement(std::vector<Wall> & wall);
		
		/* Setters */
		virtual void			setDir(eMovementDir dir);
		virtual void			setXPos(int xPos);
		virtual void			setYPos(int xPos);
		virtual void			setIsDead(bool dead);

		/* Getters */
		virtual eMovementDir	getDir() const;
		virtual int				getXPos() const;
		virtual int				getYPos() const;
		virtual bool			getIsDead() const;

	protected:

		eMovementDir		_dir;
		int					_xPos;
		int					_yPos;
		bool				_isCollide;
		bool				_isDead;

};