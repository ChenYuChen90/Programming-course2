#include <cmath>
#include <string>

#include "EffectShoot.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "ScenePlay.hpp"
#include "Resources.hpp"
// TODO 3 (2/2): You can imitate the 2 files: '"EffectExplosion.hpp', '"EffectExplosion.cpp' to create a EffectShoot.
ScenePlay* EffectShoot::getScenePlay() {
	return dynamic_cast<ScenePlay*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
EffectShoot::EffectShoot(float x, float y) : Sprite("play/shoot-1.png", x, y), timeTicks(0) {
	for (int i = 1; i <= 4; i++) {
		bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/shoot-" + std::to_string(i) + ".png"));
	}
}
void EffectShoot::Update(float deltaTime) {
	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		getScenePlay()->EffectGroup->RemoveObject(objectIterator);
		return;
	}
	int phase = floor(timeTicks / timeSpan * bmps.size());
	bmp = bmps[phase];
	Sprite::Update(deltaTime);
}
