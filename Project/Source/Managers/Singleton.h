#pragma once
#include <memory>

template <typename T>
class Singleton
{
protected:
	Singleton() {}
	virtual ~Singleton() {}

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new T;
		}
	}

	static T* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

private:
	static T* m_Instance;
};

template <typename T>
T* Singleton<T>::m_Instance = nullptr;
