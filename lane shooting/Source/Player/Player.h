#pragma once

struct Player
{
    int lane;      // Œ»İ‚ÌƒŒ[ƒ“
    float x, y, z; // ˆÊ’u
};

// ŠÖ”
void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// æ“¾—p
Player* GetPlayer();