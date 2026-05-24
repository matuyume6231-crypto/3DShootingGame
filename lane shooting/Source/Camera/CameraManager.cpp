#include "CameraManager.h"
#include "Camera.h"
#include "CameraDead.h"

// 静的変数の初期化
CameraManager* CameraManager::m_Instance = nullptr;

// コンストラクタ
CameraManager::CameraManager()
{
	// 生成されていなければnullptr
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		m_Camera[i] = nullptr;
	}

	m_ActiveCamera = CAMERA;
}

// デストラクタ
CameraManager::~CameraManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
}

void CameraManager::CreateCamera(CameraType type)
{
	switch (type)
	{
	case CAMERA:
		if (m_Camera[CAMERA] == nullptr)m_Camera[CAMERA] = new Camera;
		break;
	case CAMERA_BOSS_DEATH:
		if (m_Camera[CAMERA_BOSS_DEATH] == nullptr)
			m_Camera[CAMERA_BOSS_DEATH] = new CameraDead;
		break;
	}
}

void CameraManager::Init()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Init();
		}
	}
}

void CameraManager::Load()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Load();
		}
	}
}

void CameraManager::Start()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Start();
		}
	}
}

void CameraManager::Step()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Step();
		}
	}
}

void CameraManager::Update()
{
	CameraBase* camera = m_Camera[m_ActiveCamera];

	if (camera)
	{
		camera->Update();
	}
}

void CameraManager::Draw()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Draw();
		}
	}
}

void CameraManager::Fin()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			delete camera;
			m_Camera[i] = nullptr;
		}
	}
}

void CameraManager::SetActiveCamera(CameraType type)
{
	m_ActiveCamera = type;
}