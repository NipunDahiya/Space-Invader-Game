#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <map>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <vector>
#include <sstream>
#include <string>


class Game
{
private:

	//Window 
	sf::RenderWindow* window;

	//Resources 
	std::map <std::string,sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	
	//PLayer
	Player* player;

	// Enemies 
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;


	//GUI 
	sf::Font font;
	sf::Text pointText;

	sf::Text GameOverText;


	//World 
	sf::Sprite worldBACKGROND;
	sf::Texture worldBACKGROUNDTEXTURE;

	//Systems 
	unsigned points;

	sf::RectangleShape playerHPBAR;
	sf::RectangleShape playerHPBARBACK;


	//Private Functions 
	void initWindow();
	void initTextures();
	void initSystems();
	void initGUI();
	void initWorld();
	void updateGUI();
	void renderGUI();
	void initPlayer();
	void initEnemies();
	void initPLAYERGUI();


public:

	Game();
	virtual ~Game();

	// Funtions 
	void run();

	void updatePollEvents();
	void updateInput();
	void updateBullets();
	void updateEnemiesandCombat();
	void updateWorld();
	void updateCollision();
	void renderWORLD();
	void update();
	void render();


};

