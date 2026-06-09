#include "enemy.hpp"
#include <cmath>
#include <cstdlib>

Enemy::Enemy(float x, int difficulty, float speedMult, Texture2D tex, Texture2D bulletTex)
    : texture(tex), bulletTexture(bulletTex),
      x(x), y(-50.0f),
      speed((5.0f + difficulty * 0.8f) * 60.0f * speedMult),
      difficulty(difficulty),
      fireDelay(fmaxf(1.5f - difficulty * 0.2f, 0.3f)),
      fireTimer(0.0f), active(true) {

    if (difficulty >= 3) {
        int r = rand() % 3;
        if      (r == 0) movementPattern = MovementPattern::STRAIGHT;
        else if (r == 1) movementPattern = MovementPattern::ZIGZAG;
        else             movementPattern = MovementPattern::CIRCLE;
    } else {
        movementPattern = MovementPattern::STRAIGHT;
    }
}

void Enemy::Update(float dt, std::vector<Bullet>& enemyBullets) {
    y += speed * dt;

    switch (movementPattern) {
        case MovementPattern::STRAIGHT:
            break;
        case MovementPattern::ZIGZAG:
            x += 5.0f * sinf(GetTime() * 5.0f) * dt * 60.0f;
            break;
        case MovementPattern::CIRCLE:
            x += 10.0f * sinf(GetTime() * 10.0f) * dt * 60.0f;
            break;
    }

    fireTimer += dt;
    if (fireTimer >= fireDelay) {
        Fire(enemyBullets);
        fireTimer = 0.0f;
    }
}

void Enemy::Fire(std::vector<Bullet>& enemyBullets) {
    float cx  = x + texture.width  / 2.0f;
    float cy  = y + texture.height;
    const float spd = 250.0f;

    // DEG2RAD is defined by raylib.h
    if (difficulty == 1) {
        enemyBullets.emplace_back(cx, cy, 90.0f * DEG2RAD, spd,
                                  BulletType::ENEMY, bulletTexture);
    } else if (difficulty == 2) {
        for (int angle : {80, 90, 100})
            enemyBullets.emplace_back(cx, cy, angle * DEG2RAD, spd,
                                      BulletType::ENEMY, bulletTexture);
    } else if (difficulty == 3) {
        for (int angle : {70, 80, 90, 100, 110})
            enemyBullets.emplace_back(cx, cy, angle * DEG2RAD, spd,
                                      BulletType::ENEMY, bulletTexture);
    } else {
        // Spiral burst: base angle rotates over time
        // Python: (get_ticks()/10) % 360 → GetTime()*100 degrees
        float baseAngle = fmodf(GetTime() * 100.0f, 360.0f);
        for (int i = 0; i < 8; i++) {
            float angle = (baseAngle + i * 45.0f) * DEG2RAD;
            enemyBullets.emplace_back(cx, cy, angle, spd,
                                      BulletType::ENEMY, bulletTexture);
        }
    }
}

void Enemy::Draw() const {
    DrawTexture(texture, (int)x, (int)y, WHITE);
}

bool Enemy::IsOffscreen() const { return y > 600; }
bool Enemy::IsActive()    const { return active; }
void Enemy::SetInactive()       { active = false; }

Rectangle Enemy::GetRect() const {
    return Rectangle{ x, y, (float)texture.width, (float)texture.height };
}
