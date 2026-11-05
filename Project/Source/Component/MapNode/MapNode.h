#pragma once
#include "../../Managers/MapManager/MapManager.h"
#include "../Component.h"
#include <vector>
#include "DxLib.h"

class GameObject;

class MapNode : public Component
{
public:
	MapNode(GameObject* owner);
	~MapNode();

public:
	void Draw() override;

public:
	void SetNodeData(std::vector<VECTOR> nodeData) { m_NodeData = nodeData; }
	std::vector<VECTOR> GetNodeData() const { return m_NodeData; }

private:
	std::vector<VECTOR> m_NodeData;
};

