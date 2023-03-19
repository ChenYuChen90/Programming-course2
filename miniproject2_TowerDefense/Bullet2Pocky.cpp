#include <allegro5/base.h>
#include <random>
#include <string>

#include "EffectDirty.hpp"
#include "Enemy.hpp"
#include "Bullet2Pocky.hpp"
#include "Group.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"

class Turret;

Bullet2Pocky::Bullet2Pocky(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/bullet-2.png", 800, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}
void Bullet2Pocky::OnExplode(Enemy* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 10);
	getScenePlay()->GroundEffectGroup->AddNewObject(new EffectDirty("play/dirty-2.png", dist(rng), enemy->Position.x, enemy->Position.y));
}

