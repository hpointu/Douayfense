#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>

#include "Tower.hpp"

class Hud
{
public:
	Hud();
	void render(sf::RenderTarget *target);

	void setTower(Tower *t, bool ghost = false);

private:
	sf::Sprite sprite;
	sf::Sprite portrait;
	sf::Image image;

	sf::Sprite moneySprite;
	sf::Image moneyImage;

	sf::String line1, line2, line3, line4, line5, line6, line7;
	sf::String money, wave, life;

	bool infoTower;
};

#endif // HUD_HPP
