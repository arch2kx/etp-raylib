#pragma once

struct DifficultySettings {
    float enemySpeedMult;
    float spawnDelayMult;
    float difficultyRamp;
    int   bossScoreThresh;
    bool  hasPhase2;
    // Boss scaling
    int   bossHP;             // Total boss health
    float bossBulletSpeed;    // Boss bullet travel speed (px/s)
    float bossShootCooldown;  // Seconds between boss volleys (lower = faster firing)
    bool  bossAimedShot;      // Hard+: adds one bullet aimed straight at the player each volley
    bool  bossBurst;          // Extreme: fires a second volley 0.15s after the first
    // Miss penalty
    int   missPenaltyGrace;   // Number of enemies the player can let through before HP penalty starts
    // Player scaling
    float playerSpeedMult;    // Multiplies player base move speed (360 px/s)
};

// Field order: enemySpeedMult, spawnDelayMult, difficultyRamp, bossScoreThresh, hasPhase2,
//              bossHP, bossBulletSpeed, bossShootCooldown, bossAimedShot, bossBurst,
//              missPenaltyGrace, playerSpeedMult
inline const DifficultySettings DIFF_EASY    = { 0.6f, 1.5f, 0.03f, 300, false,  40,
240.0f, 0.9f,  false, false, 0, 1.0f  };
inline const DifficultySettings DIFF_NORMAL  = { 1.0f, 1.0f, 0.05f, 150, false,  50,
280.0f, 0.7f,  false, false, 0, 1.0f  };
inline const DifficultySettings DIFF_HARD    = { 1.4f, 0.7f, 0.08f, 100, true,   70,
320.0f, 0.5f,  true,  false, 3, 1.15f };
inline const DifficultySettings DIFF_EXTREME = { 1.8f, 0.4f, 0.15f,  50, true,  100,
370.0f, 0.35f, true,  true,  5, 1.3f  };
