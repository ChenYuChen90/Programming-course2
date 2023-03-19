#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Bullet1IceCream.hpp"
#include "Group.hpp"
#include "Turret1WBCell.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int Turret1WBCell::Price = 30;
Turret1WBCell::Turret1WBCell(float x, float y) :
    // TODO 2 (2/8): You can imitate the 2 files: 'Turret3Freeze.hpp', 'Turret3Freeze.cpp' to create a new turret.
	Turret("play/turret-1.png", x, y, Price, 0.5, 10) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void Turret1WBCell::CreateBullet() {
	Engine::Point diff = Engine::Point(1,0);
	float rotation = ALLEGRO_PI / 2;
	getScenePlay()->BulletGroup->AddNewObject(new Bullet1IceCream(Position , diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
