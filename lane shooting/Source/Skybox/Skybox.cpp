#include "Skybox.h"

Skybox::Skybox()
{
	m_Handle = 0;
	m_Pos = {};
}

Skybox::~Skybox()
{
	Fin();
}

void Skybox::Load(const char* path)
{
	m_Handle = MV1LoadModel(path);
}

void Skybox::Step()
{
}

void Skybox::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
}

void Skybox::Draw()
{
	MV1DrawModel(m_Handle);
}

void Skybox::Fin()
{
	MV1DeleteModel(m_Handle);
}