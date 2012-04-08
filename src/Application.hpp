#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Enemy.hpp"
#include "Map.hpp"
#include "Singleton.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Tower.hpp"
#include "Hud.hpp"
#include "Wave.hpp"
#include "Level.hpp"
#include "Menu.hpp"
#include "PausableClock.hpp"
#include "IngameMenu.hpp"

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
	bool paySum(int sum);
	bool canPay(int sum);
	void addMoney(int sum);

	void initLevel(Level *level);
	void reset();
	void togglePause();
	void setPaused();


	// res
	sf::Image enemyImage;
	sf::Image towerImage, towerImageUp;
	sf::Image freezerImage, freezerImageUp;
	sf::Image poisonerImage, poisonerImageUp;
	sf::Image grassImage;
	sf::Image buttonImage;

	sf::SoundBuffer dingBuff, dyingBuff, fireBuff;
	sf::SoundBuffer buildBuff, moneyBuff;


	int bank;
	unsigned int currentWave;
	int homePv;
	bool paused;
	PausableClock gameClock;
	sf::RenderWindow *window;

private:
	Application();
	~Application();


	void processEvents(const sf::Event &e);
	void manageAtHome();

	void selectTowers(bool val = false);

	bool towerOnCell(const Map::Cell &c);

//	void sellTower(const Map::Cell &c);

	int nbAlive();

	Tower *createGhostFromKey(sf::Key::Code keyCode);

	Hud *hud;
	sf::View gameView;
	sf::View hudView;
	std::vector<Enemy*> enemies;
	std::vector<Tower*> towers;
	std::vector<Wave> waves;
	Map gameMap;

	MouseMode mouseMode;

	Tower *lastSelectedTower;
	Tower *ghostTower;

	sf::Clock mainClock;

	Menu *menu;
	IngameMenu *ingameMenu;

	bool over;


};

#endif // APPLICATION_HPP
