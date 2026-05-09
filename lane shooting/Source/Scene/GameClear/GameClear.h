#pragma once
#include "../SceneBase.h"

class GameClearScene : public SceneBase
{
public:
    GameClearScene();
    ~GameClearScene();

    void Init() override;
    void Load() override;
    void Start() override;
    void Step() override;
    void Update() override;
    void Draw() override;
    void Fin() override;
};