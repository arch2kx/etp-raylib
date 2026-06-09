#include "boss.hpp"
#include <cmath>
#include <vector>

Boss::Boss(Texture2D tex, Texture2D bulletTex, const DifficultySettings& diff)
    : texture(tex), bulletTexture(bulletTex),
      x(400.0f - tex.width / 2.0f), y(80.0f),
      health(diff.bossHP), maxHealth(diff.bossHP),
      speed(180.0f * diff.enemySpeedMult), direction(1),
      shootCooldown(diff.bossShootCooldown), shootTimer(0.0f),
      bulletSpeed(diff.bossBulletSpeed),
      aimedShot(diff.bossAimedShot), burst(diff.bossBurst),
      burstTimer(-1.0f) {}

void Boss::Update(float dt, std::vector<Bullet>& enemyBullets,
                  float playerX, float playerY) {
    x += direction * speed * dt;
    if (x + texture.width > 750) direction = -1;
    if (x < 50)                  direction =  1;

    if (burst && burstTimer >= 0.0f) {
        burstTimer += dt;
        if (burstTimer >= 0.15f) {
            Fire(enemyBullets, playerX, playerY);
            burstTimer = -1.0f;
        }
    }

    shootTimer += dt;
    if (shootTimer >= shootCooldown) {
        Fire(enemyBullets, playerX, playerY);
        shootTimer = 0.0f;
        if (burst) burstTimer = 0.0f;
    }
}

void Boss::Fire(std::vector<Bullet>& enemyBullets,
                float playerX, float playerY) {
    float cx = x + texture.width  / 2.0f;
    float cy = y + texture.height;

    std::vector<float> angles;
    if (health > maxHealth / 2) {
        angles = {-15.0f, 0.0f, 15.0f};
    } else {
        for (int a = -60; a <= 60; a += 15)
            angles.push_back((float)a);
    }

    for (float angleOffset : angles) {
        float rad     = angleOffset * DEG2RAD;
        float targetX = playerX + sinf(rad) * 100.0f;
        float targetY = playerY + cosf(rad) * 100.0f;
        float dx      = targetX - cx;
        float dy      = targetY - cy;
        float dist    = sqrtf(dx * dx + dy * dy);
        if (dist < 1.0f) dist = 1.0f;
        float dir = atan2f(dy, dx);
        enemyBullets.emplace_back(cx, cy, dir, bulletSpeed,
                                  BulletType::ENEMY, bulletTexture);
    }

    if (aimedShot) {
        float dx   = playerX - cx;
        float dy   = playerY - cy;
        float dist = sqrtf(dx * dx + dy * dy);
        if (dist < 1.0f) dist = 1.0f;
        float dir = atan2f(dy, dx);
        enemyBullets.emplace_back(cx, cy, dir, bulletSpeed,
                                  BulletType::ENEMY, bulletTexture);
    }
}

void Boss::Draw() const {
    DrawTexture(texture, (int)x, (int)y, WHITE);
}

void Boss::DrawHealthBar() const {
    const int barWidth  = 400;
    const int barHeight = 20;
    const int bx = (800 - barWidth) / 2;
    const int by = 20;
    int fill = (int)((health / (float)maxHealth) * barWidth);

    DrawRectangle(bx, by, barWidth, barHeight, Color{166, 81,  81,  255});
    DrawRectangle(bx, by, fill,     barHeight, Color{110, 212, 113, 255});
    DrawRectangleLines(bx, by, barWidth, barHeight, Color{240, 240, 240, 255});
}

bool Boss::IsDead() const { return health <= 0; }

Rectangle Boss::GetRect() const {
    return Rectangle{ x, y, (float)texture.width, (float)texture.height };
}
