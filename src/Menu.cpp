#include "Menu.hpp"

#include "Application.hpp"
#include "Level.hpp"
#include "levels/Level1.hpp"
#include "levels/Level2.hpp"
#include "levels/Level3.hpp"

#include "Const.hpp"
#include <string>

Menu::Menu() :
	visible(true)
{
	onCredits = false;

	bg.LoadFromFile("img/menubg.png");
	title.LoadFromFile("img/title.png");

	float bx = 310, by = 430;

	bLvl1 = Button(bx, by);
	bLvl1.setText("Initiation");
	bLvl1.setCallback(Menu::initLevel1);
	by += 25;

	bLvl2 = Button(bx, by);
	bLvl2.setText("La tourmente");
	bLvl2.setCallback(Menu::initLevel2);
	by += 25;

	bLvl3 = Button(bx, by);
	bLvl3.setText("Challenge++");
	bLvl3.setCallback(Menu::initLevel3);
	by += 25;

	bShowCredits = Button(580,715);
	bShowCredits.setCallback(Menu::actionShowCredits);
	bShowCredits.setText("Credits");


	bHideCredits = Button(580,715);
	bHideCredits.setCallback(Menu::actionHideCredits);
	bHideCredits.setText("Retour");
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

	if(!onCredits)
	{
		bLvl1.processEvents(event);
		bLvl2.processEvents(event);
		bLvl3.processEvents(event);
		bShowCredits.processEvents(event);
	}
	else
		bHideCredits.processEvents(event);

}

void Menu::render(sf::RenderTarget *target)
{
	target->Clear(sf::Color(0,0,0));
	sf::Sprite sp(bg);
	target->Draw(sp);

	sf::Sprite spt(title);
	spt.SetPosition(130, 80);
	target->Draw(spt);


	if(!onCredits)
	{
		sf::Shape sh = sf::Shape::Rectangle(290, 410,
														436, 520,
														sf::Color(110,90,60,150),
														1.f,
														sf::Color(30,35,60,200));
		target->Draw(sh);


		bLvl1.render(target);
		bLvl2.render(target);
		bLvl3.render(target);

		bShowCredits.render(target);
	}
	else
	{
		sf::Shape sh = sf::Shape::Rectangle(210, 350,
														520, 560,
														sf::Color(50,50,50,200),
														1.f,
														sf::Color(30,35,60,200));
		target->Draw(sh);

		sf::String creditText, creditTitles;

		creditTitles.SetPosition(225, 360);
//		creditTitles.SetStyle();
		creditTitles.SetSize(14);
		creditTitles.SetColor(sf::Color(220,220,200));

		creditText.SetPosition(370, 360);
		creditText.SetStyle(sf::String::Italic);
		creditText.SetSize(14);

		std::string str = ""
				"Developpement\n"
				"et conception:\n"
				"\n\n"
				"Musique:\n"
				"\n\n"
				"Graphismes:\n"
				"\n"
				"\n"
				"\n\n"
				"Effets sonores:\n"
				"\n";

		creditTitles.SetText(str);

		std::string str2 = ""
				"\n"
				"Freddy Teuma\n"
				"\n\n"
				"Celestial Aeon Project\n"
				"\n\n"
				"Julien Venerosy,\n"
				"Freddy Teuma\n"
				"Battle for Wesnoth\n"
				"\n\n"
				"Freddy Teuma\n"
				"\n";

		creditText.SetText(str2);

		target->Draw(creditTitles);
		target->Draw(creditText);
		bHideCredits.render(target);
	}

}

void Menu::showCredits()
{
	onCredits = true;
}

void Menu::hideCredits()
{
	onCredits = false;
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
	Level *lvl = new Level3();
	Application::getInstance()->initLevel(lvl);
	Menu::getInstance()->hide();
	delete lvl;
}

void Menu::actionShowCredits()
{
	Menu::getInstance()->showCredits();
}

void Menu::actionHideCredits()
{
	Menu::getInstance()->hideCredits();
}
