#pragma once
#include "Dxlib.h"
#include <vector>
#include <memory>
#include "../../Component/Effect/EffectBase.h"
#include "../Singleton.h"

class GameObject;
class Physics3D;

class EffectManager : public Singleton<EffectManager>
{
public:
	EffectManager();
	~EffectManager();

public:
	void SetUp();
	bool Init();
	void Load();
	void Start();

	std::shared_ptr<GameObject> PlayEffect(EffekseerEffectType type, std::weak_ptr<Physics3D> parentPhysics);
	void DeleteEffect();

	void Step();
	void Update();
	void Draw();
	void Fin();

private:
	static EffectManager* m_Instance;

	std::vector<int> m_EffectHandles;
	std::vector<std::weak_ptr<GameObject>> m_Effects;
};

