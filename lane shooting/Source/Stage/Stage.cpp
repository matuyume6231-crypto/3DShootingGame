#include "Stage.h"

#define DEFAULT_POS VGet(0.0f, 0.0f, 0.0f)


// コンストラクタ
Stage::Stage()
{
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
}

// デストラクタ
Stage::~Stage()
{
	Fin();
}

void Stage::Init()
{

}

void Stage::Load()
{
	m_Handle = MV1LoadModel("Data/Stage/Stage.x");
}

void Stage::Start()
{
	m_Pos = DEFAULT_POS;
}

void Stage::Step()
{
}

void Stage::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
}

void Stage::Draw()
{
	MV1DrawModel(m_Handle);
}

void Stage::Fin()
{
	MV1DeleteModel(m_Handle);
}

