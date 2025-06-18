#include "Player.h"

void Player::initTexture()
{
	//Load a texture from a file 
	this->texture.loadFromFile("Textures/lol1.png");
}

void Player::initSprite()
{
	//Set the texture to a sprite 
	this->sprite.setTexture(this->texture);

	//Resize the Sprite 
	this->sprite.scale(0.1f, 0.1f);
}



Player::Player()
{	
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int Player::getHP() const
{
	return this->hp;
}

const int Player::getHPMAX() const
{
	return this->hpMAX;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);

}

void Player::setPosition(const float x, float const y)
{

	this->sprite.setPosition(x, y);
}

void Player::setHP(const int hp)
{
	this->hp = hp;
}

void Player::loseHP(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::initVariables()
{
	this->moveSpeed = 6.f;
	this->attackCoolDownMax = 2.f;
	this->attackCoolDown = attackCoolDownMax;
	this->hpMAX = 50; 
	this->hp = this->hpMAX;

}

const bool Player::canAttack()
{
	if (this->attackCoolDown >= this->attackCoolDownMax)
	{
		this->attackCoolDown = 0.f;
		return true;
	}
	return false;
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->moveSpeed*dirX,this->moveSpeed*dirY);
}

void Player::updateAttack()
{	if(this->attackCoolDown < this->attackCoolDownMax)
		this->attackCoolDown += 0.5f;
}

void Player::update()
{	
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
