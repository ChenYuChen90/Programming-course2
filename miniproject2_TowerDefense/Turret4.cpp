#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "Turret4.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int Turret4::Price = 20;
Turret4::Turret4(float x, float y) :
	Turret("play/turret-4.png", x, y, Price, 0.5, 5) {
	Anchor.y += 8.0f / GetBitmapHeight();
}
void Turret4::CreateBullet() {
}
