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
	bool isRooted();

	void hurt(float damage);
	void win();

	inline float getSpeed(){ return speed; }

	virtual sf::Image* getImage();
	virtual void applyPoison();
	virtual float getRealSpeed();

	virtual void freezeMe();
	virtual void rootMe(float val);

	virtual Enemy* createClone();
	virtual int getValue();

	virtual float getInitialPv();
	virtual void playDyingSound();

	void init();

private:
	void moveToNext();
	sf::Sprite sprite, rsp;
	Map myMap;

protected:
	float lastRooted;
	float rooted;
	float speed;
};

#endif // ENEMY_HPP
