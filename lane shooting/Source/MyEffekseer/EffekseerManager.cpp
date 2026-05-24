#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "EffekseerManager.h"
#include "EffekseerEffect.h"
#include "EffekseerParam.h"


EffekseerManager* EffekseerManager::m_Instance = nullptr;

EffekseerManager::EffekseerManager()
{
	m_EffectHandles = {};
	m_Effects = {};
}

EffekseerManager::~EffekseerManager()
{
	Fin();
}

void EffekseerManager::Setup()
{
	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);
}

bool EffekseerManager::Init()
{
	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(EFFEKSEER_MAX_PARTICLE) == -1)
	{
		return false;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	return true;
}

void EffekseerManager::Load()
{
	// ファイルパス群
	const char* PATH[] =
	{
		"Data/Effect/Effekseer_Hit.efkefc",
		"Data/Effect/PlayerDead.efkefc",
		"Data/Effect/BossDead.efkefc"
	};

	for (const char* path : PATH)
	{
		int handle = LoadEffekseerEffect(path);
		m_EffectHandles.push_back(handle);
	}
}

void EffekseerManager::Start()
{
}

EffekseerEffect* EffekseerManager::PlayEffect(int type, VECTOR pos)
{
	// 未使用のものがあれば使いまわす
	for (EffekseerEffect* effect : m_Effects)
	{
		if (!effect->IsActive())
		{
			// アクティブにする
			effect->SetActive(true);

			// 位置設定
			effect->SetPos(pos);

			// エフェクト再生
			effect->Play(m_EffectHandles[type]);

			// 再生するエフェクトを返却
			return effect;
		}
	}

	// 未使用のものがなければ新しく作る
	EffekseerEffect* effect = new EffekseerEffect;
	// アクティブにする
	effect->SetActive(true);
	// 位置設定
	effect->SetPos(pos);
	// エフェクト再生
	effect->Play(m_EffectHandles[type]);
	// 配列に追加
	m_Effects.push_back(effect);

	return effect;
}

void EffekseerManager::Step()
{
	// 各エフェクトを更新
	for (EffekseerEffect* effect : m_Effects)
	{
		effect->Step();
	}
}

void EffekseerManager::Update()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	// 各エフェクトを更新
	for (EffekseerEffect* effect : m_Effects)
	{
		effect->Update();
	}

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
}

void EffekseerManager::Draw()
{
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}

void EffekseerManager::Fin()
{
	// ロードしたものを削除
	for (int handle : m_EffectHandles)
	{
		DeleteEffekseerEffect(handle);
	}
	// 動的配列をクリア
	m_EffectHandles.clear();
	m_EffectHandles.shrink_to_fit();

	// 生成されたエフェクトを全て削除
	for (EffekseerEffect* effect : m_Effects)
	{
		delete effect;
	}
	// 動的配列をクリア
	m_Effects.clear();
	m_Effects.shrink_to_fit();

	// Effekseerを終了する。
	Effkseer_End();
}