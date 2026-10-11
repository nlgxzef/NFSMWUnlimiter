#pragma once

#define _SkipFE 0x926064
#define _SkipFEPlayerCar 0x8F86A8

#define _HudResourceManager_mCustIndex 0x8F3C44

struct HudResourceManager
{
	enum HudResourceLoadStates : __int32
	{
		HRM_NOT_LOADED = 0x0,
		HRM_LOADING_IN_PROGRESS = 0x1,
		HRM_LOADED = 0x2,
		HRM_UNLOADING_IN_PROGRESS = 0x3,
	};

	DWORD* _vptr_HudResourceManager;
	HudResourceManager::HudResourceLoadStates mHudResourcesState;
	ResourceFile* pHudTextures;
	
};

struct RedlineEntry
{
	float redLimit;
	float normalRot;
	float dragRot;
};

// max < 7000
static const RedlineEntry tblMaxBelow7000[] =
{
	{ 5500.0f, 113.5f, 19.25f },
	{ 6000.0f, 131.5f, 26.0f  },
	{ 6500.0f, 149.5f, 32.25f },
	{ FLT_MAX, 164.5f, 39.25f }
};

// 7000 <= max < 8000
static const RedlineEntry tblMax7000to8000[] =
{
	{ 6000.0f, 110.0f, 17.25f },
	{ 6500.0f, 123.0f, 22.5f  },
	{ 7000.0f, 138.0f, 28.25f },
	{ 7500.0f, 152.0f, 34.0f  },
	{ FLT_MAX, 165.0f, 40.0f  }
};

// 8000 <= max < 9000
static const RedlineEntry tblMax8000to9000[] =
{
	{ 7000.0f, 115.0f, 22.0f  },
	{ 7500.0f, 127.0f, 27.0f  },
	{ 8000.0f, 140.5f, 32.25f },
	{ 8500.0f, 154.0f, 37.0f  },
	{ FLT_MAX, 166.0f, 42.0f  }
};

// max >= 9000
static const RedlineEntry tblMaxAbove9000[] =
{
	{ 8000.0f, 123.0f, 22.75f },
	{ 8500.0f, 134.0f, 27.0f  },
	{ 9000.0f, 145.0f, 31.5f  },
	{ 9500.0f, 156.0f, 37.0f  },
	{ FLT_MAX, 167.0f, 41.5f  }
};

float evalTable(const RedlineEntry* tbl, int count, float red, bool drag)
{
	for (int i = 0; i < count; ++i)
	{
		if (red < tbl[i].redLimit)
			return drag ? tbl[i].dragRot : tbl[i].normalRot;
	}
	return 0.0f; // unreachable
}

void HudResourceManager_ChooseLoadableTextures(ePlayerHudType hudType, int* textureHash, float* redlineRotation)
{
	DWORD VehicleKey;
	DWORD CurrentCar;
	Attrib_Instance pveh, engine;
	char buf[32];

	DWORD* FEDatabase = *(DWORD**)_FEDatabase;
	DWORD* UserProfile = (DWORD*)*((DWORD*)FEDatabase + 4);
	FEPlayerCarDB* stable = (FEPlayerCarDB*)*((DWORD*)UserProfile + 414);
	   // UserProfile->CareerSettings.CurrentCar

	if (*(bool*)_SkipFE)
	{
		VehicleKey = Attrib_StringToKey(*(char const**)_SkipFEPlayerCar);
	}
	else
	{
		DWORD* GRaceStatusfObj = *(DWORD**)GRaceStatus_fObj;
		if (GRaceStatusfObj && GRaceStatusfObj[1625] == 2)
		{
			CurrentCar = *((DWORD*)UserProfile + 0xA8 / 4);
		}
		else
		{
			RaceSettings* QRS = (RaceSettings*)cFrontendDatabase_GetQuickRaceSettings(FEDatabase, FEDatabase[5]);
			CurrentCar = QRS->SelectedCar[0];
		}

		VehicleKey = stable->GetCarRecordByHandle(CurrentCar)->VehicleKey;

		Attrib_Gen_pvehicle_pvehicle((DWORD*)&pveh, VehicleKey, 0, 0);
		Attrib_Collection *AttributePointer = (Attrib_Collection*)Attrib_Instance_GetAttributePointer((DWORD*)&pveh, 0xF1F5FBC7, 0);
		if (!AttributePointer) AttributePointer = (Attrib_Collection*)Attrib_DefaultDataArea(0xC);

		Attrib_Instance_ctInstance(&engine, AttributePointer, 0, 0);
		if (!engine.mLayoutPtr) engine.mLayoutPtr = Attrib_DefaultDataArea(0x60);

		Attrib_Gen_engine_LayoutStruct* eng = (Attrib_Gen_engine_LayoutStruct*)engine.mLayoutPtr;

		float max = eng->MAX_RPM;
		float red = eng->RED_LINE;

		float tex = FEngHud_ChooseMaxRpmTextureNumber(eng->MAX_RPM);

		if (hudType == PHT_DRAG)
			sprintf(buf, "DRAG_RPM_%d_LINES", (int)tex);
		else
		{
			sprintf(buf, "%d_LINES_%2.2d", (int)tex, *(int*)_HudResourceManager_mCustIndex);
		}

		*textureHash = bStringHash(buf);

		const bool drag = (hudType == PHT_DRAG);

		if (max < 7000.0f)
		{
			*redlineRotation = evalTable(
				tblMaxBelow7000,
				sizeof(tblMaxBelow7000) / sizeof(RedlineEntry),
				red,
				drag
			);
		}
		else if (max < 8000.0f)
		{
			*redlineRotation = evalTable(
				tblMax7000to8000,
				sizeof(tblMax7000to8000) / sizeof(RedlineEntry),
				red,
				drag
			);
		}
		else if (max < 9000.0f)
		{
			*redlineRotation = evalTable(
				tblMax8000to9000,
				sizeof(tblMax8000to9000) / sizeof(RedlineEntry),
				red,
				drag
			);
		}
		else
		{
			*redlineRotation = evalTable(
				tblMaxAbove9000,
				sizeof(tblMaxAbove9000) / sizeof(RedlineEntry),
				red,
				drag
			);
		}

		Attrib_Instance_dtInstance((DWORD*)&engine);
		Attrib_Instance_dtInstance((DWORD*)&pveh);
	}
}