#pragma once

#include "Physics.h"

struct SelectablePart;
struct CarPart;

typedef void(__thiscall* SelectablePart_dtor_t)(SelectablePart* that, BYTE b);
SelectablePart_dtor_t SelectablePart_dtor = (SelectablePart_dtor_t)0x7A9F00;

struct SelectablePart : bTNode<SelectablePart>
{
	CarPart* ThePart;
	int CarSlotID;
	unsigned int UpgradeLevel;
	Physics_Upgrades_Type PhysicsType;
	bool PerformancePkg;
	eCustomizePartState PartState;
	int Price;
	bool JunkmanPart;

	virtual ~SelectablePart()
	{
		SelectablePart_dtor(this, 0);
	}
};