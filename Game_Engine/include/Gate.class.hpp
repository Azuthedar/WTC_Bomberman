#pragma once

#include "main.hpp"
#include "AEntity.class.hpp"

class Gate : public AEntity
{
	public:

		Gate();
		Gate(int x, int y);
		~Gate();

		void		setExists(bool exists);
		void		setIsLocked(bool isLocked);

		bool &		getExists();
		bool &		getIsLocked();

	private:

		bool	_exists;
		bool	_isLocked;
};
