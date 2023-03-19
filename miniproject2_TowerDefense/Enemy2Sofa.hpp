#ifndef Enemy2Sofa_HPP
#define Enemy2Sofa_HPP
#include "Enemy.hpp"

class Enemy2Sofa : public Enemy {
public:
	Enemy2Sofa(int x, int y);
	void CreateBulletEnemy() override;
};
#endif // Enemy2Sofa_HPP
