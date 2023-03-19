#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "BulletEnemy1.hpp"
#include "Group.hpp"
#include "Enemy1Normal.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Enemy.hpp"

Enemy1Normal::Enemy1Normal(int x, int y) : Enemy("play/enemy-1.png", x, y, 10, 50, 5, 5, 2) {
    // TODO 2 (6/8): You can imitate the 2 files: 'Enemy1Normal.hpp', 'Enemy1Normal.cpp' to create a new enemy.
}
void Enemy1Normal::CreateBulletEnemy() {
	Engine::Point diff = Engine::Point(1, 0);
	float rotation = ALLEGRO_PI / 2;
	getScenePlay()->BulletGroup->AddNewObject(new BulletEnemy1(Position, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}