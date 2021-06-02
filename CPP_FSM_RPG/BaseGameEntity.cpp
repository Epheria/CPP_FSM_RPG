#include "BaseGameEntity.h"
#include <cassert>

int BaseGameEntity::m_nNextValidID = 0;

void BaseGameEntity::SetID(const int& id)
{
	assert((id >= m_nNextValidID) && "<BaseGameEntity::SetID>:invaild ID");

	m_nID = id;
	m_nNextValidID = m_nID + 1;
}