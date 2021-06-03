#include "PlayerOwnedStates.h"
#include "EntityNames.h"
#include "ConsoleUtils.h"

// �����ؾ���
// EnterDungeonAndFarming ---------------------------------------------
EnterDungeonAndFarming* EnterDungeonAndFarming::Instance()
{
	static EnterDungeonAndFarming instance;
	return &instance;
}

void EnterDungeonAndFarming::Enter(Player* pPlayer)
{
	if (pPlayer->Location() != Location_Type::Dungeon)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":�������� ����" << std::endl;

		pPlayer->ChangeLocation(Location_Type::Dungeon);
	}
}

void EnterDungeonAndFarming::Execute(Player* pPlayer)
{
	int nRandom;

	pPlayer->IncreaseFatigue();
	pPlayer->DecreaseDruability();

	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	nRandom = rand() % 10;
	if (nRandom >= 0 && nRandom < 7)
	{
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":���� 1������ ����Ͽ� 1��带 ������ϴ�." << std::endl;
		pPlayer->AddToGoldCarried(1);
	}
	else if (nRandom >= 7 && nRandom <= 8)
	{
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":��θӸ� ���� 1������ ����Ͽ� 2��带 ������ϴ�." << std::endl;
		pPlayer->AddToGoldCarried(2);
	}
	else if (nRandom == 9)
	{
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":������ ����Ͽ� 3��带 ������ϴ�." << std::endl;
		pPlayer->AddToGoldCarried(3);
	}

	if (pPlayer->PocketsFull())
		pPlayer->ChangeState(VisitBankAndDepositGold::Instance());

	if (pPlayer->Thirsty())
		pPlayer->ChangeState(QuenchThirst::Instance());

	if (pPlayer->ZeroDurability())
		pPlayer->ChangeState(FixWeaponAtStore::Instance());
}

void EnterDungeonAndFarming::Exit(Player* pPlayer)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pPlayer->ID()) << ":��� " << pPlayer->GoldCarried() << "���� ������ �������� ���Խ��ϴ�." << std::endl;
}

// ---------------------------------------------------------

// VisitBankAndDepositGold ----------------------------------
VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
	static VisitBankAndDepositGold instance;
	return &instance;
}

void VisitBankAndDepositGold::Enter(Player* pPlayer)
{
	if (pPlayer->Location() != Location_Type::bank)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":�������� �̵�" << std::endl;

		pPlayer->ChangeLocation(Location_Type::bank);
	}
}

void VisitBankAndDepositGold::Execute(Player* pPlayer)
{
	pPlayer->AddToWealth(pPlayer->GoldCarried());

	pPlayer->SetGoldCarried(0);

	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pPlayer->ID()) << ":��� ����\n\n���� �ܱ�: " << pPlayer->Wealth() << std::endl;

	if (pPlayer->Wealth() >= COMFORT_LEVEL)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":\"���! ���� ���� ���ڴ�. ���� �ִ� �Ƴ����Է� ���ư���.\"" << std::endl;

		pPlayer->ChangeState(GoInnAndSleepTillRested::Instance());
	}
	else
	{
		pPlayer->ChangeState(EnterDungeonAndFarming::Instance());
	}
}

void VisitBankAndDepositGold::Exit(Player* pPlayer)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pPlayer->ID()) << ":������ ������" << std::endl;
}

// ---------------------------------------------------------

// GoInnAndSleepTillRested ----------------------------------
GoInnAndSleepTillRested* GoInnAndSleepTillRested::Instance()
{
	static GoInnAndSleepTillRested instance;
	return &instance;
}

void GoInnAndSleepTillRested::Enter(Player* pPlayer)
{
	if (pPlayer->Location() != Location_Type::Inn)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":�������� ����" << std::endl;

		pPlayer->ChangeLocation(Location_Type::Inn);
	}
}

void GoInnAndSleepTillRested::Execute(Player* pPlayer)
{
	if (!pPlayer->Fatigued())
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":\"�޽��� ���ߴ�. �ٽ� �Ĺ��Ϸ� ���߰ڱ�!\"" << std::endl;

		pPlayer->ChangeState(EnterDungeonAndFarming::Instance());
	}
	else
	{
		pPlayer->DecreaseFatigue();
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":...zZ" << std::endl;
	}
}

void GoInnAndSleepTillRested::Exit(Player* pPlayer)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pPlayer->ID()) << ":������ ������" << std::endl;
}

// ---------------------------------------------------------

// GoInnAndSleepTillRested ----------------------------------
QuenchThirst* QuenchThirst::Instance()
{
	static QuenchThirst instance;
	return &instance;
}

void QuenchThirst::Enter(Player* pPlayer)
{
	if (pPlayer->Location() != Location_Type::Guild)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":\"���� ������!\"" << std::endl;
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":���� ����" << std::endl;

		pPlayer->ChangeLocation(Location_Type::Guild);
	}
}

void QuenchThirst::Execute(Player* pPlayer)
{
	if (pPlayer->Thirsty())
	{
		pPlayer->VisitGuildAndDrink();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":���� ���Ŵ�." << std::endl;

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "\n���� �ܱ�: " << pPlayer->Wealth() << std::endl << std::endl;

		pPlayer->ChangeState(EnterDungeonAndFarming::Instance());
	}
	else
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "\nERROR! \nERROR!" << std::endl;
	}
}

void QuenchThirst::Exit(Player* pPlayer)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pPlayer->ID()) << ":��带 ������." << std::endl;
}
// ---------------------------------------------------------

// FixWeaponAtStore ----------------------------------
FixWeaponAtStore* FixWeaponAtStore::Instance()
{
	static FixWeaponAtStore instance;
	return &instance;
}

void FixWeaponAtStore::Enter(Player* pPlayer)
{
	if (pPlayer->Location() != Location_Type::Store)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":���� �������� ����" << std::endl;

		pPlayer->ChangeLocation(Location_Type::Store);
	}
}

void FixWeaponAtStore::Execute(Player* pPlayer)
{
	if (pPlayer->ZeroDurability())
	{
		pPlayer->FixWeapon();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":\"���� �������� ����!\"" << std::endl;
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":���⸦ �����Ѵ�." << std::endl;

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "\n���� �ܱ�: " << pPlayer->Wealth() << std::endl << std::endl;

		pPlayer->ChangeState(EnterDungeonAndFarming::Instance());
	}
}

void FixWeaponAtStore::Exit(Player* pPlayer)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pPlayer->ID()) << ":��������� ������." << std::endl;
}