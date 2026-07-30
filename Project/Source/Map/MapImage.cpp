#include "MapImage.h"
#include "../MyMath/MyMath.h"
#include "../Character/CharacterManager.h"

const float MAP_IMAGE_SCALE = 180.0f;
const int MAP_IMAGE_POS_X = 1400;
const int MAP_IMAGE_POS_Y = 700;

MapImage::MapImage()
{
	m_Handle = 0;
	m_CharacterIndex = 0;
	m_MapScale = MyMath::VecZero();
	m_ImageScale = MyMath::VecZero();

	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		m_CharacterPos[i] = MyMath::VecZero();
	}
}

MapImage::~MapImage()
{
	Fin();
}

void MapImage::Init()
{
	
}

void MapImage::Load()
{
	m_Handle = LoadGraph("Data/UI/BattleScene/MapImage.png");
}

void MapImage::Start()
{
	m_ImageScale = MyMath::Vec2D(MAP_IMAGE_SCALE, MAP_IMAGE_SCALE);
}

void MapImage::Step()
{
	auto characterList = CharacterManager::GetInstance()->GetCharacterList();

	m_CharacterIndex = 0;

	VECTOR posOnMap = MyMath::VecZero();
	float convPosX = 0.0f;
	float convPosY = 0.0f;

	for (auto& character : characterList)
	{
		posOnMap = character->GetPos();

		convPosX = posOnMap.x * m_MapScale.x / m_ImageScale.x;
		convPosY = posOnMap.z * m_MapScale.z / m_ImageScale.y;

		m_CharacterPos[m_CharacterIndex] = MyMath::Vec2D(convPosX, convPosY);

		m_CharacterIndex++;
	}
}

void MapImage::Update()
{

}

void MapImage::Draw()
{
	DrawRotaGraph(MAP_IMAGE_POS_X, MAP_IMAGE_POS_Y, 1.0, 0.0, m_Handle, TRUE);

	auto characterList = CharacterManager::GetInstance()->GetCharacterList();

	for (int i = 0; i < static_cast<int>(characterList.size()); i++)
	{
		auto& character = characterList[i];

		float drawPosX = m_CharacterPos[i].x + MAP_IMAGE_POS_X;
		float drawPosY = m_CharacterPos[i].y + MAP_IMAGE_POS_Y;

		if (character->IsBoss())
		{
			DrawCircle((int)drawPosX, (int)drawPosY, 15, GetColor(255, 0, 0));
		}
		else
		{
			DrawCircle((int)drawPosX, (int)drawPosY, 8, GetColor(255, 0, 0));
		}
	}
}

void MapImage::Fin()
{
	DeleteGraph(m_Handle);
}