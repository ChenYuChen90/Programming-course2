#ifndef Bullet2Pocky_HPP
#define Bullet2Pocky_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class Bullet2Pocky : public Bullet {
public:
	explicit Bullet2Pocky(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
};
#endif // Bullet2Pocky_HPP
