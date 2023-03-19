#include <allegro5/base.h>
#include <random>
#include <string>
#include "EffectDirty.hpp"
#include "Enemy.hpp"
#include "BulletEnemy1.hpp"
#include "Group.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"

class Turret;

BulletEnemy1::BulletEnemy1(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent) :
	BulletEnemy("play/bullet-12.png", 250, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}
void BulletEnemy1::OnExplode(Turret* turret) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	// need check
	/*
	getScenePlay()->GroundEffectGroup->AddNewObject(new EffectDirty("play/dirty-1.png", dist(rng), turret->Position.x, turret->Position.y));
	*/
}

