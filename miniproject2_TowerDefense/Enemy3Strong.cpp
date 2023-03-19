#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "BulletEnemy3.hpp"
#include "Group.hpp"
#include "Enemy3Strong.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Enemy.hpp"

Enemy3Strong::Enemy3Strong(int x, int y) : Enemy("play/enemy-3.png", x, y, 20, 20, 100, 50, 3) {
}
void Enemy3Strong::CreateBulletEnemy() {
	Engine::Point diff = Engine::Point(1, 0);
	float rotation = ALLEGRO_PI / 2;
	getScenePlay()->BulletGroup->AddNewObject(new BulletEnemy3(Position, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}