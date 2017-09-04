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

		bool &		getExists();

	private:

		bool	_exists;
};
