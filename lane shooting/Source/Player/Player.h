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

private:
	int m_Handle;	// 画像ハンドル
	int m_Lane;        // 現在レーン
	float m_LanePos[3]; // レーン位置
	VECTOR m_Pos;
	CollisionAABB* m_AABB;	// AABBの当たり判定
};
