#include <Player.class.hpp>
#include <main.hpp>

Player::Player()
{
	this->_lives = 3;
	this->_score = 0;
	this->_isCollide = false;
	this->_canPlaceBombs = false;
	return ;
}

Player::Player(Player const & src)
{
	*this = src;
	return ;
}

Player::~Player()
{
	this->_isDead = false;
	std::cout << "Player has been destroyed" << std::endl;
	return ;
}

void	Player::movement()
{
	this->_xPos++;
	this->_yPos++;
}

void	Player::collision()
{
	this->_isCollide = true;
}