#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet

{
private:
	sf::Sprite shape;

	sf::Vector2f direction;
	float moveSpeed; 


public:
	Bullet();
	Bullet(sf::Texture* texture,float pos_x,float pos_y,float dirX,float dirY,float move_Speed);
	virtual ~Bullet();

	//Accessor 
	const sf::FloatRect getBounds() const;


	void update();
	void render(sf::RenderTarget* target);
};

