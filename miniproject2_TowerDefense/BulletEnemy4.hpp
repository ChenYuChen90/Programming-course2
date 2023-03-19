#ifndef BulletEnemy1_HPP
#define BulletEnemy1_HPP
#include "BulletEnemy.hpp"

class Enemy;
class Turret;
namespace Engine {
	struct Point;
}  // namespace Engine

class BulletEnemy4 : public BulletEnemy {
public:
	explicit BulletEnemy4(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
	void OnExplode(Turret* turret) override;
};
#endif // BulletEnemy1_HPP
