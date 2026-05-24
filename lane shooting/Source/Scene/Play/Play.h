#pragma once
#include "../SceneBase.h"
#include "../../Camera/CameraManager.h"
#include "../../Stage/Stage.h"
#include <vector>

class Skybox;
class Bullet;
class EnemySpawnManager;

class PlayScene : public SceneBase
{
public:
    PlayScene();
    ~PlayScene();

    void Init() override;
    void Load() override;
    void Start() override;
    void Step() override;
    void Update() override;
    void Draw() override;
    void Fin() override;

private:
    Stage* m_Stage;
    Skybox* m_Skybox;
    std::vector<Bullet*> m_Bullets;
    float m_ShotTimer;
    const float SHOT_COOLDOWN = 0.2f;
    EnemySpawnManager* m_SpawnManager;

	bool m_GameOver;       // ゲームオーバーフラグ
	float m_GameOverTimer;
};