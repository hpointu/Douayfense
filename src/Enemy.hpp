#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Map.hpp"
#include <SFML/Graphics.hpp>
class Enemy
{
public:
	Enemy(Map::Cell pos, Map map);
	~Enemy();

	void render(sf::RenderTarget *target);

	float x, y;
	float pv;
	bool frozen;
	bool poisoned;

	float waveWait;

	void tick();
	bool isDead();
	bool atHome();

	void hurt(float damage);
	void win();

	inline float getSpeed(){ return speed; }

	virtual sf::Image* getImage();
	virtual void applyPoison();
	virtual float getRealSpeed();

	virtual void freezeMe();

	virtual Enemy* createClone();
	virtual int getValue();

	virtual float getInitialPv();
	virtual void playDyingSound();

	void init();

private:
	void moveToNext();
	sf::Sprite sprite;
	Map myMap;

protected:
	float speed;
};

#endif // ENEMY_HPP
