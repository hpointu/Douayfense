#include "Application.hpp"
#include "Const.hpp"
#include "MapFileReader.hpp"
#include <iostream>

Application::Application() :
	homePv(5)
{
	enemyImage.LoadFromFile("skel.png");
	towerImage.LoadFromFile("tower.png");
	towerImageUp.LoadFromFile("tower_up.png");

	MapFileReader reader("default.map");
	gameMap = reader.getMap();

	mouseMode = NORMAL;

	gameView = sf::View(sf::Vector2f( gameMap.width*CELL_SIZE/2.f, 56+(gameMap.height*CELL_SIZE/2.f) ),
							  sf::Vector2f( W_WIDTH/2.f, W_HEIGHT/2.f ));

	bank = 700;
}

Application::~Application()
{
}

void Application::run()
{
	paused = false;
	sf::WindowSettings settings;
	settings.AntialiasingLevel = 0;
	window = new sf::RenderWindow(sf::VideoMode(W_WIDTH, W_HEIGHT, 8),
											"Douayfense", sf::Style::Close, settings);

	hud = new Hud();


	Tower *ghostTower = NULL;

	sf::String finalText;
	finalText.SetSize(40);
	finalText.SetPosition(260,300);
	finalText.SetColor(sf::Color::Red);

	sf::Clock mainClock;

	createWaves();
	currentWave = 0;
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
				ghostTower->wrong = towerOnCell(cell) || (cell.type != Map::GROUND);
			}

			else if(e.Type == sf::Event::KeyPressed
					  && (e.Key.Code == sf::Key::A
							|| e.Key.Code == sf::Key::Z
							|| e.Key.Code == sf::Key::E))
			{
				if(mouseMode != TOWER_ADD)
				{
					ghostTower = createGhostFromKey(e.Key.Code);
					mouseMode = TOWER_ADD;
					selectTowers(true);
					hud->setTower(ghostTower, true);
				}
			}
			else if(e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Escape)
			{
				if(mouseMode == TOWER_ADD)
				{
					delete ghostTower; ghostTower = NULL;
					mouseMode = NORMAL;
				}
				selectTowers(false);
				hud->setTower(NULL);
				lastSelectedTower = NULL;
			}

			else if(e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Space)
			{
				paused = !paused;
			}

			else if(e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::U)
			{
				if(mouseMode == NORMAL && lastSelectedTower)
				{
					if(!lastSelectedTower->upgraded && paySum(lastSelectedTower->getUpgradePrice()))
					{
						lastSelectedTower->upgrade();
						hud->setTower(lastSelectedTower);
					}
				}
			}

			else if(e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::S)
			{
				if(mouseMode == NORMAL && lastSelectedTower)
				{
					addMoney(lastSelectedTower->getValue());
					lastSelectedTower->active = false;
					selectTowers(false);
					hud->setTower(NULL);
					lastSelectedTower = NULL;
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
						if(!ghostTower->wrong)
						{
							if(paySum(ghostTower->getPrice()))
							{
								towers.push_back(ghostTower->createCopy());
								delete ghostTower; ghostTower = NULL;
								mouseMode = NORMAL;
								selectTowers(false);
								towers.back()->selected = true;
								lastSelectedTower = towers.back();
								hud->setTower(lastSelectedTower);
							}
						}
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
								lastSelectedTower = t;
								hud->setTower(t);
								break;
							}
						}
					}
				}
				else
				{
				}
			}
		}

		if(mainClock.GetElapsedTime() > 1.f/60.f)
		{
			mainClock.Reset();

			window->Clear(sf::Color(10,10,10));
			// ------ tick
			if(homePv < 1)
			{
				paused = true;
			}

			if(!paused)
			{
				if(currentWave < waves.size())
				{
					Enemy *e = NULL;
					if(waves[currentWave].hasStock())
					{
						e = waves[currentWave].getNextEnemy();
						if(e)
						{
							enemies.push_back(e);
						}
					}
					else
					{
						// next wave
						if(nbAlive() < 1)
						{
							addMoney(waves[currentWave].value);
							currentWave++;
						}
					}
				}

				for(eit=enemies.begin(); eit!=enemies.end(); eit++)
					(*eit)->moveToNext();
				for(tit=towers.begin(); tit!=towers.end(); tit++)
					(*tit)->shoot(enemies);
			}
			// ------- draw
			// GAME Drawing
			window->SetView(gameView);
			gameMap.render(window);

			for(eit=enemies.begin(); eit!=enemies.end(); eit++)
				(*eit)->render(window);

			for(tit=towers.begin(); tit!=towers.end(); tit++)
				(*tit)->render(window);

			if(ghostTower)
				ghostTower->render(window, true);

			// HUD Drawing
			window->SetView(window->GetDefaultView());
			hud->render(window);

			// ended ?
			if(homePv < 1)
			{
				finalText.SetText("GAME OVER!");
				window->Draw(finalText);
			}
			else if(currentWave >= waves.size())
			{
				finalText.SetText("Congratulations !");
				window->Draw(finalText);
			}

			// postprocess
			manageAtHome();


			window->Display();
		}


	}
}

void Application::createWaves()
{
	std::vector<Enemy> tmpStock;
	int i;

	// first wave
	for(i=0; i<10; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// second wave
	for(i=0; i<10; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1/2.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// third wave
	for(i=0; i<14; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/2.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// fourth wave
	for(i=0; i<16; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/4.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// fifth wave
	for(i=0; i<18; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/5.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

}

Tower* Application::createGhostFromKey(sf::Key::Code keyCode)
{
	switch(keyCode)
	{
	case sf::Key::A:
		return new Tower();
		break;
	case sf::Key::Z:
		return new Tower();
		break;
	case sf::Key::E:
		return new Tower();
		break;
	default:
		return NULL;
		break;
	}
}

int Application::nbAlive()
{
	int cpt = 0;

	std::vector<Enemy*>::iterator eit;
	for(eit=enemies.begin(); eit!=enemies.end(); eit++)
	{
		if(!(*eit)->isDead())
			cpt++;
	}

	return cpt;
}

bool Application::paySum(int sum)
{
	if(canPay(sum))
	{
		bank -= sum;
		return true;
	}
	return false;
}

bool Application::canPay(int sum)
{
	return bank >= sum;
}

bool Application::towerOnCell(const Map::Cell &c)
{
	std::vector<Tower*>::iterator tit;
	for(tit=towers.begin(); tit!=towers.end(); tit++)
	{
		if((*tit)->i == c.posI && (*tit)->j == c.posJ)
		{
			return true;
		}
	}
	return false;
}

void Application::selectTowers(bool val)
{
	std::vector<Tower*>::iterator tit;
	for(tit=towers.begin(); tit!=towers.end(); tit++)
		(*tit)->selected = val;

}

void Application::addMoney(int sum)
{
	bank += sum;
}

void Application::manageAtHome()
{
	std::vector<Enemy*>::iterator eit;
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
