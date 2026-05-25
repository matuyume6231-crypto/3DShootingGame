#include "SoundManager.h"
#include "DxLib.h"

SoundManager* SoundManager::m_Instance = nullptr;

SoundManager::SoundManager()
{
	m_ShotSE = -1;
	m_HitSE = -1;
	m_DamageSE = -1;
	m_FocusSE = -1;
	m_BombSE = -1;
	m_TitleBGM = -1;
	m_GameBGM = -1;
	m_ClearBGM = -1;
	m_OverBGM = -1;
}

SoundManager::~SoundManager()
{
	Fin();
}

void SoundManager::Load()
{
	m_ShotSE =
		LoadSoundMem("Data/Sound/SE/shot.ogg");

	m_HitSE =
		LoadSoundMem("Data/Sound/SE/hit.ogg");

	m_DamageSE =
		LoadSoundMem("Data/Sound/SE/damage.ogg");

	m_FocusSE =
		LoadSoundMem("Data/Sound/SE/focus.ogg");

	m_BombSE =
		LoadSoundMem("Data/Sound/SE/bomb.ogg");

	m_TitleBGM = 
		LoadSoundMem("Data/Sound/BGM/title.ogg");

	m_GameBGM =
		LoadSoundMem("Data/Sound/BGM/play.ogg");

	m_ClearBGM =
		LoadSoundMem("Data/Sound/BGM/clear.ogg");

	m_OverBGM =
		LoadSoundMem("Data/Sound/BGM/over.ogg");
}

void SoundManager::Update()
{
}

void SoundManager::Fin()
{
	DeleteSoundMem(m_ShotSE);
	DeleteSoundMem(m_HitSE);
	DeleteSoundMem(m_DamageSE);
	DeleteSoundMem(m_FocusSE);
	DeleteSoundMem(m_BombSE);
	DeleteSoundMem(m_TitleBGM);
	DeleteSoundMem(m_GameBGM);
	DeleteSoundMem(m_ClearBGM);
	DeleteSoundMem(m_OverBGM);
}

void SoundManager::PlayShotSE()
{
	PlaySoundMem(m_ShotSE, DX_PLAYTYPE_BACK);
}

void SoundManager::PlayHitSE()
{
	PlaySoundMem(m_HitSE, DX_PLAYTYPE_BACK);
}

void SoundManager::PlayDamageSE()
{
	PlaySoundMem(m_DamageSE, DX_PLAYTYPE_BACK);
}

void SoundManager::PlayFocusSE()
{
	PlaySoundMem(m_FocusSE, DX_PLAYTYPE_BACK);
}

void SoundManager::PlayBombSE()
{
	PlaySoundMem(m_BombSE, DX_PLAYTYPE_BACK);
}

void SoundManager::PlayTitleBGM()
{
	PlaySoundMem(m_TitleBGM, DX_PLAYTYPE_LOOP);
}

void SoundManager::PlayGameBGM()
{
	PlaySoundMem(m_GameBGM, DX_PLAYTYPE_LOOP);
}

void SoundManager::PlayClearBGM()
{
	PlaySoundMem(m_ClearBGM, DX_PLAYTYPE_LOOP);
}

void SoundManager::PlayOverBGM()
{
	PlaySoundMem(m_OverBGM, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBGM()
{
	StopSoundMem(m_TitleBGM);
	StopSoundMem(m_GameBGM);
	StopSoundMem(m_ClearBGM);
	StopSoundMem(m_OverBGM);
}