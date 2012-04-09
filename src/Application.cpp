#include "Application.hpp"
#include "Const.hpp"
#include "MapFileReader.hpp"
#include <iostream>
#include "TowerFreezer.hpp"
#include "TowerPoisoner.hpp"
#include "levels/Level1.hpp"
#include "levels/Level2.hpp"
#include "SoundManager.hpp"

Application::Application() :
	homePv(5)
{
	enemyImage.LoadFromFile("img/skel.png");

	towerImage.LoadFromFile("img/tower.png");
	towerImageUp.LoadFromFile("img/tower_up.png");

	freezerImage.LoadFromFile("img/freezer.png");
	freezerImageUp.LoadFromFile("img/freezer_up.png");

	poisonerImage.LoadFromFile("img/poisoner.png");
	poisonerImageUp.LoadFromFile("img/poisoner_up.png");

	grassImage.LoadFromFile("img/grass.png");

	buttonImage.LoadFromFile("img/button.png");
	tipImage.LoadFromFile("img/dialog-information.png");
	crownImage.LoadFromFile("img/crown.png");
	skullImage.LoadFromFile("img/skull.png");

	dingBuff.LoadFromFile("snd/ding.ogg");
	dyingBuff.LoadFromFile("snd/dying.ogg");
	fireBuff.LoadFromFile("snd/fire.ogg");
	buildBuff.LoadFromFile("snd/build.ogg");
	moneyBuff.LoadFromFile("snd/money.ogg");

	mouseMode = NORMAL;
	ghostTower = NULL;

	menu = Menu::getInstance();
	ingameMenu = IngameMenu::getInstance();
}

Application::~Application()
{
}

void Application::reset()
{
	menu->show();
}

void Application::initLevel(Level *level)
{
	enemies.clear();
	towers.clear();
	waves.clear();
	mouseMode = NORMAL;
	lastSelectedTower = NULL;
	ghostTower = NULL;
	paused = false;
	over = false;
	currentWave = 0;
	mainClock.Reset();
	gameClock.Reset();

	// level information
	level->init();
	waves = level->getWaves();
	bank = level->getBank();
	gameMap = level->getMap();
	homePv = level->getHomePv();

	// init view
	gameView = sf::View(sf::Vector2f( gameMap.width*CELL_SIZE/2.f, 56+(gameMap.height*CELL_SIZE/2.f) ),
							  sf::Vector2f( W_WIDTH/2.f, W_HEIGHT/2.f ));

	// play music
	SoundManager::getInstance()->playMusic();
}

void Application::processEvents(const sf::Event &e)
{
	std::vector<Tower*>::iterator tit;

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
		if(mouseMode == TOWER_ADD)
		{
			delete ghostTower; ghostTower = NULL;
			mouseMode = NORMAL;
		}
		if(mouseMode != TOWER_ADD)
		{
			ghostTower = createGhostFromKey(e.Key.Code);
			ghostTower->wrong = true;
			mouseMode = TOWER_ADD;
			selectTowers(true);
			hud->setTower(ghostTower, true);
		}
	}
	else if(e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Escape)
	{
		if((mouseMode == NORMAL && lastSelectedTower == NULL) || over)
		{
			// display ingame-menu
			ingameMenu->show();

			setPaused();
		}
		else if(mouseMode == TOWER_ADD)
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
		togglePause();
	}

	else if(e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::U)
	{
		if(mouseMode == NORMAL && lastSelectedTower)
		{
			if(!lastSelectedTower->upgraded && paySum(lastSelectedTower->getUpgradePrice()))
			{
				lastSelectedTower->upgrade();
				hud->setTower(lastSelectedTower);
				SoundManager::getInstance()->playSound(buildBuff, 60, 1.6f);
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
			SoundManager::getInstance()->playSound(moneyBuff, 60, 1.0f);
		}
	}

	else if(e.Type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2f vcoords = window->ConvertCoords(e.MouseButton.X, e.MouseButton.Y, &gameView);
		Map::Cell cell = gameMap.getCell(vcoords.x, vcoords.y);
		if(e.MouseButton.Button == sf::Mouse::Left && mouseMode == TOWER_ADD)
		{
			if(cell.type != Map::ERR)
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
						SoundManager::getInstance()->playSound(buildBuff, 60, 1.1f);
					}
				}
			}
		}
		else if(e.MouseButton.Button == sf::Mouse::Left && mouseMode == NORMAL)
		{
			if(cell.type != Map::ERR)
			{
				selectTowers(false);
				hud->setTower(NULL);
				// is there any tower here ?
				for(tit=towers.begin(); tit!=towers.end(); tit++)
				{
					Tower *t = *tit;
					if(t->i == cell.posI && t->j == cell.posJ && t->active)
					{
						t->selected = true;
						lastSelectedTower = t;
						hud->setTower(t);
						break;
					}
				}
			}
		}
	}
}

