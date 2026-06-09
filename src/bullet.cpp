#include "bullet.hpp"
#include <cmath>

Bullet::Bullet(float x, float y, float direction, float speed,
               BulletType type, Texture2D tex)
    : x(x), y(y), direction(direction), speed(speed),
      type(type), texture(tex), active(true) {}

void Bullet::Update(float dt) {
    x += std::cos(direction) * speed * dt;
    y += std::sin(direction) * speed * dt;
}

void Bullet::Draw() const {
    DrawTexture(texture, (int)x, (int)y, WHITE);
}

bool Bullet::IsOffscreen() const {
    return y > 600 || y + texture.height < 0 ||
           x > 800 || x + texture.width  < 0;
}

bool Bullet::IsActive() const  { return active; }
void Bullet::SetInactive()     { active = false; }

Rectangle Bullet::GetRect() const {
    return Rectangle{ x, y, (float)texture.width, (float)texture.height };
}
