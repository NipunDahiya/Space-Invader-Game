#pragma once

#include <SFML/Graphics.hpp>



class Enemy
{
private:
	unsigned pointCount;
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVariables();
	void initShape();



public:
	Enemy(float pos_x, float pos_y);
	virtual~Enemy();

	//Accessors 
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;


	// Funtions 

	void update();
	void render(sf::RenderTarget* target);

};

