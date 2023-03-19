#include <allegro5/base.h>
#include <random>
#include <string>

#include "EffectDirty.hpp"
#include "Enemy.hpp"
#include "Bullet3Fire.hpp"
#include "Group.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"

class Turret;

Bullet3Fire::Bullet3Fire(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/bullet-7.png", 500, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}
void Bullet3Fire::OnExplode(Enemy* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getScenePlay()->GroundEffectGroup->AddNewObject(new EffectDirty("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
	// 子彈特效(緩速)
	if (!enemy->frozen) {
		enemy->Velocity = Engine::Point(enemy->Velocity.x / 2, 0);
		enemy->frozen = true;
	}
}
