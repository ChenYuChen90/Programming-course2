#ifndef EffectShoot_HPP
#define EffectShoot_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <vector>

#include "Sprite.hpp"

class ScenePlay;

class EffectShoot : public Engine::Sprite {
protected:
	ScenePlay* getScenePlay();
	float timeTicks;
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
	float timeSpan = 0.5;
public:
	EffectShoot(float x, float y);
	void Update(float deltaTime) override;
};
#endif // EffectExplosion_HPP
