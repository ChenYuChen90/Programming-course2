#ifndef Turret2Platelet_HPP
#define Turret2Platelet_HPP
#include "Turret.hpp"

class Turret2Platelet: public Turret {
public:
	static const int Price;
    Turret2Platelet(float x, float y);
	void CreateBullet() override;
	void Update(float deltaTime) override;
};
#endif // Turret2Platelet_HPP
