#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "AudioHelper.hpp"
#include "Bullet.hpp"
#include "EffectDirty.hpp"
#include "Enemy.hpp"
#include "EffectExplosion.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "LOG.hpp"
#include "ScenePlay.hpp"
#include "Turret.hpp"

ScenePlay* Enemy::getScenePlay() {
	return dynamic_cast<ScenePlay*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Enemy::OnExplode() {
	getScenePlay()->EffectGroup->AddNewObject(new EffectExplosion(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getScenePlay()->GroundEffectGroup->AddNewObject(new EffectDirty("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
}
void Enemy::EnemyEffect(Enemy* enemy) {
}
Enemy::Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money, float coolDown) :
	Engine::Sprite(img, x, y), speed(speed), hp(hp), money(money), coolDown(coolDown) {
	CollisionRadius = radius;
	reachEndTime = 0;
	Velocity = Engine::Point(speed , 0);
	target = Engine::Point(ScenePlay::EndGridPointx , static_cast<int>(floor(Position.y / ScenePlay::BlockSize))) * ScenePlay::BlockSize + Engine::Point(ScenePlay::BlockSize / 2, ScenePlay::BlockSize / 2);
}
void Enemy::Hit(float damage) {
	hp -= damage;
	EnemyEffect(this);
	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it: lockedTurrets)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
		getScenePlay()->EarnMoney(money);
		getScenePlay()->EnemyGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}
void Enemy::Update(float deltaTime) {
	
	float remainSpeed = speed * deltaTime;
	
	Position.x -= Velocity.x * deltaTime;
	Position.y += Velocity.y * deltaTime;
	
	/*-----------------敵人停下-----------------*/
	int flag = 1;
	ScenePlay* scene = getScenePlay();
	for (auto& it : scene->TowerGroup->GetObjects()) {
			Turret *target= dynamic_cast<Turret*>(it);
			if (!target->Visible) continue;
			if ( abs(target->Position.y - Position.y) < Engine::GameEngine::GetInstance().GetScreenSize().y / 14) {
				if (target->Position.x <= Position.x && Position.x <= target->Position.x + 180) {
					Position.x = target->Position.x + 180;
					flag = 0;
				}
				// 設在裡面才能射同一條的子彈
				if (reload <= 0) {
					if (!flag ) {
						// shoot.
						reload = coolDown;
						CreateBulletEnemy();
					}
				}
				reload -= deltaTime;
			}
	}
	/*-----------------敵人射子彈-----------------*/
	/*
	reload -= deltaTime;
	if (reload <= 0) {
		// shoot.
		reload = coolDown;
		CreateBulletEnemy();
	}
	*/
	if(Position.x <= ScenePlay::EndGridPointx * ScenePlay::BlockSize + ScenePlay::BlockSize / 2){
		Hit(hp);
		getScenePlay()->Hit();
		reachEndTime = 0;
		return;
	}
	Engine::Point vec = target - Position;
	reachEndTime = (vec.Magnitude() - remainSpeed) / speed;
}
void Enemy::Draw() const {
	Sprite::Draw();
	if (ScenePlay::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}
