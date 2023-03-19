#include "BulletEnemy.hpp"
#include "Collider.hpp"
#include "Turret.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Sprite.hpp"

ScenePlay* BulletEnemy::getScenePlay() {
	return dynamic_cast<ScenePlay*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void BulletEnemy::OnExplode(Turret* turret) {
}
BulletEnemy::BulletEnemy(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent) :
	Sprite(img, position.x, position.y), speed(speed), damage(damage), parent(parent) {
	Velocity = forwardDirection * speed * (-1);
	Rotation = rotation;
	CollisionRadius = 4;
}
void BulletEnemy::Update(float deltaTime) {
	// need check
	
	Sprite::Update(deltaTime);
	ScenePlay* scene = getScenePlay();
	// Can be improved by Spatial Hash, Quad Tree, ...
	// However simply loop through all enemies is enough for this program.
	
	for (auto& it : scene->TowerGroup->GetObjects()) {
		Turret* turret = dynamic_cast<Turret*>(it);
		if (!turret->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, turret->Position, turret->CollisionRadius)) {
			OnExplode(turret);
			turret->Hit(damage);
			getScenePlay()->BulletGroup->RemoveObject(objectIterator);
			return;
		}
	}
	
	// Check if out of boundary.
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), ScenePlay::GetClientSize()))
		getScenePlay()->BulletGroup->RemoveObject(objectIterator);
	
}
