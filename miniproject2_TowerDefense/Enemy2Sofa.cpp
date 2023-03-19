#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "BulletEnemy2.hpp"
#include "Group.hpp"
#include "Enemy2Sofa.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Enemy.hpp"

Enemy2Sofa::Enemy2Sofa(int x, int y) : Enemy("play/enemy-2.png", x, y, 16, 100, 10, 10, 2) {
}
void Enemy2Sofa::CreateBulletEnemy() {
	Engine::Point diff = Engine::Point(1, 0);
	float rotation = ALLEGRO_PI / 2;
	getScenePlay()->BulletGroup->AddNewObject(new BulletEnemy2(Position, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}