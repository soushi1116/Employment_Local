#include "Event.h"
#include "../FPS/FPSManager.h"

namespace Event
{
	int m_StartCount = INT_MAX;

	// シーン遷移のカウント設定
	void SetStartCount()
	{
		FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
		m_StartCount = fps->GetTotalTime();
	}

	// カウント後にシーン遷移
	bool ChangeScene(int interval)
	{
		FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
		int sceneChangeCount = fps->GetTotalTime();

		if (sceneChangeCount - m_StartCount < interval)
		{
			return false;
		}
		else
		{
			return true;
		}
		
	}

	void ResetCount()
	{
		m_StartCount = INT_MAX;
	}
}