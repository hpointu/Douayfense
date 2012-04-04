#include "Application.hpp"
#include "Const.hpp"
#include "MapFileReader.hpp"
#include "Enemy.hpp"

#include <iostream>

Application::Application() :
	homePv(5)
{
	enemyImage.LoadFromFile("skel.png");
	towerImage.LoadFromFile("tower.png");

	MapFileReader reader("default.map");
	gameMap = reader.getMap();

	mouseMode = NORMAL;
}

Application::~Application()
{
}

void Application::run()
{
	window = new sf::RenderWindow(sf::VideoMode(W_WIDTH, W_HEIGHT, 32),
											"Douayfense");


	Enemy *e1 = new Enemy(gameMap.getDoors()[0], gameMap);
	enemies.push_back(e1);

	Tower *ghostTower = NULL;

	while(window->IsOpened())
	{
		sf::Event e;
		while(window->GetEvent(e)){
			if(e.Type == sf::Event::Closed)
				window->Close();

			else if(e.Type == sf::Event::MouseMoved && mouseMode == ADD_TOWER)
			{
				Map::Cell cell = gameMap.getCell(e.MouseMove.X, e.MouseMove.Y);
				ghostTower->i = cell.posI;
				ghostTower->j = cell.posJ;
			}

			else if(e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::A)
			{
				if(mouseMode != ADD_TOWER)
				{
					ghostTower = new Tower();
					mouseMode = ADD_TOWER;
				}
				else
				{
					delete ghostTower; ghostTower = NULL;
					mouseMode = NORMAL;
				}
			}

			else if(e.Type == sf::Event::MouseButtonPressed)
			{
				if(e.MouseButton.Button == sf::Mouse::Left && mouseMode == ADD_TOWER)
				{
					towers.push_back(new Tower(*ghostTower));
					towers.back()->placed = true;
					delete ghostTower; ghostTower = NULL;
					mouseMode = NORMAL;
				}
			}
		}

		window->Clear(sf::Color::Black);

		std::vector<Enemy*>::iterator eit;
		std::vector<Tower*>::iterator tit;
		// tick
		for(eit=enemies.begin(); eit!=enemies.end(); eit++)
			(*eit)->moveToNext();

		// draw
		gameMap.render(window);

		for(tit=towers.begin(); tit!=towers.end(); tit++)
			(*tit)->render(window);

		for(eit=enemies.begin(); eit!=enemies.end(); eit++)
			(*eit)->render(window);


		if(ghostTower)
			ghostTower->render(window);

		window->Display();

		// postprocess
		manageAtHome();

	}
}

void Application::manageAtHome()
{
	std::vector<Enemy*>::iterator eit;
	// tick
	for(eit=enemies.begin(); eit!=enemies.end(); eit++)
	{
		if(!(*eit)->isDead() && (*eit)->atHome())
		{
			homePv--;
//			enemies.erase(eit);
			(*eit)->pv = 0;
			std::cout << "Home: " << homePv << std::endl;
		}
	}
}
