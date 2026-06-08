#pragma once

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new ShadowMap;
		}
	}

	static ShadowMap* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void Init();
	void Fin();
	void StartDrawShadowMap();
	void EndDrawShadowMap();
	void StartAppearsShadowMap();
	void EndAppearsShadowMap();

private:
	static ShadowMap* m_Instance;
	int m_Handle;
};

