#include <allegro5/color.h>

#include "GameEngine.hpp"
#include "IScene.hpp"
#include "ScenePlay.hpp"
#include "TurretButton.hpp"
ScenePlay* TurretButton::getScenePlay() {
	return dynamic_cast<ScenePlay*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
TurretButton::TurretButton(std::string img, std::string imgIn, Engine::Sprite Turret, float x, float y, int money) :
	ImageButton(img, imgIn, x, y), money(money), Turret(Turret) {
}
//TurretButton::TurretButton(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite Turret, float x, float y, int money) :
//	ImageButton(img, imgIn, x, y), money(money), Base(Base), Turret(Turret) {
//}
void TurretButton::Update(float deltaTime) {
	ImageButton::Update(deltaTime);
	if (getScenePlay()->GetMoney() >= money) {
		Enabled = true;
		Turret.Tint = al_map_rgba(255, 255, 255, 255);
	} else {
		Enabled = false;
		Turret.Tint = al_map_rgba(0, 0, 0, 160);
	}
}
void TurretButton::Draw() const {
	ImageButton::Draw();
	Turret.Draw();
}
