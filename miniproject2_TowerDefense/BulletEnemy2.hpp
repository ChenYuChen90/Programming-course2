#ifndef BulletEnemy2_HPP
#define BulletEnemy2_HPP
#include "BulletEnemy.hpp"

class Enemy;
class Turret;
namespace Engine {
	struct Point;
}  // namespace Engine

class BulletEnemy2 : public BulletEnemy {
public:
	explicit BulletEnemy2(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
	void OnExplode(Turret* turret) override;
};
#endif // BulletEnemy1_HPP