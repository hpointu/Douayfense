#include "Application.hpp"
#include "Const.hpp"
#include "MapFileReader.hpp"
#include "Enemy.hpp"

#include <iostream>

Application::Application() :
	homePv(5)
{
	enemyImage.LoadFromFile("skel.png");

	MapFileReader reader("default.map");
	gameMap = reader.getMap();
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

	while(window->IsOpened())
	{
		sf::Event e;
		while(window->GetEvent(e)){
			if(e.Type == sf::Event::Closed)
				window->Close();
		}

		window->Clear(sf::Color::Black);

		std::vector<Enemy*>::iterator eit;
		// tick
		for(eit=enemies.begin(); eit!=enemies.end(); eit++)
			(*eit)->moveToNext();

		// draw
		gameMap.render(window);
		for(eit=enemies.begin(); eit!=enemies.end(); eit++)
			(*eit)->render(window);
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
