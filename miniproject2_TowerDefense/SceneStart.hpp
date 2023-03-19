#ifndef SceneStart_HPP
#define SceneStart_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "IScene.hpp"

class SceneStart final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
	explicit SceneStart() = default;
	void Initialize() override;
	void Terminate() override;
	void PlayOnClick(int stage);
};

#endif // SceneStart_HPP
