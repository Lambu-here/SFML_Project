#include "Game.h"

// private Functions
void Game::initVariables() {
	this->window = nullptr;

	// Game Logic
	this->points = 0;
	this->enemySpawnTimerMax = 50.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
}

void Game::initWindow() {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	//this->videoMode.getDesktopMode(); // For fullscreen games (Desktop rez)
	this->window = new sf::RenderWindow(this->videoMode, "Hello World!");
	this->window->setFramerateLimit(60);
}

void Game::initEnemeies() {
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);


}


// Constructors & Destructors
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initEnemeies();
}

Game::~Game() {
	// Deletes dynamically allocated window after the program is over to avoid memory leaks
	delete this->window;
}


// Accessors
const bool Game::running() const {
	// Returns true if window is open
	return this->window->isOpen();
}


// Functions
void Game::spawnEnemy() {
	/*
		Spawns enemies and sets their colors and positions
		- sets a random position
		- adds enemy to the vector (enemies)
	*/

	this->enemy.setPosition(
		static_cast<float>(
			rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)
		),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);
	
	//Spawn the enemy
	this->enemies.push_back(this->enemy);

	// Remove the enemy at the bottom of the screen
}

void Game::pollEvents() {
	/*
		Reads and takes action on User inputs
	*/
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {

			// Clicking the cross
		case sf::Event::Closed:
			this->window->close();
			break;

			// Pressing the Escape key
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePosition() {
	/*
		Updates the mouse positions
			- mouse positions relative to the window
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies() {
	/*
		Updates the enemy spawn timer and spawns the enemies when the
		total number of enemies is less than max

		Moves the enemies downwards
		Removes the enemies at the edge of the screen
	*/

	// Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			// Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	// Move the enemy
	for (int i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].move(0.f, 1.f);

		// Check if clicked upon
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
				this->enemies.erase(this->enemies.begin() + i);
			}
		}
	}
}

void Game::renderEnemies() {
	for (int i = 0; i < this->enemies.size(); i++) {
		this->window->draw(this->enemies[i]);
	}
}

void Game::update() {
	/*
		Changes per frame and actions	 take place here
	*/
	this->pollEvents();

	this->updateMousePosition();

	this->updateEnemies();


}

void Game::render() {
	/*
		- Clear old frame
		- Render objects
		- Display final frame in window

		Renders the game objects
	*/
	this->window->clear(sf::Color::Black);

	// Draw game objects
	this->renderEnemies();

	// Draw UI

	this->window->display();
}
