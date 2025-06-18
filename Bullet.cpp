#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture* texture,float pos_x,float pos_y,float dirX, float dirY, float move_Speed)
{
	this->shape.setTexture(*texture);
	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dirX;
	this->direction.y = dirY;
	this->moveSpeed = move_Speed;
	this->shape.scale(0.5f, 0.5f);

}

Bullet::~Bullet()
{

}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::update()
{
	//Update the movement 
	this->shape.move(this->moveSpeed * this->direction); 


}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
