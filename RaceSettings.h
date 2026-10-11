#pragma once

struct RaceSettings
{
	unsigned int EventHash;
	unsigned __int8 NumLaps;
	unsigned __int8 TrackDirection;
	bool IsLapKO;
	unsigned __int8 NumOpponents;
	unsigned __int8 AISkill;
	unsigned __int8 CopDensity;
	unsigned __int8 TrafficDensity;
	bool CatchUp;
	bool CopsOn;
	unsigned __int8 RegionFilterBits;
	unsigned int SelectedCar[2];
};
