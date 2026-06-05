#include "Player.h"
#include "CharacterParameter.h"

Player::Player() : CharacterBase()
{

}

Player::~Player()
{
	Fin();
}

void Player::Init()
{

}

void Player::Load()
{
	m_Handle = MV1LoadModel("Data/Character/Player.x");
}

void Player::Start()
{
	m_Scale = VGet(1.0f, 1.0f, 1.0f);

	m_Active = true;

	m_Type = PLAYER;
}

void Player::Step()
{

}

CharacterBase* Player::Clone()
{
	Player* clone = new Player;

	*clone = *this;

	clone->m_Handle = MV1DuplicateModel(m_Handle);

	return clone;
}