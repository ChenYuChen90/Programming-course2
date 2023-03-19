// [main.cpp]
// this template is provided for the 2D tower defense game.
// Program entry point.
// Returns program exit code.
#include "GameEngine.hpp"
#include "LOG.hpp"
#include "SceneLose.hpp"
#include "ScenePlay.hpp"
#include "SceneStageSelect.hpp"
#include "WinScene.hpp"
#include "SceneStart.hpp"
#include "SceneSetting.hpp"

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();
    // TODO 1 (1/3): Add a New Scene here
	game.AddNewScene("setting", new SceneSetting());
	game.AddNewScene("stage-select", new SceneStageSelect());
	game.AddNewScene("play", new ScenePlay());
	game.AddNewScene("lose", new SceneLose());
	game.AddNewScene("win", new WinScene());
	game.AddNewScene("SceneStart", new SceneStart());
	
	game.Start("SceneStart", 60, 1536, 896);
	return 0;
}
