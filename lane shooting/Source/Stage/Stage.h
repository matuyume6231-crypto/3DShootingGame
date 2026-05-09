#pragma once
#include "DxLib.h"

// ステージクラス
class Stage
{
public:
	Stage();
	~Stage();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

private:
	int m_Handle;
	VECTOR m_Pos;
};
