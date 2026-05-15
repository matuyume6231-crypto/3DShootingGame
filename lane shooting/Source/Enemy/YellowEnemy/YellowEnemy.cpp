#include "YellowEnemy.h"
#include "../../MyMath/MyMath.h"
#include "../../Collision/CollisionManager.h"
#include "../../Collision/CollisionAABB.h"

YellowEnemy::YellowEnemy()
{
	
}

YellowEnemy::~YellowEnemy()
{
}

void YellowEnemy::Init()
{
}

void YellowEnemy::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/YellowEnemy/YellowEnemy.x");
}

void YellowEnemy::Start()
{
	// AABB生成
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);

	// サイズは敵モデルに合わせて調整
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(1.0f, 1.0f, 1.0f));

	// 手前に進む速度
	m_Move = VGet(0.0f, 0.0f, -0.1f);

	m_Dead = false;
}

void YellowEnemy::Step()
{

}

// 呼ばれたオブジェクトの複製を作る関数
EnemyBase* YellowEnemy::Clone()
{
	// クローン用のオブジェクトを生成
	YellowEnemy* clone = new YellowEnemy;

	// クローン元と同じ値をセットしておく
	clone->m_Dead = false;

	// 画像はDuplicateする必要がある
	clone->m_Handle = MV1DuplicateModel(m_Handle);

	// AABBは後でStartで作るからここではnullptrでいいよ
	clone->m_AABB = nullptr;

	// 出来上がったクローンを返却
	return clone;
}
