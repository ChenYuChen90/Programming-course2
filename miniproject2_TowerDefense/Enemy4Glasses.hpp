#ifndef Enemy4Glasses_HPP
#define Enemy4Glasses_HPP
#include "Enemy.hpp"

class Enemy4Glasses : public Enemy {
public:
	Enemy4Glasses(int x, int y);
	void EnemyEffect(Enemy* enemy) override;
	void CreateBulletEnemy() override;
};
#endif // Enemy1Normal_HPP

