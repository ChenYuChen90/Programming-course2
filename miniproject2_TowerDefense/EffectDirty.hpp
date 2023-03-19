#ifndef EffectDirty_HPP
#define EffectDirty_HPP
#include <string>

#include "Sprite.hpp"

class ScenePlay;

class EffectDirty : public Engine::Sprite {
protected:
	float timeSpan;
	float alpha;
	ScenePlay* getScenePlay();
public:
	EffectDirty(std::string img, float timeSpan, float x, float y);
	void Update(float deltaTime) override;
};
#endif // EffectDirty_HPP
