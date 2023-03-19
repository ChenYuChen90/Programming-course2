#ifndef Enemy1Normal_HPP
#define Enemy1Normal_HPP
#include "Enemy.hpp"

class Enemy1Normal : public Enemy {
public:
	Enemy1Normal(int x, int y);
	void CreateBulletEnemy() override;
};
#endif // Enemy1Normal_HPP
