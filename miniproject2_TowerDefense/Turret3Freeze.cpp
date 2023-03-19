#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Bullet3Fire.hpp"
#include "Group.hpp"
#include "Turret3Freeze.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int Turret3Freeze::Price = 30;
Turret3Freeze::Turret3Freeze(float x, float y) :
	Turret("play/turret-3.png", x, y, Price, 0.5, 30) {
	Anchor.y += 8.0f / GetBitmapHeight();
}
void Turret3Freeze::CreateBullet() {
	Engine::Point diff = Engine::Point(1, 0);
	float rotation = ALLEGRO_PI / 2;
	getScenePlay()->BulletGroup->AddNewObject(new Bullet3Fire(Position, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}