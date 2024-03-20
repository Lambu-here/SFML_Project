#pragma once

#include <iostream>
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

	// Game Objects
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

	// Game Logics
	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	// Private functions
	void initVariables();
	void initWindow();
	void initEnemeies();

public:
	// Constructors & Destructors
	Game();
	~Game();

	//	Accessors
	const bool running() const;

	// Functions
	void pollEvents();
	void spawnEnemy();

	void updateMousePosition();
	void updateEnemies();
	void update();
	
	void renderEnemies();
	void render();
};