#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Collider.hpp"
#include "Group.hpp"
#include "Turret5.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int Turret5::Price = 35;
Turret5::Turret5(float x, float y) :
	Turret("play/turret-5.png", x, y, Price, 0.5, 1) {
	Anchor.y += 8.0f / GetBitmapHeight();
}
void Turret5::CreateBullet() {
}