void Application::run()
{
	sf::WindowSettings settings;
	settings.AntialiasingLevel = 5;
	window = new sf::RenderWindow(sf::VideoMode(W_WIDTH, W_HEIGHT, 8),
											"Douayfense", sf::Style::Close, settings);

	hud = new Hud();

	sf::String finalText;
	finalText.SetSize(40);
	finalText.SetPosition(260,300);
	finalText.SetColor(sf::Color::Red);

	sf::String waveText;
	sf::Clock waveMessageClock;

	while(window->IsOpened())
	{
		// common iterators
		std::vector<Enemy*>::iterator eit;
		std::vector<Tower*>::iterator tit;

		sf::Event e;
		while(window->GetEvent(e))
		{
			if(menu->isVisible())
				menu->processEvents(e);
			else if(ingameMenu->isVisible())
				ingameMenu->processEvents(e);
			else
				processEvents(e);
		}

		// playing music
		if(menu->isVisible())
			SoundManager::getInstance()->playMenuMusic();
		else if(!over)
			SoundManager::getInstance()->runningMusic();

		if(mainClock.GetElapsedTime() > 1.f/60.f)
		{
			mainClock.Reset();

			if(menu->isVisible())
			{
				//// SHOW MENU
				menu->render(window);
			}
			else
			{
				//// GAME
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
						if(waveMessageClock.GetElapsedTime() < 3)
						{
							waveText.SetText(waves[currentWave].message);
						}
						else
						{
							waveText.SetText("");
						}
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
								waveMessageClock.Reset();
							}
						}
					}

					for(eit=enemies.begin(); eit!=enemies.end(); eit++)
						(*eit)->tick();
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

					finalText.SetColor(sf::Color::White);
					finalText.SetSize(30);

					sf::FloatRect box = finalText.GetRect();
					sf::Shape boxBorder = sf::Shape::Rectangle(box.Left-8, box.Top-45, box.Right+8, box.Bottom+8,
																					sf::Color(0,0,0,150),
																					1.f, sf::Color(0,0,0));

					sf::Sprite skull(skullImage);
					skull.SetPosition((box.Right-box.Left)/2.f + box.Left - 20, box.Top-40 );

					window->Draw(boxBorder);
					window->Draw(skull);
					window->Draw(finalText);
					over = true;
				}
				else if(currentWave >= waves.size())
				{
					finalText.SetText("Congratulations !");

					finalText.SetColor(sf::Color::White);
					finalText.SetSize(30);

					sf::FloatRect box = finalText.GetRect();
					sf::Shape boxBorder = sf::Shape::Rectangle(box.Left-8, box.Top-45, box.Right+8, box.Bottom+8,
																					sf::Color(0,0,0,150),
																					1.f, sf::Color(0,0,0));

					sf::Sprite crown(crownImage);
					crown.SetPosition((box.Right-box.Left)/2.f + box.Left - 20, box.Top-40 );

					window->Draw(boxBorder);
					window->Draw(crown);
					window->Draw(finalText);
					over = true;
					SoundManager::getInstance()->playEndingMusic();
				}

				if(std::string(waveText.GetText()) != "")
				{

					waveText.SetColor(sf::Color::Yellow);
					waveText.SetSize(12);
					waveText.SetPosition(40,45);

					sf::FloatRect tRect = waveText.GetRect();
					sf::Shape waveTextBorder = sf::Shape::Rectangle(tRect.Left-25, tRect.Top-4, tRect.Right+3, tRect.Bottom+5,
																					sf::Color(0,0,0,150),
																					1.f, sf::Color(200,200,200));

					sf::Sprite starSprite(tipImage);
					starSprite.SetPosition(20,45);

					window->Draw(waveTextBorder);
					window->Draw(starSprite);


					window->Draw(waveText);
				}

				// postprocess
				manageAtHome();
			} //// END GAME

			if(ingameMenu->isVisible())
			{
				ingameMenu->render(window);
			}

			window->Display();
		}

	} // end loop
}

Tower* Application::createGhostFromKey(sf::Key::Code keyCode)
{
	switch(keyCode)
	{
		case sf::Key::A:
			return new Tower();
			break;
		case sf::Key::Z:
			return new TowerFreezer();
			break;
		case sf::Key::E:
			return new TowerPoisoner();
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
		if((*tit)->i == c.posI && (*tit)->j == c.posJ && (*tit)->active)
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

void Application::togglePause()
{
	paused = !paused;
	if(paused)
		gameClock.Pause();
	else
		gameClock.Play();
}

void Application::setPaused()
{
	if(!paused)
		togglePause();
}

void Application::manageAtHome()
{
	std::vector<Enemy*>::iterator eit;
	for(eit=enemies.begin(); eit!=enemies.end(); eit++)
	{
		if(!(*eit)->isDead() && (*eit)->atHome())
		{
			homePv--;
			(*eit)->win();
		}
	}
}
