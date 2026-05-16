#include "SoundManager.h"
#include "DxLib.h"

SoundManager* SoundManager::m_Instance = nullptr;

SoundManager::SoundManager()
{
	m_ShotSE = -1;
	m_HitSE = -1;
	m_DamageSE = -1;

	m_GameBGM = -1;
}

SoundManager::~SoundManager()
{
	Fin();
}

void SoundManager::Load()
{
	m_ShotSE =
		LoadSoundMem("Data/Sound/SE/shot.wav");

	m_HitSE =
		LoadSoundMem("Data/Sound/SE/hit.wav");

	m_DamageSE =
		LoadSoundMem("Data/Sound/SE/damage.wav");

	m_GameBGM =
		LoadSoundMem("Data/Sound/BGM/game.mp3");
}

void SoundManager::Update()
{
}

void SoundManager::Fin()
{
	DeleteSoundMem(m_ShotSE);
	DeleteSoundMem(m_HitSE);
	DeleteSoundMem(m_DamageSE);

	DeleteSoundMem(m_GameBGM);
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

void SoundManager::PlayGameBGM()
{
	PlaySoundMem(m_GameBGM, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBGM()
{
	StopSoundMem(m_GameBGM);
}