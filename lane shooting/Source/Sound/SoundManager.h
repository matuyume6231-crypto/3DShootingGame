#pragma once

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new SoundManager;
		}
	}

	static SoundManager* GetInstance()
	{
		return m_Instance;
	}

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void Load();
	void Update();
	void Fin();

public:
	void PlayShotSE();
	void PlayHitSE();
	void PlayDamageSE();
	void PlayFocusSE();
	void PlayBombSE();
	void PlayGameBGM();
	void StopBGM();

private:
	static SoundManager* m_Instance;

private:
	int m_ShotSE;
	int m_HitSE;
	int m_DamageSE;
	int m_FocusSE;
	int m_BombSE;
	int m_GameBGM;
};