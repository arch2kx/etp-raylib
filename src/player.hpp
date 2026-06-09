#pragma once
#include "raylib.h"
#include "bullet.hpp"
#include <vector>

class Player {
public:
    Player();
    Player(Texture2D tex, Texture2D bulletTex, float speedMult = 1.0f);

    void Update(float dt, std::vector<Bullet>& playerBullets);
    void Draw() const;
    void DrawHealthBar() const;
    Rectangle GetRect() const;
    void TakeDamage(int amount);
    bool IsDead() const;

    int health;
    int maxHealth;

private:
    Texture2D texture;
    Texture2D bulletTexture;
    float x, y;
    float speed;
    float shootTimer;
    float shootCooldown;
};
