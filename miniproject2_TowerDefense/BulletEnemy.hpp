#ifndef BULLET_HPP
#define BULLET_HPP
#include <string>

#include "Sprite.hpp"

class Enemy;
class ScenePlay;
class Turret;
namespace Engine {
	struct Point;
}  // namespace Engine

class BulletEnemy : public Engine::Sprite {
protected:
	float speed;
	float damage;
	Enemy* parent;
	ScenePlay* getScenePlay();
	/*-----------------�ĤH�g�l�u-----------------*/
	virtual void OnExplode(Turret* turret);
public:
	explicit BulletEnemy(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
	void Update(float deltaTime) override;
	/*-----------------�ĤH�g�l�u-----------------*/
	Turret* Target = nullptr;
	friend ScenePlay;
};
#endif // BULLET_HPP
