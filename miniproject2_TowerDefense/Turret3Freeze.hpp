#ifndef Turret3Freeze_HPP
#define Turret3Freeze_HPP
#include "Turret.hpp"

class Turret3Freeze : public Turret {
public:
	static const int Price;
	Turret3Freeze(float x, float y);
	void CreateBullet() override;
};
#endif // Turret1WBCell_HPP
#pragma once
