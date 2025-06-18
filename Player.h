#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>



class Player

{

private:
	sf::Sprite sprite;
	sf::Texture texture;

	float moveSpeed;

	float attackCoolDown;
	float attackCoolDownMax;

	int hp;
	int hpMAX;



	//Private Funtions 
	void initTexture();
	void initSprite();


public:
	Player();
	virtual ~Player();

	//Accessor 
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int getHP() const;
	const int getHPMAX() const;

	//Modifiers 
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x,float const y);
	void setHP(const int hp);
	void loseHP(const int value);


	//Funtions 


	void initVariables();
	const bool canAttack();
	void move(const float dirX, const float dirY);
	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);

};

