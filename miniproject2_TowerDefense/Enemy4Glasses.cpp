#include <allegro5/base.h>
#include <cmath>
#include <string>
#include <iostream>

#include "AudioHelper.hpp"
#include "BulletEnemy4.hpp"
#include "Group.hpp"
#include "Enemy4Glasses.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Enemy.hpp"

Enemy4Glasses::Enemy4Glasses(int x, int y) : Enemy("play/enemy-4.png", x, y, 10, 50, 5, 5, 3) {
}
void Enemy4Glasses::EnemyEffect(Enemy* enemy) {
	printf("in EnemyEffect\n");
	if (!enemy->hit) {
		enemy->Velocity = Engine::Point(enemy->Velocity.x * 2.5, 0);
		enemy->hit = true;
	}
}
void Enemy4Glasses::CreateBulletEnemy() {
	Engine::Point diff = Engine::Point(1, 0);
	float rotation = ALLEGRO_PI / 2;
	getScenePlay()->BulletGroup->AddNewObject(new BulletEnemy4(Position, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}