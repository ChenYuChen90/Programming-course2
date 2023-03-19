#ifndef BulletEnemy3_HPP
#define BulletEnemy3_HPP
#include "BulletEnemy.hpp"

class Enemy;
class Turret;
namespace Engine {
	struct Point;
}  // namespace Engine

class BulletEnemy3 : public BulletEnemy {
public:
	explicit BulletEnemy3(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
	void OnExplode(Turret* turret) override;
};
#endif // BulletEnemy1_HPP
