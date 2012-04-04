#include "Application.hpp"
#include "Const.hpp"
#include "Map.hpp"
#include "MapFileReader.hpp"
#include "Enemy.hpp"

Application::Application()
{
	enemyImage.LoadFromFile("skel.png");
}

Application::~Application()
{
}

void Application::run()
{
	window = new sf::RenderWindow(sf::VideoMode(W_WIDTH, W_HEIGHT, 32),
											"Douayfense");


	MapFileReader reader("default.map");
	Map _map = reader.getMap();

	Enemy e1(_map.getDoors()[0], _map);


	while(window->IsOpened())
	{
		sf::Event e;
		while(window->GetEvent(e)){
			if(e.Type == sf::Event::Closed)
				window->Close();
		}

		window->Clear(sf::Color::Black);

		// tick
		e1.moveToNext();

		/////

		_map.render(window);
		e1.render(window);

		window->Display();
	}
}
