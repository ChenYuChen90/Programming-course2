#ifndef TURRET_HPP
#define TURRET_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Sprite.hpp"

class Enemy;
class BulletEnemy;
class ScenePlay;

class Turret: public Engine::Sprite {
protected:
    int price;
    float hp;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    std::list<Turret*>::iterator lockedTurretIterator;
    ScenePlay* getScenePlay();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;
    /*-----------------敵人射子彈-----------------*/
    virtual void OnExplode();

public:
    bool level = false;
    bool Enabled = true;
    bool Preview = false;
    Enemy* Target = nullptr;
    Turret(/*std::string imgBase,*/std::string imgTurret, float x, float y,/* float radius,*/ int price, float coolDown, float hp);
    void Update(float deltaTime) override;
    void Draw() const override;
	int GetPrice() const;
    /*-----------------敵人射子彈-----------------*/
    void Hit(float damage);
    std::list<Enemy*> lockedEnemies;
    std::list<BulletEnemy*> lockedBulletEnemies;
    friend ScenePlay;
    /*----------------level up--------------------*/
    bool level_up = false;
};
#endif // TURRET_HPP
