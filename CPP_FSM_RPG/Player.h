#pragma once
#include "BaseGameEntity.h"
#include "Locations.h"

#define MAX_GOLD            3
#define COMFORT_LEVEL       5
#define TIREDNESS_THRESHOLD 5
#define THIRST_LEVEL        5
#define WEAPON_DURABILITY   5

class Player;
class State
{
public:
	virtual ~State() {}

	virtual void Enter(Player*) abstract;
	virtual void Execute(Player*) abstract;
	virtual void Exit(Player*) abstract;
};

class Player : public BaseGameEntity
{
private:
	State* m_pCurrState;
	Location_Type m_Location;
	int m_nGoldCarried;
	int m_nMoneyInBank;
	int m_nThirst;
	int m_nFatigue;
	int m_nWeaponDurability;

public:
	Player(const int& id);
	virtual ~Player() {}

	void Update() override;
	void ChangeState(State*);

	Location_Type Location() const { return m_Location; }
	void ChangeLocation(const Location_Type& loc_type) { m_Location = loc_type; }

	int GoldCarried() const { return m_nGoldCarried; }
	void SetGoldCarried(const int& value) { m_nGoldCarried = value; }
	void AddToGoldCarried(const int&);
	bool PocketsFull() const { return (MAX_GOLD <= m_nGoldCarried); }

	bool Fatigued() const;
	void DecreaseFatigue() { m_nFatigue--; }
	void IncreaseFatigue() { m_nFatigue++; }

	int Wealth() const { return m_nMoneyInBank; }
	void SetWealth(const int& value) { m_nMoneyInBank = value; }
	void AddToWealth(const int&);

	bool Thirsty() const;
	void VisitGuildAndDrink() { m_nThirst = 0; m_nMoneyInBank -= 2; }
	void VisitGuildAndDrink(int i) { m_nThirst = 0; m_nGoldCarried -= 2; }
	void DrinkWater() { m_nThirst = 0; }

	int WeaponStatus() const { return m_nWeaponDurability; }
	void SetWeaponDurability(const int& value) { m_nWeaponDurability = value; }
	void DecreaseDruability() { m_nWeaponDurability--; }
	void FixWeapon() { m_nWeaponDurability = WEAPON_DURABILITY; m_nMoneyInBank -= 2; }
	void FixWeapon(int i) { m_nWeaponDurability = WEAPON_DURABILITY; m_nGoldCarried -= 2; }
	bool ZeroDurability() const;
};

