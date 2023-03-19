#ifndef Enemy3Strong_HPP
#define Enemy3Strong_HPP
#include "Enemy.hpp"

class Enemy3Strong : public Enemy {
public:
	Enemy3Strong(int x, int y);
	void CreateBulletEnemy() override;
};
#endif // Enemy3Strong_HPP
