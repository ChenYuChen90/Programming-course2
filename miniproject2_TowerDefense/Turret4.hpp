#ifndef Turret4_HPP
#define Turret4_HPP
#include "Turret.hpp"

class Turret4 : public Turret {
public:
	static const int Price;
	Turret4(float x, float y);
	void CreateBullet() override;
};
#endif // Turret1WBCell_HPP
#pragma once
