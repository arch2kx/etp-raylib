#include "player.hpp"

Player::Player()
    : texture{}, bulletTexture{},
      x(0.0f), y(520.0f), speed(360.0f),
      shootTimer(0.0f), shootCooldown(0.2f),
      health(100), maxHealth(100) {}

Player::Player(Texture2D tex, Texture2D bulletTex, float speedMult)
    : texture(tex), bulletTexture(bulletTex),
    x(400.0f - tex.width / 2.0f), y(520.0f),
    speed(360.0f * speedMult), shootTimer(0.0f), shootCooldown(0.2f),
    health(100), maxHealth(100) {}

void Player::Update(float dt, std::vector<Bullet>& playerBullets) {
    if (IsKeyDown(KEY_LEFT)  && x > 0)                         x -= speed * dt;
    if (IsKeyDown(KEY_RIGHT) && x + texture.width  < 800)      x += speed * dt;
    if (IsKeyDown(KEY_UP)    && y > 0)                         y -= speed * dt;
    if (IsKeyDown(KEY_DOWN)  && y + texture.height < 600)      y += speed * dt;

    shootTimer += dt;
    if (IsKeyDown(KEY_SPACE) && shootTimer >= shootCooldown) {
        float bx = x + texture.width  / 2.0f - bulletTexture.width  / 2.0f;
        float by = y;
        playerBullets.emplace_back(bx, by, -(PI / 2.0f), 600.0f,
                                   BulletType::FRIENDLY, bulletTexture);
        shootTimer = 0.0f;
    }
}

void Player::Draw() const {
    DrawTexture(texture, (int)x, (int)y, WHITE);
}

void Player::DrawHealthBar() const {
    const int barWidth  = 200;
    const int barHeight = 12;
    const int bx = 10;
    const int by = 578;
    int fill = (int)((health / (float)maxHealth) * barWidth);
    DrawRectangle(bx, by, barWidth, barHeight, Color{166, 81,  81,  255});
    DrawRectangle(bx, by, fill,     barHeight, Color{110, 212, 113, 255});
    DrawRectangleLines(bx, by, barWidth, barHeight, Color{240, 240, 240, 255});
}

Rectangle Player::GetRect() const {
    return Rectangle{ x, y, (float)texture.width, (float)texture.height };
}

void Player::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

bool Player::IsDead() const { return health <= 0; }
