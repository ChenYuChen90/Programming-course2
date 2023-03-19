#ifndef SceneSetting_HPP
#define SceneSetting_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "IScene.hpp"

class SceneSetting final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
	explicit SceneSetting() = default;
	void Initialize() override;
	void Terminate() override;
	void BackOnClick(int stage);
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
};

#endif // SELECTSCENE_HPP
#pragma once
