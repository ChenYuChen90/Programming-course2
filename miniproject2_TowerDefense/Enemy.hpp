#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <vector>
#include <string>
#include <cstdbool>
#include "Point.hpp"
#include "Sprite.hpp"

class Bullet;
class ScenePlay;
class Turret;

class Enemy : public Engine::Sprite {
protected:
	Engine::Point target;
	float speed;
	float hp;
	int money;
	bool frozen = false;
	bool hit = false;
	ScenePlay* getScenePlay();
	virtual void OnExplode();
	virtual void EnemyEffect(Enemy* enemy);
	/*-----------------�ĤH�g�l�u-----------------*/
	float coolDown;
	float reload = 0;
	virtual void CreateBulletEnemy() = 0;
public:
	float reachEndTime;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money, float coolDown);
 	void Hit(float damage);
	void Update(float deltaTime) override;
	void Draw() const override;
	// �l�u�S��(�w�t)
	friend class Bullet3Fire;
	friend class Enemy4Glasses;
	/*-----------------�ĤH�g�l�u-----------------*/
	Turret* Target = nullptr;
	friend Turret;
};
#endif // ENEMY_HPP
