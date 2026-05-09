#pragma once
#include "../SceneBase.h"
#include "../../Camera/CameraManager.h"
#include "../../Stage/Stage.h"
#include <vector>

class Bullet;

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

    std::vector<Bullet*> m_Bullets;
    float m_ShotTimer;
    const float SHOT_COOLDOWN = 0.2f;
};