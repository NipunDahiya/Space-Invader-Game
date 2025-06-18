#include "Enemy.h"

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount*4);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));

}

void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->type = 0;
	this->speed = static_cast <float>(this->pointCount/2);
	this->hpMax = static_cast<int>(this->pointCount*2);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
}

Enemy::Enemy(float pos_x,float pos_y)
{
	this->shape.setPosition(pos_x, pos_y);
	this->initVariables();
	this->initShape();


}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

//Accessors 



void Enemy::update()
{
	this->shape.move(0, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
