#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Singleton.hpp"

class Menu : public Singleton<Menu>
{
	friend class Singleton<Menu>;

public:

	void show(){ visible = true; }
	void hide(){ visible = false; }
	bool isVisible(){ return visible; }

	void render(sf::RenderTarget *target);
	void processEvents(const sf::Event &event);

	void showCredits();
	void hideCredits();

private:
	Menu();
	bool visible;
	bool onCredits;
	Button bLvl1, bLvl2, bLvl3;
	Button bShowCredits, bHideCredits;

	sf::Image bg, title;

	static void initLevel1();
	static void initLevel2();
	static void initLevel3();

	static void actionShowCredits();
	static void actionHideCredits();
};

#endif // MENU_HPP
