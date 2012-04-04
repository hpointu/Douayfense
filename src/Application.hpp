#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Enemy.hpp"
#include "Map.hpp"
#include "Singleton.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Application : public Singleton<Application>
{
	friend class Singleton<Application>;
public:
	void run();
	sf::Image enemyImage;

private:
	Application();
	~Application();

	void manageAtHome();

	sf::RenderWindow *window;
	std::vector<Enemy*> enemies;
	Map gameMap;

	int homePv;

};

#endif // APPLICATION_HPP
