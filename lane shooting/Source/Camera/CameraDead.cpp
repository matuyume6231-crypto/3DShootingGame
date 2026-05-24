#include "CameraDead.h"
#include "DxLib.h"
#include "../Enemy/Boss/Boss.h"
#include <math.h>

void CameraDead::Init()
{
	m_Time = 0.0f;
	m_Finished = false;
	m_Boss = nullptr;
}

void CameraDead::Load()
{
}

void CameraDead::Start()
{
	m_Time = 0.0f;
	m_Finished = false;

	// ボスを正面から見る位置（固定）
	m_Pos = VGet(0.0f, 4.0f, 25.0f);
	m_Target = VGet(0.0f, 0.0f, 40.0f);
	m_UpVec = VGet(0.0f, 1.0f, 0.0f);

	SetCameraNearFar(0.01f, 1000.0f);
}

void CameraDead::Step()
{
	m_Time += 1.0f / 60.0f;

	if (m_Time > 8.5f) // 約9秒演出
	{
		m_Finished = true;
	}
}

void CameraDead::Update()
{
	if (m_Boss)
	{
		m_Target = m_Boss->GetPos();
	}

	SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
}

void CameraDead::Draw()
{
}

void CameraDead::Fin()
{
}