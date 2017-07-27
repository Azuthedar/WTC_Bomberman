#pragma once

#include <main.hpp>

class Wall
{
    public:

        Wall();
        Wall(int x, int y, eBlockType type);
        Wall(Wall const & src);
        ~Wall();

        int     getXPos() const;
        int     getYPos() const;

        sf::Texture texture__; //TEMP MOFO, DELETE IT!
		sf::Sprite	sprite__; //ALSO TEMP!

    private:

        int         _xPos;
        int         _yPos;
        eBlockType  _blockType; 
};