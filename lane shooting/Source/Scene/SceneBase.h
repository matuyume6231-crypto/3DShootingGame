#pragma once

class SceneBase
{
public:
	SceneBase();	// コンストラクタ
	~SceneBase();	// デストラクタ

public:
	// 派生クラスには初期～終了までは実装必須にするため純粋仮想関数にする
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Fin() = 0;
};


