#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Enemy.hpp"
#include "Map.hpp"
#include "Singleton.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tower.hpp"
#include "Hud.hpp"

class Application : public Singleton<Application>
{
	friend class Singleton<Application>;
public:
	enum MouseMode
	{
		NORMAL,
		TOWER_ADD,
		TOWER_EDIT
	};

	void run();
	sf::Image enemyImage;
	sf::Image towerImage;

private:
	Application();
	~Application();

	void manageAtHome();

	void selectTowers(bool val = false);

	sf::RenderWindow *window;
	Hud *hud;
	sf::View gameView;
	sf::View hudView;
	std::vector<Enemy*> enemies;
	std::vector<Tower*> towers;
	Map gameMap;

	int homePv;

	MouseMode mouseMode;

	Tower *selectedTower;

};

#endif // APPLICATION_HPP
