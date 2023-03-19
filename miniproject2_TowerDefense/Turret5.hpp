#ifndef Turret5_HPP
#define Turret5_HPP
#include "Turret.hpp"

class Turret5 : public Turret {
public:
	static const int Price;
	Turret5(float x, float y);
	void CreateBullet() override;
};
#endif // Turret1WBCell_HPP
#pragma once
