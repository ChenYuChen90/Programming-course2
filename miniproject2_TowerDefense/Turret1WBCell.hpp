#ifndef Turret1WBCell_HPP
#define Turret1WBCell_HPP
#include "Turret.hpp"

class Turret1WBCell: public Turret {
public:
	static const int Price;
    Turret1WBCell(float x, float y);
	void CreateBullet() override;
};
#endif // Turret1WBCell_HPP
