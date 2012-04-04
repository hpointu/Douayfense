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

	gameView = sf::View(sf::Vector2f( gameMap.width*CELL_SIZE/2.f, 56+(gameMap.height*CELL_SIZE/2.f) ),
						 sf::Vector2f( W_WIDTH/2.f, W_HEIGHT/2.f ));
}

Application::~Application()
{
}

void Application::run()
{
	sf::WindowSettings settings;
	settings.AntialiasingLevel = 0;
	window = new sf::RenderWindow(sf::VideoMode(W_WIDTH, W_HEIGHT, 8),
											"Douayfense", sf::Style::Close, settings);

	hud = new Hud();


	Enemy *e1 = new Enemy(gameMap.getDoors()[0], gameMap);
	enemies.push_back(e1);

	Tower *ghostTower = NULL;

	sf::Clock mainClock;

	while(window->IsOpened())
	{
		// common iterators
		std::vector<Enemy*>::iterator eit;
		std::vector<Tower*>::iterator tit;

		sf::Event e;
		while(window->GetEvent(e)){
			if(e.Type == sf::Event::Closed)
				window->Close();

			else if(e.Type == sf::Event::MouseMoved && mouseMode == TOWER_ADD)
			{
				sf::Vector2f vcoords = window->ConvertCoords(e.MouseMove.X, e.MouseMove.Y, &gameView);
				Map::Cell cell = gameMap.getCell(vcoords.x, vcoords.y);
				ghostTower->i = cell.posI;
				ghostTower->j = cell.posJ;
			}

			else if(e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::A)
			{
				if(mouseMode != TOWER_ADD)
				{
					ghostTower = new Tower();
					mouseMode = TOWER_ADD;
					selectTowers(true);
				}
				else
				{
					delete ghostTower; ghostTower = NULL;
					mouseMode = NORMAL;
					selectTowers(false);
				}
			}

			else if(e.Type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f vcoords = window->ConvertCoords(e.MouseButton.X, e.MouseButton.Y, &gameView);
				Map::Cell cell = gameMap.getCell(vcoords.x, vcoords.y);
				if(e.MouseButton.Button == sf::Mouse::Left && mouseMode == TOWER_ADD)
				{
					if(cell.type != Map::ERROR)
					{
						towers.push_back(ghostTower->createCopy());
						towers.back()->placed = true;
						delete ghostTower; ghostTower = NULL;
						mouseMode = NORMAL;
						selectTowers(false);
					}
				}
				else if(e.MouseButton.Button == sf::Mouse::Left && mouseMode == NORMAL)
				{
					if(cell.type != Map::ERROR)
					{
						selectTowers(false);
						hud->setTower(NULL);
						// is there any tower here ?
						for(tit=towers.begin(); tit!=towers.end(); tit++)
						{
							Tower *t = *tit;
							if(t->i == cell.posI && t->j == cell.posJ)
							{
								t->selected = true;
								hud->setTower(t);
								break;
							}
						}
					}
				}
				else
				{
//					mouseMode = NORMAL;
				}
			}
		}


		if(mainClock.GetElapsedTime() > 1.f/60.f)
		{
			mainClock.Reset();

			window->Clear(sf::Color(10,10,10));
			// tick
			for(eit=enemies.begin(); eit!=enemies.end(); eit++)
				(*eit)->moveToNext();

			// GAME Drawing
			window->SetView(gameView);
			gameMap.render(window);

			for(eit=enemies.begin(); eit!=enemies.end(); eit++)
				(*eit)->render(window);

			for(tit=towers.begin(); tit!=towers.end(); tit++)
				(*tit)->render(window);

			if(ghostTower)
				ghostTower->render(window);

			// HUD Drawing
			window->SetView(window->GetDefaultView());
			hud->render(window);

			// postprocess
			manageAtHome();


			window->Display();
		}


	}
}

void Application::selectTowers(bool val)
{
	std::vector<Tower*>::iterator tit;
	for(tit=towers.begin(); tit!=towers.end(); tit++)
		(*tit)->selected = val;

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
