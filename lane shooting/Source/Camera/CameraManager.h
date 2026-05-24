#pragma once
#include "CameraBase.h"

// カメラの種類
enum CameraType
{
	CAMERA,
	CAMERA_BOSS_DEATH,
	CAMERA_TYPE_MAX,
	CAMERA_NONE = -1,
};

// プレイヤーオブジェクト管理クラス
class CameraManager
{
public:
	CameraManager();	// コンストラクタ
	~CameraManager();	// デストラクタ

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new CameraManager; }
	static CameraManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

public:
	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

public:
	void CreateCamera(CameraType type);

	// 管理中のカメラを取得する
	CameraBase* GetCamera(CameraType type) { return m_Camera[type]; }

	void SetActiveCamera(CameraType type);
	CameraType GetActiveCamera() const { return m_ActiveCamera; }

private:
	static CameraManager* m_Instance;
	CameraBase* m_Camera[CAMERA_TYPE_MAX];
	CameraType m_ActiveCamera;
};
