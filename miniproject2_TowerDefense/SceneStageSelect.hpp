#ifndef SceneStageSelect_HPP
#define SceneStageSelect_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "IScene.hpp"

class SceneStageSelect final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
	explicit SceneStageSelect() = default;
	void Initialize() override;
	void Terminate() override;
	void PlayOnClick(int stage);
	void SettingOnClick();
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
};

#endif // SceneStageSelect_HPP
