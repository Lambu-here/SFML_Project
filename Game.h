#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

// SFML includes
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>

/*
	Game wrapper class (Basic functionality)
*/

class Game {
private:
	// Window Control
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;

	// Game Objects
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

	// Game Logics
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	// Private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemeies();

public:
	// Constructors & Destructors
	Game();
	~Game();

	//	Accessors
	const bool running() const;
	const bool getEndGame() const;

	// Functions
	void spawnEnemy();

	void pollEvents();
	void updateText();
	void updateMousePosition();
	void updateEnemies();
	void update();
	
	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};