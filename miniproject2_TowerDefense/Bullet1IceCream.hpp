#ifndef Bullet1IceCream_HPP
#define Bullet1IceCream_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class Bullet1IceCream : public Bullet {
public:
	explicit Bullet1IceCream(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
};
#endif // Bullet1IceCream_HPP
