#ifndef Turret7_HPP
#define Turret7_HPP
#include "Turret.hpp"

class Turret7 : public Turret {
public:
	static const int Price;
	Turret7(float x, float y);
	void CreateBullet() override;
};
#endif // Turret1WBCell_HPP
#pragma once
