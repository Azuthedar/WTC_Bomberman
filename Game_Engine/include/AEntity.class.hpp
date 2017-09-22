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
		virtual float			getZPos() const;
		virtual bool			getIsDead() const;

	protected:

		eMovementDir		_dir;
		float				_xPos;
		float				_yPos;
		float				_zPos;
		bool				_isCollide;
		bool				_isDead;

};
