#pragma once
#include "raylib.h"
#include "player.hpp"
#include "enemy.hpp"
#include "boss.hpp"
#include "sniper.hpp"
#include "bullet.hpp"
#include "difficulty.hpp"
#include <vector>
#include <memory>

class Game {
public:
    Game(DifficultySettings settings = DIFF_NORMAL);
    ~Game();

    void Update(float dt);
    void Draw() const;
    bool IsGameOver() const;
    bool IsGameWon() const;
    void Reset(DifficultySettings settings = DIFF_NORMAL);

private:
    // Textures loaded once here, passed by value to entities (raylib textures are GPU handles)
    Texture2D bgTexture;
    Texture2D playerTex;
    Texture2D enemyTex;
    Texture2D bossTex;
    Texture2D friendlyBulletTex;
    Texture2D enemyBulletTex;
    Texture2D sniperTex;
    Font      font;

    Player              player;
    std::vector<Enemy>  enemies;
    std::vector<Bullet> playerBullets;
    std::vector<Bullet> enemyBullets;
    std::unique_ptr<Boss>    boss;
    std::vector<Sniper>      snipers;
    bool                     phase2Active;

    int   score;
    float difficulty;
    float spawnTimer;
    float spawnDelay;
    bool  bossSpawned;
    bool  gameOver;
    bool  gameWon;
    int   missedEnemyCount;
    DifficultySettings settings;

    void SpawnEnemy();
    void SpawnSnipers();
    void CheckCollisions();
    void DrawScore() const;
};
