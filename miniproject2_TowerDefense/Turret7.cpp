#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Collider.hpp"
#include "Group.hpp"
#include "Turret7.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int Turret7::Price = 10;
Turret7::Turret7(float x, float y) :
	Turret("play/turret-6.png", x, y, Price, 0.5, 1) {
	Anchor.y += 8.0f / GetBitmapHeight();
}
void Turret7::CreateBullet() {
}

