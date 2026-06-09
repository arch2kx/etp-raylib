#pragma once
#include "raylib.h"
#include "bullet.hpp"
#include <vector>

enum class MovementPattern { STRAIGHT, ZIGZAG, CIRCLE };

class Enemy {
public:
    Enemy(float x, int difficulty, float speedMult, Texture2D tex, Texture2D bulletTex);

    void Update(float dt, std::vector<Bullet>& enemyBullets);
    void Draw() const;
    bool IsOffscreen() const;
    bool IsActive() const;
    void SetInactive();
    Rectangle GetRect() const;

private:
    Texture2D texture;
    Texture2D bulletTexture;
    float x, y;
    float speed;           // pixels per second
    int difficulty;
    MovementPattern movementPattern;
    float fireDelay;       // seconds between shots
    float fireTimer;
    bool active;

    void Fire(std::vector<Bullet>& enemyBullets);
};
