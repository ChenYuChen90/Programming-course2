#ifndef SceneLose_HPP
#define SceneLose_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "IScene.hpp"

class SceneLose final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
	explicit SceneLose() = default;
	void Initialize() override;
	void Terminate() override;
	void BackOnClick(int stage);
};

#endif // SceneLose_HPP
