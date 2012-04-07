#include "Menu.hpp"

#include "Application.hpp"
#include "Level.hpp"
#include "levels/Level1.hpp"
#include "levels/Level2.hpp"

#include "Const.hpp"

Menu::Menu() :
	visible(true)
{
	float bw = 130, bh = 28;
	float bx = 580, by = 620;

	bLvl1 = Button(bx, by, bx+bw, by+bh);
	bLvl1.setText("Niveau 1");
	bLvl1.setCallback(Menu::initLevel1);
	by += 40;

	bLvl2 = Button(bx, by, bx+bw, by+bh);
	bLvl2.setText("Niveau 2");
	bLvl2.setCallback(Menu::initLevel2);
	by += 40;

	bLvl3 = Button(bx, by, bx+bw, by+bh);
	bLvl3.setText("Niveau 3");
	bLvl3.setCallback(Menu::initLevel3);
	by += 40;
}

void Menu::processEvents(const sf::Event &event)
{
	if(event.Type == sf::Event::Closed)
		Application::getInstance()->window->Close();

//	else if(event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left )
//	{
//	}
//	else if(event.Type == sf::Event::MouseMoved)
//	{
//	}

	bLvl1.processEvents(event);
	bLvl2.processEvents(event);
	bLvl3.processEvents(event);
}

void Menu::render(sf::RenderTarget *target)
{
	target->Clear(sf::Color(0,0,0));

	bLvl1.render(target);
	bLvl2.render(target);
	bLvl3.render(target);
}


void Menu::initLevel1()
{
	Level *lvl = new Level1();
	Application::getInstance()->initLevel(lvl);
	Menu::getInstance()->hide();
	delete lvl;
}

void Menu::initLevel2()
{
	Level *lvl = new Level2();
	Application::getInstance()->initLevel(lvl);
	Menu::getInstance()->hide();
	delete lvl;
}

void Menu::initLevel3()
{

}
