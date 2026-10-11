#pragma once

enum eCustomizePartState : __int32
{
	CPS_AVAILABLE = 0x1,
	CPS_LOCKED = 0x2,
	CPS_NEW = 0x3,
	CPS_INSTALLED = 0x10,
	CPS_IN_CART = 0x20,
	CPS_GAME_STATE_MASK = 0xF,
	CPS_PLAYER_STATE_MASK = 0xF0,
};
