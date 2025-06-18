#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1100,900),"SPACE PIRATES",sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false); // I HAVE NO IDEA WHAT THIS IS 

}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/01.png");
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initGUI()
{
	//Load font and everything
	this->font.loadFromFile("C:/Users/91958/source/repos/SFML C++ 3/Fonts/Dosis-Light.otf");

	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(40);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("TEXT");


	this->GameOverText.setFont(this->font);
	this->GameOverText.setCharacterSize(70);
	this->GameOverText.setPosition(this->window->getSize().x/2-this->GameOverText.getGlobalBounds().width/2-150, this->window->getSize().y / 2.f - this->GameOverText.getGlobalBounds().height / 2.f - 75);
	this->GameOverText.setFillColor(sf::Color::White);
	this->GameOverText.setString("GAME OVER");


	

	// INIT PLAYER GUI  
	this->playerHPBAR.setSize(sf::Vector2f(300.f, 20.f));
	this->playerHPBAR.setFillColor(sf::Color::Red);
	this->playerHPBAR.setPosition(sf::Vector2f(0.f, 50.f));
	this->playerHPBARBACK = this->playerHPBAR;
	this->playerHPBARBACK.setFillColor(sf::Color(25, 25, 25, 200));

}

void Game::initWorld()
{
	this->worldBACKGROUNDTEXTURE.loadFromFile("Textures/SPACE2.png");
	this->worldBACKGROND.setTexture(this->worldBACKGROUNDTEXTURE);
	

}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "POINTS : " << this->points;
	this->pointText.setString(ss.str());

	// UPDATE PLAYER GUI 
	float hpPercent = static_cast<float>(this->player->getHP())/ this->player->getHPMAX();
	std::cout << "lol = " << hpPercent<<this->player->getHP()<< "\n";
	this->playerHPBAR.setSize(sf::Vector2f(300*hpPercent, this->playerHPBAR.getSize().y));



}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHPBARBACK);
	this->window->draw(this->playerHPBAR);
}

void Game::initPlayer()
{
	this->player = new Player();

}

void Game::initEnemies()
{
	this->spawnTimerMax = 40.f;
	this->spawnTimer = this->spawnTimerMax;

}

//PLAYER GUI 

void Game::initPLAYERGUI()
{
}

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initPlayer();
	this->initEnemies();
	this->initSystems();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete Textures 
	for (auto& i : this->textures)
	{
		delete i.second;

	}


	//Delete Bullets 
	for (auto* i : this->bullets)
	{
		delete i;
	}

	//Delete Enemies 

	for (auto* j : this->enemies)
	{
		delete j;
	}

}


// Functions 
void Game::run()
{	
	while (this->window->isOpen()) 
	{
		this->updatePollEvents();
		if(this->player->getHP()>0)
			this->update();
		this->updateGUI();
		this->render();
	}

}

void Game::updatePollEvents()
{

	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();

		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();

	}
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],this->player->getPos().x + 16, this->player->getPos().y, 0.f, -1.f, 5.f));
	}


}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto *bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (Top of screen )
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete the bullet 
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin()+counter);
			--counter;
		}
		
		++counter;
	}
}

void Game::updateEnemiesandCombat()
{
	this->spawnTimer += 1.f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand()%this->window->getSize().x-40.f, -100.f));
		this->spawnTimer = 0.f;
	}
	for (int i=0;i<this->enemies.size();++i)
	{
		bool enemy_removed = false;
		this->enemies[i]->update();

		for (size_t k = 0; k < this->bullets.size() && !enemy_removed; ++k)
		{
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();
				this->bullets.erase(this->bullets.begin() + k);
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;

			}
		}

		//Remove enemies when they go below the screen 

		if (!enemy_removed) {
			if (this->enemies[i]->getBounds().top > this->window->getSize().y)
			{
				this->enemies.erase(this->enemies.begin() + i);
				std::cout << this->enemies.size() << "\n";
				enemy_removed = true;
			}
		}

		//Remove enemies that touch the player and reduce the player's HP 

		if (!enemy_removed)
		{
			if (this->enemies[i]->getBounds().intersects(this->player->getBounds()))
			{
				this->enemies.erase(this->enemies.begin() + i);
				this->player->loseHP(10);
			}
		}



	}
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	

	if (this->player->getBounds().left+ this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x- this->player->getBounds().width, this->player->getBounds().top);


	}

	if (this->player->getBounds().top <= 0) 
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);


	}

	if (this->player->getBounds().top+this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left,this->window->getSize().y-this->player->getBounds().height);
	}

	


}

void Game::renderWORLD()
{
	this->window->draw(this->worldBACKGROND);
}


void Game::update()
{
	this->updateInput();
	this->updateGUI();
	this->player->update();
	this->updateCollision();
	this->updateBullets();
	this->updateEnemiesandCombat();
	this->updateWorld();

}

void Game::render()
{
	this->window->clear();

	//TO Render The Background 
	this->renderWORLD();


	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}


	this->renderGUI();
	if (this->player->getHP() <= 0) 
	{
		this->window->draw(this->GameOverText);
	}
	this->window->display();
}
