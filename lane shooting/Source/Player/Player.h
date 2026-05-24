#pragma once
#include "DxLib.h"

class CollisionAABB;
struct HitResultAABB;

// プレイヤークラス
class Player
{
public:
	Player();	// コンストラクタ
	~Player();	// デストラクタ

	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

	CollisionAABB* GetAABB() { return m_AABB; }

	VECTOR GetPos() { return m_Pos; }

public:
	void Damage(int damage);

	int GetHP() const { return m_HP; }
	bool IsDead() const { return m_IsDead; }
	bool IsInvincible() const { return m_IsInvincible; }

private:
	int m_Handle;	// 画像ハンドル
	int m_Lane;        // 現在レーン
	float m_LanePos[3]; // レーン位置
	VECTOR m_Pos;
	CollisionAABB* m_AABB;	// AABBの当たり判定

private:
	int m_HP;                // 体力
	bool m_IsInvincible;     // 無敵状態かどうか
	float m_InvincibleTimer; // 無敵状態の残り時間
	bool m_IsDead;           // 死亡フラグ
	bool m_DeathEffectPlayed;
};
