#include <allegro5/base.h>
#include <random>
#include <string>
#include "EffectDirty.hpp"
#include "Enemy.hpp"
#include "Bullet1IceCream.hpp"
#include "Group.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"

class Turret;

Bullet1IceCream::Bullet1IceCream(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/bullet-1.png", 500, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
	// TODO 2 (1/8): You can imitate the 2 files: 'Bullet3Fire.hpp', 'Bullet3Fire.cpp' to create a new bullet.
}
void Bullet1IceCream::OnExplode(Enemy* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getScenePlay()->GroundEffectGroup->AddNewObject(new EffectDirty("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
}

