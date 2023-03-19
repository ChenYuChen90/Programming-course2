#ifndef BULLET3FIRE_HPP
#define BULLET3FIRE_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
	struct Point;
}  // namespace Engine

class Bullet3Fire : public Bullet {
public:
	explicit Bullet3Fire(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
};
#endif // Bullet1IceCream_HPP
