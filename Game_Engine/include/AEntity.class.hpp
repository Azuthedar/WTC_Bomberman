#pragma once

#include "main.hpp"
#include "Wall.class.hpp"

class AEntity
{
	public:

		AEntity();

		AEntity(AEntity const & src);
        AEntity &operator=(AEntity const& rhs);

	    virtual ~AEntity();

		/* Setters */
		virtual void			setDir(eMovementDir dir);
		virtual void			setXPos(int xPos);
		virtual void			setYPos(int xPos);
		virtual void			setIsDead(bool dead);

		/* Getters */
		virtual eMovementDir	getDir() const;
		virtual float			getXPos() const;
		virtual float			getYPos() const;
		virtual bool			getIsDead() const;

	protected:

		eMovementDir		_dir;
		float				_xPos;
		float				_yPos;
		bool				_isCollide;
		bool				_isDead;

};
