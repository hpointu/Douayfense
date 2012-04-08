#ifndef INGAMEMENU_HPP
#define INGAMEMENU_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Singleton.hpp"

class IngameMenu : public Singleton<IngameMenu>
{
	friend class Singleton<IngameMenu>;

public:
	void show(){ visible = true; }
	void hide(){ visible = false; }
	bool isVisible(){ return visible; }

	void render(sf::RenderTarget *target);
	void processEvents(const sf::Event &event);

private:
	IngameMenu();

	bool visible;
	Button bCancel, bQuit;

	static void cancelAction();
	static void quitAction();
};

#endif // INGAMEMENU_HPP
