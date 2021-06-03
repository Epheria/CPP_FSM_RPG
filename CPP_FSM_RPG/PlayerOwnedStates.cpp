#include "PlayerOwnedStates.h"
#include "EntityNames.h"
#include "ConsoleUtils.h"

// 수정해야함
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
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":던전으로 들어간다" << std::endl;

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
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":몬스터 1마리를 사냥하여 1골드를 얻었습니다." << std::endl;
		pPlayer->AddToGoldCarried(1);
	}
	else if (nRandom >= 7 && nRandom <= 8)
	{
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":우두머리 몬스터 1마리를 사냥하여 2골드를 얻었습니다." << std::endl;
		pPlayer->AddToGoldCarried(2);
	}
	else if (nRandom == 9)
	{
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":보스를 사냥하여 3골드를 얻었습니다." << std::endl;
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
	std::cout << GetNameOfEntity(pPlayer->ID()) << ":골드 " << pPlayer->GoldCarried() << "개를 가지고 던전에서 나왔습니다." << std::endl;
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
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":은행으로 이동" << std::endl;

		pPlayer->ChangeLocation(Location_Type::bank);
	}
}

void VisitBankAndDepositGold::Execute(Player* pPlayer)
{
	pPlayer->AddToWealth(pPlayer->GoldCarried());

	pPlayer->SetGoldCarried(0);

	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pPlayer->ID()) << ":골드 저금\n\n현재 잔금: " << pPlayer->Wealth() << std::endl;

	if (pPlayer->Wealth() >= COMFORT_LEVEL)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":\"우와! 이제 나는 부자다. 집에 있는 아내에게로 돌아가지.\"" << std::endl;

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
	std::cout << GetNameOfEntity(pPlayer->ID()) << ":은행을 떠난다" << std::endl;
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
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":여관으로 들어간다" << std::endl;

		pPlayer->ChangeLocation(Location_Type::Inn);
	}
}

void GoInnAndSleepTillRested::Execute(Player* pPlayer)
{
	if (!pPlayer->Fatigued())
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":\"휴식을 취했다. 다시 파밍하러 가야겠군!\"" << std::endl;

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
	std::cout << GetNameOfEntity(pPlayer->ID()) << ":여관을 떠난다" << std::endl;
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
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":\"목이 마르군!\"" << std::endl;
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":길드로 들어간다" << std::endl;

		pPlayer->ChangeLocation(Location_Type::Guild);
	}
}

void QuenchThirst::Execute(Player* pPlayer)
{
	if (pPlayer->Thirsty())
	{
		pPlayer->VisitGuildAndDrink();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":술을 마신다." << std::endl;

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "\n현재 잔금: " << pPlayer->Wealth() << std::endl << std::endl;

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
	std::cout << GetNameOfEntity(pPlayer->ID()) << ":길드를 떠난다." << std::endl;
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
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":무기 상점으로 들어간다" << std::endl;

		pPlayer->ChangeLocation(Location_Type::Store);
	}
}

void FixWeaponAtStore::Execute(Player* pPlayer)
{
	if (pPlayer->ZeroDurability())
	{
		pPlayer->FixWeapon();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":\"무기 내구도가 없군!\"" << std::endl;
		std::cout << GetNameOfEntity(pPlayer->ID()) << ":무기를 수리한다." << std::endl;

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "\n현재 잔금: " << pPlayer->Wealth() << std::endl << std::endl;

		pPlayer->ChangeState(EnterDungeonAndFarming::Instance());
	}
}

void FixWeaponAtStore::Exit(Player* pPlayer)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pPlayer->ID()) << ":무기상점을 떠난다." << std::endl;
}