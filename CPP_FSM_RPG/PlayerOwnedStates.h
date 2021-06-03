#pragma once
#include "Player.h"


class EnterDungeonAndFarming : public State
{
private:
	EnterDungeonAndFarming() {}
	EnterDungeonAndFarming(const EnterDungeonAndFarming&);
	EnterDungeonAndFarming& operator=(const EnterDungeonAndFarming&);
public:
	static EnterDungeonAndFarming* Instance();

	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);
};

class VisitBankAndDepositGold : public State
{
private:
	VisitBankAndDepositGold() {}
	VisitBankAndDepositGold(const VisitBankAndDepositGold&);
	VisitBankAndDepositGold& operator=(const VisitBankAndDepositGold&);
public:
	static VisitBankAndDepositGold* Instance();

	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);
};

class GoInnAndSleepTillRested : public State
{
private:
	GoInnAndSleepTillRested() {}
	GoInnAndSleepTillRested(const GoInnAndSleepTillRested&);
	GoInnAndSleepTillRested& operator=(const GoInnAndSleepTillRested&);
public:
	static GoInnAndSleepTillRested* Instance();

	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);
};

class QuenchThirst : public State
{
private:
	QuenchThirst() {}
	QuenchThirst(const QuenchThirst&);
	QuenchThirst& operator=(const QuenchThirst&);
public:
	static QuenchThirst* Instance();

	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);
};

class FixWeaponAtStore : public State
{
private:
	FixWeaponAtStore() {}
	FixWeaponAtStore(const FixWeaponAtStore&);
	FixWeaponAtStore& operator=(const FixWeaponAtStore&);
public:
	static FixWeaponAtStore* Instance();

	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);
};