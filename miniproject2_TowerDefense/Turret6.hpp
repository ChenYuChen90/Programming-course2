#ifndef Turret6_HPP
#define Turret6_HPP
#include "Turret.hpp"

class Turret6 : public Turret {
public:
	static const int Price;
	Turret6(float x, float y);
	void CreateBullet() override;
};
#endif // Turret1WBCell_HPP
#pragma once
