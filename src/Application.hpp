#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Enemy.hpp"
#include "Map.hpp"
#include "Singleton.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tower.hpp"

class Application : public Singleton<Application>
{
	friend class Singleton<Application>;
public:
	enum MouseMode
	{
		NORMAL,
		ADD_TOWER
	};

	void run();
	sf::Image enemyImage;
	sf::Image towerImage;

private:
	Application();
	~Application();

	void manageAtHome();

	sf::RenderWindow *window;
	std::vector<Enemy*> enemies;
	std::vector<Tower*> towers;
	Map gameMap;

	int homePv;

	MouseMode mouseMode;

};

#endif // APPLICATION_HPP
