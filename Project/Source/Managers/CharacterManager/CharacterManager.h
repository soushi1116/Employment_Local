#pragma once
//#include "CharacterBase.h"
//#include "CharacterParameter.h"
//#include "Rooter/Rooter.h"
#include <vector>
#include <list>
#include <string>
#include "../../Component/GameObject.h"
#include "../../Component/Component.h"
#include "../Singleton.h"

const int CHARACTER_MAX_NUM = 4;

class GameObject;
class CharacterParameter;

class CharacterManager : public Singleton<CharacterManager>
{
public:
	CharacterManager();
	~CharacterManager();

public:
	std::shared_ptr<GameObject> CreateCharacter(bool isPlayer, bool inBattleScene, CharacterType type);
	std::vector<int> GetStateIconList() const { return m_StateIconList; }
	void SetBossNum(int num) { m_BossNum = num; }
	int GetBossNum() const { return m_BossNum; }

	CharacterType GetCharacterType(int characterNum) { return m_CharacterType[characterNum]; }

	void SetCharacterType(int characterNum, CharacterType type) { m_CharacterType[characterNum] = type; }

	bool IsAlive(bool isBoss);

	std::vector<std::weak_ptr<GameObject>> GetCharacters() const { return m_Characters; }

	void AddParametersForResult(std::shared_ptr<CharacterParameter> param) { m_ParametersForResult.push_back(param); }

	std::vector<std::shared_ptr<CharacterParameter>> GetParametersForResult() { return m_ParametersForResult; }

private:
	std::vector<float> LoadStatusData(const std::string& filePath, CharacterType type);

private:
	static CharacterManager* m_Instance;

	std::vector<std::weak_ptr<GameObject>> m_Characters;

	std::vector<std::shared_ptr<CharacterParameter>> m_ParametersForResult;

	int m_BossNum;

	bool m_BossCreated;

	CharacterType m_CharacterType[CHARACTER_MAX_NUM];

	std::vector<int> m_StateIconList;

	//std::list<Rooter*> m_RooterList;
};
