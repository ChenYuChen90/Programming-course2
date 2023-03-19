#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>
#include <random>

#include "AudioHelper.hpp"
#include "BulletEnemy.hpp"
#include "Collider.hpp"
#include "Enemy.hpp"
#include "EffectExplosion.hpp"
#include "EffectDirty.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Turret.hpp"

ScenePlay* Turret::getScenePlay() {
	return dynamic_cast<ScenePlay*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Turret::Turret(std::string imgTurret, float x, float y,/* float radius,*/ int price, float coolDown, float hp) :
	Sprite(imgTurret, x, y), price(price), coolDown(coolDown), hp(hp) {
	//CollisionRadius = radius;
}
void Turret::Update(float deltaTime) {
	
	Sprite::Update(deltaTime);
	ScenePlay* scene = getScenePlay();
	if (!Enabled)
		return;
	if (Target) {
		if (Target->Position.x < Position.x&& Target->Position.y >= Position.y  && Target->Position.y < Position.y+scene->BlockSize) {
			Target->lockedTurrets.erase(lockedTurretIterator);
			Target = nullptr;
			lockedTurretIterator = std::list<Turret*>::iterator();
		}
		// Shoot reload.
		reload -= deltaTime;
		if (reload <= 0) {
			// shoot.
			reload = coolDown;
			if (level_up && (price == 30 || price == 50) && !level) {
				level = true;
				coolDown /= 2;
			}
			CreateBullet();
		}
	}
	if (!Target) {
		// Lock first seen target.
		// Can be improved by Spatial Hash, Quad Tree, ...
		// However simply loop through all enemies is enough for this program.
		for (auto& it : scene->EnemyGroup->GetObjects()) {
            if (it->Position.x > Position.x && it->Position.y >= Position.y  && it->Position.y < Position.y+scene->BlockSize) {
				Target = dynamic_cast<Enemy*>(it);
				Target->lockedTurrets.push_back(this);
				lockedTurretIterator = std::prev(Target->lockedTurrets.end());
				break;
			}
		}
	}

}
void Turret::Draw() const {
	if (price == 35) {
		if (level_up) {
			al_draw_circle(Position.x, Position.y, 350, al_map_rgb(0, 0, 255), 2);
		}
		else {
			al_draw_circle(Position.x, Position.y, 250, al_map_rgb(0, 0, 255), 2);
		}
	}
	/*if (Preview) {
		al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(0, 255, 0, 50));
	}*/
	Sprite::Draw();
	/*if (ScenePlay::DebugMode) {
		// Draw target radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(0, 0, 255), 2);
	}*/
}
int Turret::GetPrice() const {
	return price;
}
/*-----------------¼Ä¤H®g¤l¼u-----------------*/

void Turret::Hit(float damage) {
	hp -= damage;
	if (hp <= 0) {
		OnExplode();
		if (price == 35) {
			ScenePlay* scene = getScenePlay();
			for (auto& it : scene->EnemyGroup->GetObjects()) {
				Enemy* enemy = dynamic_cast<Enemy*>(it);
				if (!enemy->Visible)
					continue;
				if (level_up) {
					if (Engine::Collider::IsCircleOverlap(Position, 350, enemy->Position, enemy->CollisionRadius)) {
						enemy->OnExplode();
						enemy->Hit(enemy->hp);
					}
				}
				else {
					if (Engine::Collider::IsCircleOverlap(Position, 250, enemy->Position, enemy->CollisionRadius)) {

						enemy->OnExplode();
						enemy->Hit(enemy->hp);
					}
				}
			}
		}
		else if (price == 20 && level_up) {
			ScenePlay* scene = getScenePlay();
			for (auto& it : scene->EnemyGroup->GetObjects()) {
				Enemy* enemy = dynamic_cast<Enemy*>(it);
				if (!enemy->Visible)
					continue;
				if (level_up) {
					if (abs(enemy->Position.y - Position.y) < Engine::GameEngine::GetInstance().GetScreenSize().y / 14) {
						enemy->OnExplode();
						enemy->Hit(enemy->hp);
					}
				}
			}
		}
		int y = Position.y / 128;
		int x = Position.x / 128;
		getScenePlay()->change_mapstate(y, x);
		// Remove all turret's reference to target.
		for (auto& it : lockedEnemies)
			it->Target = nullptr;
		for (auto& it : lockedBulletEnemies)
			it->Target = nullptr;
		getScenePlay()->TowerGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}

/*
void Turret::Hit(float damage) {
	hp -= damage;
	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it : lockedEnemies)
			it->Target = nullptr;
		for (auto& it : lockedBulletEnemies)
			it->Target = nullptr;
		getScenePlay()->TowerGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}
*/
void Turret::OnExplode() {
	getScenePlay()->EffectGroup->AddNewObject(new EffectExplosion(Position.x, Position.y));
	// need check
	
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getScenePlay()->GroundEffectGroup->AddNewObject(new EffectDirty("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
	
}