#include "MapNode.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../../MyColor/MyColor.h"

MapNode::MapNode(GameObject* owner) : Component(owner)
{
	
}

MapNode::~MapNode()
{

}

void MapNode::Draw()
{
	if (m_NodeData.empty()) return;

	for (VECTOR nodePos : m_NodeData)
	{
		DrawSphere3D(nodePos, 5.0f, 16, COLOR_SYAN, COLOR_SYAN, false);
	}
}