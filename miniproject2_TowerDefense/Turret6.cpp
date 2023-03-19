#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Collider.hpp"
#include "Group.hpp"
#include "Turret6.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int Turret6::Price = 0;
Turret6::Turret6(float x, float y) :
	Turret("play/bomb.png", x, y, Price, 0.5, 1) {
	Anchor.y += 8.0f / GetBitmapHeight();
}
void Turret6::CreateBullet() {
}

