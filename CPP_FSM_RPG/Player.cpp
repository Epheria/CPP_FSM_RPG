#include "Player.h"
#include "PlayerOwnedStates.h"
#include <cassert>

Player::Player(const int& id) :
	BaseGameEntity(id),
	m_Location(Location_Type::Inn),
	m_nGoldCarried(0),
	m_nMoneyInBank(0),
	m_nThirst(0),
	m_nFatigue(0),
	m_nWeaponDurability(WEAPON_DURABILITY),
	m_pCurrState(GoInnAndSleepTillRested::Instance()) {}

void Player::Update()
{
	m_nThirst += 1;

	if (m_pCurrState)
	{
		m_pCurrState->Execute(this);
	}
}

void Player::ChangeState(State* pState)
{
	assert(m_pCurrState && pState);

	m_pCurrState->Exit(this);
	m_pCurrState = pState;
	m_pCurrState->Enter(this);
}

void Player::AddToGoldCarried(const int& value)
{
	m_nGoldCarried += value;

	//if (m_nGoldCarried > MAX_GOLD)
	//{
	//	m_nGoldCarried = MAX_GOLD;
	//}

	if (m_nGoldCarried < 0)
	{
		m_nGoldCarried = 0;
	}
}

void Player::AddToWealth(const int& value)
{
	m_nMoneyInBank += value;
	if (m_nMoneyInBank < 0)
	{
		m_nMoneyInBank = 0;
	}
}

bool Player::Thirsty() const
{
	if (THIRST_LEVEL <= m_nThirst)
	{
		return true;
	}

	return false;
}

bool Player::Fatigued() const
{
	if (TIREDNESS_THRESHOLD < m_nFatigue)
	{
		return true;
	}

	return false;
}

bool Player::ZeroDurability() const
{
	if (m_nWeaponDurability <= 0)
	{
		return true;
	}

	return false;
}