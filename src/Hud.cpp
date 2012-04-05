#include "Hud.hpp"
#include "Const.hpp"
#include "Application.hpp"

#include <sstream>

Hud::Hud()
{
	image.LoadFromFile("img/bg.png");
	moneyImage.LoadFromFile("img/money.png");

	sprite = sf::Sprite(image);
	moneySprite = sf::Sprite(moneyImage);

	float topY = W_HEIGHT-112;
	sprite.SetPosition(0, topY);
	moneySprite.SetPosition(508, topY+10);

	line1.SetSize(15);
	line2.SetSize(12);
	line3.SetSize(12);
	line4.SetSize(12);
	line5.SetSize(11);
	line6.SetSize(11);

	line1.SetPosition(60, topY+8);
	line2.SetPosition(60, topY+25);
	line3.SetPosition(60, topY+40);
	line4.SetPosition(60, topY+55);
	line5.SetPosition(60, topY+75);
	line6.SetPosition(60, topY+90);

	money.SetPosition(530, topY+10);
	wave.SetPosition(530, topY+30);
	life.SetPosition(530, topY+50);
	money.SetSize(14);
	wave.SetSize(14);
	life.SetSize(14);
	money.SetColor(sf::Color(200,150,0));
	wave.SetColor(sf::Color(200,200,200));
	life.SetColor(sf::Color(200,200,200));

	line1.SetColor(sf::Color::Yellow);

	line5.SetColor(sf::Color(0,200,200));
	line6.SetColor(sf::Color(0,200,0));

	portrait.SetPosition(15, topY+15);

	infoTower = false;
}

void Hud::render(sf::RenderTarget *target)
{
	target->Draw(sprite);

	if(infoTower)
	{
		target->Draw(portrait);
		target->Draw(line1);
		target->Draw(line2);
		target->Draw(line3);
		target->Draw(line4);
		target->Draw(line5);
		target->Draw(line6);
	}

	std::stringstream moneyText, waveText, lifeText;
	moneyText << "Argent: " << Application::getInstance()->bank << "$";
	waveText << "Vague: " << Application::getInstance()->currentWave+1 << std::endl;
	lifeText << "Vie restantes: " << Application::getInstance()->homePv;
	money.SetText(moneyText.str());
	wave.SetText(waveText.str());
	life.SetText(lifeText.str());

	target->Draw(moneySprite);
	target->Draw(money);
	target->Draw(wave);
	target->Draw(life);


	// test menu
	float topY = W_HEIGHT-112;
	sf::Sprite t1(Application::getInstance()->towerImage);
	sf::Sprite t2(Application::getInstance()->freezerImage);

	sf::String tt1("A");
	sf::String tt2("Z");
	tt1.SetSize(12);
	tt2.SetSize(12);

	sf::Shape mbg = sf::Shape::Rectangle(1, topY-40,
													 70, topY,
													 sf::Color(0,0,0,150),
													 2.f, sf::Color(180,180,180,150));

	target->Draw(mbg);

	t1.SetPosition(5, topY-35);
	t2.SetPosition(40, topY-35);

	tt1.SetPosition(5, topY-15);
	tt2.SetPosition(40, topY-15);

	target->Draw(t1);
	target->Draw(t2);

	target->Draw(tt1);
	target->Draw(tt2);

}


void Hud::setTower(Tower *t, bool ghost)
{
	infoTower = t == NULL ? false : true;

	if(!infoTower) return;

	std::stringstream damage, range, speed, value, upgrade, name;

	name << t->getName();
	if(ghost)
		name << " (prix: " << t->getPrice() << "$)";
	damage << "Degats : " << t->damage;
	range << "Portee : " << t->range;
	speed << "Vitesse : " << t->speed << " (" << (t->speed/2.f) << " tir/sec)";
	upgrade << "[U] Ameliorer pour " << t->getUpgradePrice() << "$ (";
	upgrade << t->upgradeDescription() << ")";
	value << "[S] Vendre pour " << t->getValue() << "$";

	if(t->upgraded)
	{
		upgrade.str("");
	}

	line1.SetText(name.str());
	line2.SetText(damage.str());
	line3.SetText(range.str());
	line4.SetText(speed.str());
	line5.SetText(upgrade.str());
	line6.SetText(value.str());

	portrait.SetImage(*t->getImage());

}
