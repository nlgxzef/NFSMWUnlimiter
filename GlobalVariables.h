#pragma once

#define CarTypeInfoArray 0x9B09D8
#define SingleCarTypeInfoBlockSize 0xD0
#define SingleCarPartSize 0xE

#define NumFECarRecords 200
#define NumFECustomizationRecords 75
#define NumCarSlots 139
#define CarNameLength 32
#define PresetNameLength 32
#define PresetFileLength 0x290

#define _nullString 0x890978
#define _SaveFolderNameString 0x901748
#define _CustomizeParts_TexturePackLoaded 0x9B9EB0
#define _CarViewer_haveLoadedOnce 0x9B9E64
#define _gCarCustomizeManager 0x9B9EC0
#define _FECarRecord 0x9B9EC4
#define _PhysicsUpgrades 0x9B9EC8
#define _FEDatabase 0x91CF90
#define _CarPartDB 0x9B26A8
#define _MasterCarPartPack 0x9B09D4
#define _CarPartTypeNameHashTable 0x9B09C4
#define _CarPartPartsTable 0x9B09CC
#define _CarPartModelsTable 0x9B09D0
#define g_pCustomizeMainPkg 0x905EA4
#define g_pCustomizePartsPkg 0x905EB0
#define g_pCustomizePerfPkg 0x905EB4
#define g_pCustomizeDecalsPkg 0x905EB8
#define g_pCustomizeSubPkg 0x905EA8
#define g_pCustomizeSubTopPkg 0x905EAC
#define g_pCustomizeSpoilerPkg 0x905ECC
#define g_pCustomizeRimsPkg 0x905EC0
#define g_pCustomizeHudColorPkg 0x905EC8
#define g_pCustomizePaintPkg 0x905EBC
#define g_pCustomizeHudPkg 0x905EC4
#define g_pCustomizeShoppingCartPkg 0x905ED0
#define SelectablePart_vtable 0x8B7518
#define SetStockPartOption_vtable 0x8B7564
#define cFEng_mInstance 0x91CADC
#define GRaceStatus_fObj 0x91E000
#define gEasterEggs 0x8F8408
#define g_bTestCareerCustomization 0x9B9E8D
#define g_bCustomizeInBackRoom 0x91D3D0
#define CustomizeDecals_CurrentDecalLocation 0x905ED8
#define TheFEMarkerManager 0x91D928
#define _RealTimer 0x925B14
#define _RealTimeElapsedFrame 0x9259BC
#define _TheGameFlowManager 0x925E90
#define _FEGroup_vtbl 0x8A2E24
#define _CustomizePaintDatum_vtable 0x8B7580
#define _IsCollectorsEdition 0x8F8718
#define _UnlockAllThings 0x926124
#define _TweakKitWheelOffsetFront 0x9B0960
#define _TweakKitWheelOffsetRear 0x9B0964
#define _Showcase_FromArgs 0x9B9E80
#define _Showcase_FromIndex 0x9B9E84
#define _Showcase_FromFilter 0x905E38
#define _Showcase_FromColor 0x9B9E3C
#define _DrawCars 0x903320
#define _DrawLightFlares 0x8F2918
#define _FrontEndRenderingCarList 0x9B27EC
#define _EnableReleasePrintf 0x90E630
#define _MemoryCard_s_pThis 0x91CB20
#define _gTradeInFactor 0x89F71C
#define _CarSelectTireSteerAngle 0x905E20
#define _UsePrecompositeVinyls 0x9B09FC
#define _StreamingTexturePackLoader 0x91A098
#define _StreamingSolidPackLoader 0x91A060
#define _WheelPivotTranslationAmount 0x903314
#define _WheelStandardWidth 0x903318
#define _WheelStandardRadius 0x90331C
#define _gFastMem 0x925B30
#define _ForceHeadlightsOn 0x9B092C
#define _ForceBrakelightsOn 0x9B0930
#define _ForceReverselightsOn 0x9B0934
#define flt_8B2EE8 0x8B2EE8
#define _UTL_Collections_Singleton_INIS_mInstance 0x9885C8
#define _cpr 0x903528
#define _cpb 0x90352C
#define _cpw 0x903530
#define _copWhitemul 0x903540
#define _gTWEAKER_NISLightPosX 0x9B097C
#define _gTWEAKER_NISLightPosY 0x9B0980
#define _gTWEAKER_NISLightPosZ 0x9B0984
#define _gTWEAKER_NISLightEnabled 0x9B0978
#define _gTWEAKER_NISLightIntensity 0x903548
#define _ShaperLightsCharacters 0x8F2F10
#define _ShaperLightsCharactersBackup 0x8F2FB0
#define _Lightslot 0x90354C

bool BETACompatibility = 0;
bool HPCCompatibility = 0;

char AttachmentString[64];
char AttachmentDefaultString[64];
char CarTypeName[15];
char CarININame[MAX_PATH];
char RimBrandID[15];
char RimBrandString[64];
char RimBrandIcon[64];
char VinylBrandID[15];
char VinylBrandString[64];
char VinylBrandIcon[64];
char DecalMenuTexture[64];
char DecalMenuString[64];
char DecalMenuDefaultTexture[64];
char DecalMenuDefaultString[64];

int RenderFECarFlares = -1;

int RimsToCustomize = 1; // -1 = Rear, 0 = All, 1 = Front

bool InShowcase = 0;

// Default values for Rim Brands if _RimBrands.ini is N/A
#define DefaultRimBrandCount 10

char* DefaultRimBrandNames[]
{
	(char*)"",
	(char*)"5ZIGEN",
	(char*)"ADR",
	(char*)"BBS",
	(char*)"ENKEI",
	(char*)"KONIG",
	(char*)"LOWENHART",
	(char*)"RACINGHART",
	(char*)"OZ",
	(char*)"VOLK",
	(char*)"ROJA"
};

char* DefaultRimBrandStrings[]
{
	(char*)"CO_RIM_BRAND_CUSTOM",
	(char*)"CO_RIM_BRAND_5_ZIGEN",
	(char*)"CO_RIM_BRAND_ADR",
	(char*)"CO_RIM_BRAND_BBS",
	(char*)"CO_RIM_BRAND_ENKEI",
	(char*)"CO_RIM_BRAND_KONIG",
	(char*)"CO_RIM_BRAND_LOWENHART",
	(char*)"CO_RIM_BRAND_RACING_HART",
	(char*)"CO_RIM_BRAND_OZ",
	(char*)"CO_RIM_BRAND_VOLK",
	(char*)"CO_RIM_BRAND_ROJA"
};

char* DefaultRimBrandTextures[]
{
	(char*)"VISUAL_RIMS_BRAND_CUSTOM",
	(char*)"VISUAL_RIMS_BRAND_5ZIGEN",
	(char*)"VISUAL_RIMS_BRAND_ADR",
	(char*)"VISUAL_RIMS_BRAND_BBS",
	(char*)"VISUAL_RIMS_BRAND_ENKEI",
	(char*)"VISUAL_RIMS_BRAND_KONIG",
	(char*)"VISUAL_RIMS_BRAND_LOWENHEART",
	(char*)"VISUAL_RIMS_BRAND_RACINGHART",
	(char*)"VISUAL_RIMS_BRAND_OZ",
	(char*)"VISUAL_RIMS_BRAND_VOLK",
	(char*)"VISUAL_RIMS_BRAND_RAJA"
};

// Default values for Vinyl Groups if _VinylGroups.ini is N/A
#define DefaultVinylGroupCount 9

int DefaultVinylGroupIndexes[]
{
	31, 0, 1, 2, 3, 4, 5, 6, 7, 8
};

char* DefaultVinylGroupStrings[]
{
	(char*)"CO_VINYL_CUSTOM",
	(char*)"CO_VINYL_FLAME",
	(char*)"CO_VINYL_TRIBAL",
	(char*)"CO_VINYL_STRIPE",
	(char*)"CO_VINYL_RACE_FLAG",
	(char*)"CO_VINYL_NATIONAL_FLAG",
	(char*)"CO_VINYL_BODY",
	(char*)"CO_VINYL_UNIQUE",
	(char*)"CO_VINYL_CONTEST",
	(char*)"CO_VINYL_SPECIAL"
};

char* DefaultVinylGroupTextures[]
{
	(char*)"VINYL_GROUP_CUSTOM",
	(char*)"VINYL_GROUP_FLAMES",
	(char*)"VINYL_GROUP_TRIBAL",
	(char*)"VINYL_GROUP_STRIPES",
	(char*)"VINYL_GROUP_RACING_FLAG",
	(char*)"VINYL_GROUP_NATIONAL_FLAG",
	(char*)"VINYL_GROUP_BODY",
	(char*)"VINYL_GROUP_UNIQUE",
	(char*)"VINYL_GROUP_CONTEST",
	(char*)"VINYL_GROUP_SPECIAL"
};

bool DefaultVinylGroupAltCameras[]
{
	1, 0, 1, 1, 0, 1, 1, 1, 1, 1
};

// Default values for Vinyl Groups if _PaintGroups.ini is N/A
#define DefaultPaintBrandCount 5
#define MaximumPaintBrandCount 64

char* DefaultPaintBrandNames[]
{
	(char*)"",
	(char*)"GLOSS",
	(char*)"METAL",
	(char*)"PEARL",
	(char*)"TRAFFIC",
	(char*)"COP"
};

char* DefaultPaintBrandStrings[]
{
	(char*)"CP_FILTER_CUSTOM",
	(char*)"CP_FILTER_GLOSS",
	(char*)"CP_FILTER_METALLIC",
	(char*)"CP_FILTER_PEARL",
	(char*)"CP_FILTER_TRAFFIC",
	(char*)"CP_FILTER_COP"
};

// Default values for Vinyl Groups if _CopDestroyedStrings.ini is N/A
#define DefaultCopDestroyedStringCount 11

char* DefaultCopDestroyedStringPVehicles[]
{
	(char*)"",
	(char*)"copcross",
	(char*)"copsport",
	(char*)"copmidsize",
	(char*)"copghost",
	(char*)"copgto",
	(char*)"copgtoghost",
	(char*)"copsporthench",
	(char*)"copsportghost",
	(char*)"copsuv",
	(char*)"copsuvpatrol",
	(char*)"copsuvl"
};

char* DefaultCopDestroyedStrings[]
{
	(char*)"HUD_COPDESTROYED_DEFAULT",
	(char*)"HUD_COPDESTROYED_COPCROSS",
	(char*)"HUD_COPDESTROYED_COPCROSS",
	(char*)"HUD_COPDESTROYED_COPMIDSIZE",
	(char*)"HUD_COPDESTROYED_COPGHOST",
	(char*)"HUD_COPDESTROYED_COPGTO",
	(char*)"HUD_COPDESTROYED_COPGTOGHOST",
	(char*)"HUD_COPDESTROYED_COPSPORTHENCH",
	(char*)"HUD_COPDESTROYED_COPSPORTGHOST",
	(char*)"HUD_COPDESTROYED_COPSUV",
	(char*)"HUD_COPDESTROYED_COPSUV",
	(char*)"HUD_COPDESTROYED_COPSUVL"
};


// _General.ini & CARNAME.ini
typedef struct
{
	int InitiallyUnlocked;
	bool ForceLODA;
	int EngineType;
	bool ScaleBrakesWithRims;
	bool ListAttachmentsUnderParts;
} MainSection;
typedef struct
{
	bool HeadlightOff;
	bool DamageLights;
	bool CentreBrake;
	bool Reverse;
	bool BrakelightOnfInGame;
	bool TireInnerMask;
} TextureSection;
typedef struct
{
	bool Parts;
	bool Performance;
	bool Visual;
} CategorySection;
typedef struct
{
	bool BodyKits;
	bool Spoilers;
	bool Rims;
	bool RimsCustom;
	bool Hoods;
	bool RoofScoops;
	bool Interior;
	bool Roof;
	bool Brakes;
	bool Headlights;
	bool Taillights;
	bool Mirrors;
	int Attachments;
} PartsSection;
typedef struct
{
	bool Engine;
	bool Transmission;
	bool Chassis;
	bool Nitrous;
	bool Tires;
	bool Brakes;
	bool Induction;
} PerformanceSection;
typedef struct
{
	bool Paint;
	bool PaintCustom;
	bool Vinyls;
	bool VinylsCustom;
	bool RimPaint;
	bool WindowTint;
	bool Decals;
	bool DecalsWindshield;
	bool DecalsRearWindow;
	bool DecalsLeftDoor;
	bool DecalsRightDoor;
	bool DecalsLeftQuarter;
	bool DecalsRightQuarter;
	bool Numbers;
	bool CustomGauges;
	bool Driver;
	bool LicensePlate;
	bool Tires;
	bool Neon;
} VisualSection;
typedef struct
{
	DWORD Parts;
	DWORD PartsBodyKits;
	DWORD PartsSpoilers;
	DWORD PartsSpoilersCF;
	DWORD PartsRims;
	DWORD PartsRimsCustom;
	DWORD PartsHoods;
	DWORD PartsHoodsCF;
	DWORD PartsRoofScoops;
	DWORD PartsRoofScoopsCF;
	DWORD PartsInterior;
	DWORD PartsRoof;
	DWORD PartsBrakes;
	DWORD PartsHeadlights;
	DWORD PartsTaillights;
	DWORD PartsMirrors;
	DWORD PartsAttachments;
	DWORD PartsAttachment0;
	DWORD PartsAttachment1;
	DWORD PartsAttachment2;
	DWORD PartsAttachment3;
	DWORD PartsAttachment4;
	DWORD PartsAttachment5;
	DWORD PartsAttachment6;
	DWORD PartsAttachment7;
	DWORD PartsAttachment8;
	DWORD PartsAttachment9;
	DWORD Performance;
	DWORD PerformanceEngine;
	DWORD PerformanceTransmission;
	DWORD PerformanceChassis;
	DWORD PerformanceNitrous;
	DWORD PerformanceTires;
	DWORD PerformanceBrakes;
	DWORD PerformanceTurbo;
	DWORD PerformanceSupercharger;
	DWORD Visual;
	DWORD VisualPaint;
	DWORD VisualVinyls;
	DWORD VisualVinylsCustom;
	DWORD VisualRimPaint;
	DWORD VisualWindowTint;
	DWORD VisualDecals;
	DWORD VisualDecalsWindshield;
	DWORD VisualDecalsWindshield1;
	DWORD VisualDecalsWindshield2;
	DWORD VisualDecalsWindshield3;
	DWORD VisualDecalsWindshield4;
	DWORD VisualDecalsWindshield5;
	DWORD VisualDecalsWindshield6;
	DWORD VisualDecalsWindshield7;
	DWORD VisualDecalsWindshield8;
	DWORD VisualDecalsRearWindow;
	DWORD VisualDecalsRearWindow1;
	DWORD VisualDecalsRearWindow2;
	DWORD VisualDecalsRearWindow3;
	DWORD VisualDecalsRearWindow4;
	DWORD VisualDecalsRearWindow5;
	DWORD VisualDecalsRearWindow6;
	DWORD VisualDecalsRearWindow7;
	DWORD VisualDecalsRearWindow8;
	DWORD VisualDecalsLeftDoor;
	DWORD VisualDecalsLeftDoor1;
	DWORD VisualDecalsLeftDoor2;
	DWORD VisualDecalsLeftDoor3;
	DWORD VisualDecalsLeftDoor4;
	DWORD VisualDecalsLeftDoor5;
	DWORD VisualDecalsLeftDoor6;
	DWORD VisualDecalsRightDoor;
	DWORD VisualDecalsRightDoor1;
	DWORD VisualDecalsRightDoor2;
	DWORD VisualDecalsRightDoor3;
	DWORD VisualDecalsRightDoor4;
	DWORD VisualDecalsRightDoor5;
	DWORD VisualDecalsRightDoor6;
	DWORD VisualDecalsLeftQuarter;
	DWORD VisualDecalsLeftQuarter1;
	DWORD VisualDecalsLeftQuarter2;
	DWORD VisualDecalsLeftQuarter3;
	DWORD VisualDecalsLeftQuarter4;
	DWORD VisualDecalsLeftQuarter5;
	DWORD VisualDecalsLeftQuarter6;
	DWORD VisualDecalsLeftQuarter7;
	DWORD VisualDecalsLeftQuarter8;
	DWORD VisualDecalsRightQuarter;
	DWORD VisualDecalsRightQuarter1;
	DWORD VisualDecalsRightQuarter2;
	DWORD VisualDecalsRightQuarter3;
	DWORD VisualDecalsRightQuarter4;
	DWORD VisualDecalsRightQuarter5;
	DWORD VisualDecalsRightQuarter6;
	DWORD VisualDecalsRightQuarter7;
	DWORD VisualDecalsRightQuarter8;
	DWORD VisualNumbers;
	DWORD VisualCustomGauges;
	DWORD VisualDriver;
	DWORD VisualLicensePlate;
	DWORD VisualTires;
	DWORD VisualNeon;
	DWORD BackroomParts;
	DWORD BackroomPartsBodyKits;
	DWORD BackroomPartsSpoilers;
	DWORD BackroomPartsSpoilersCF;
	DWORD BackroomPartsRims;
	DWORD BackroomPartsHoods;
	DWORD BackroomPartsHoodsCF;
	DWORD BackroomPartsRoofScoops;
	DWORD BackroomPartsRoofScoopsCF;
	DWORD BackroomPerformance;
	DWORD BackroomPerformanceEngine;
	DWORD BackroomPerformanceTransmission;
	DWORD BackroomPerformanceChassis;
	DWORD BackroomPerformanceNitrous;
	DWORD BackroomPerformanceTires;
	DWORD BackroomPerformanceBrakes;
	DWORD BackroomPerformanceTurbo;
	DWORD BackroomPerformanceSupercharger;
	DWORD BackroomVisual;
	DWORD BackroomVisualPaint;
	DWORD BackroomVisualVinyls;
	DWORD BackroomVisualDecals;
	DWORD BackroomVisualCustomGauges;
	DWORD PerformanceEngineStock;
	DWORD PerformanceEngineStreet;
	DWORD PerformanceEngineSuperStreet;
	DWORD PerformanceEngineRace;
	DWORD PerformanceEnginePro;
	DWORD PerformanceEngineSuperPro;
	DWORD PerformanceEngineUltimate;
	DWORD PerformanceEngineJunkman;
	DWORD PerformanceTransmissionStock;
	DWORD PerformanceTransmissionStreet;
	DWORD PerformanceTransmissionSuperStreet;
	DWORD PerformanceTransmissionRace;
	DWORD PerformanceTransmissionPro;
	DWORD PerformanceTransmissionSuperPro;
	DWORD PerformanceTransmissionUltimate;
	DWORD PerformanceTransmissionJunkman;
	DWORD PerformanceChassisStock;
	DWORD PerformanceChassisStreet;
	DWORD PerformanceChassisSuperStreet;
	DWORD PerformanceChassisRace;
	DWORD PerformanceChassisPro;
	DWORD PerformanceChassisSuperPro;
	DWORD PerformanceChassisUltimate;
	DWORD PerformanceChassisJunkman;
	DWORD PerformanceNitrousStock;
	DWORD PerformanceNitrousStreet;
	DWORD PerformanceNitrousSuperStreet;
	DWORD PerformanceNitrousRace;
	DWORD PerformanceNitrousPro;
	DWORD PerformanceNitrousSuperPro;
	DWORD PerformanceNitrousUltimate;
	DWORD PerformanceNitrousJunkman;
	DWORD PerformanceTiresStock;
	DWORD PerformanceTiresStreet;
	DWORD PerformanceTiresSuperStreet;
	DWORD PerformanceTiresRace;
	DWORD PerformanceTiresPro;
	DWORD PerformanceTiresSuperPro;
	DWORD PerformanceTiresUltimate;
	DWORD PerformanceTiresJunkman;
	DWORD PerformanceBrakesStock;
	DWORD PerformanceBrakesStreet;
	DWORD PerformanceBrakesSuperStreet;
	DWORD PerformanceBrakesRace;
	DWORD PerformanceBrakesPro;
	DWORD PerformanceBrakesSuperPro;
	DWORD PerformanceBrakesUltimate;
	DWORD PerformanceBrakesJunkman;
	DWORD PerformanceTurboStock;
	DWORD PerformanceTurboStreet;
	DWORD PerformanceTurboSuperStreet;
	DWORD PerformanceTurboRace;
	DWORD PerformanceTurboPro;
	DWORD PerformanceTurboSuperPro;
	DWORD PerformanceTurboUltimate;
	DWORD PerformanceTurboJunkman;
	DWORD PerformanceSuperchargerStock;
	DWORD PerformanceSuperchargerStreet;
	DWORD PerformanceSuperchargerSuperStreet;
	DWORD PerformanceSuperchargerRace;
	DWORD PerformanceSuperchargerPro;
	DWORD PerformanceSuperchargerSuperPro;
	DWORD PerformanceSuperchargerUltimate;
	DWORD PerformanceSuperchargerJunkman;
	DWORD PerformanceEngineLevel1Item1;
	DWORD PerformanceEngineLevel1Item2;
	DWORD PerformanceEngineLevel1Item3;
	DWORD PerformanceEngineLevel2Item1;
	DWORD PerformanceEngineLevel2Item2;
	DWORD PerformanceEngineLevel2Item3;
	DWORD PerformanceEngineLevel3Item1;
	DWORD PerformanceEngineLevel3Item2;
	DWORD PerformanceEngineLevel3Item3;
	DWORD PerformanceEngineLevel4Item1;
	DWORD PerformanceEngineLevel4Item2;
	DWORD PerformanceEngineLevel4Item3;
	DWORD PerformanceEngineLevel2Item1Rotary;
	DWORD PerformanceEngineLevel4Item1Rotary;
	DWORD PerformanceEngineLevel4Item3Castrol;
	DWORD PerformanceEngineJunkmanItem;
	DWORD PerformanceTransmissionLevel1Item1;
	DWORD PerformanceTransmissionLevel1Item2;
	DWORD PerformanceTransmissionLevel1Item3;
	DWORD PerformanceTransmissionLevel2Item1;
	DWORD PerformanceTransmissionLevel2Item2;
	DWORD PerformanceTransmissionLevel2Item3;
	DWORD PerformanceTransmissionLevel3Item1;
	DWORD PerformanceTransmissionLevel3Item2;
	DWORD PerformanceTransmissionLevel3Item3;
	DWORD PerformanceTransmissionLevel4Item1;
	DWORD PerformanceTransmissionLevel4Item2;
	DWORD PerformanceTransmissionLevel4Item3;
	DWORD PerformanceTransmissionJunkmanItem;
	DWORD PerformanceChassisLevel1Item1;
	DWORD PerformanceChassisLevel1Item2;
	DWORD PerformanceChassisLevel1Item3;
	DWORD PerformanceChassisLevel2Item1;
	DWORD PerformanceChassisLevel2Item2;
	DWORD PerformanceChassisLevel2Item3;
	DWORD PerformanceChassisLevel3Item1;
	DWORD PerformanceChassisLevel3Item2;
	DWORD PerformanceChassisLevel3Item3;
	DWORD PerformanceChassisJunkmanItem;
	DWORD PerformanceNitrousLevel1Item1;
	DWORD PerformanceNitrousLevel1Item2;
	DWORD PerformanceNitrousLevel1Item3;
	DWORD PerformanceNitrousLevel2Item1;
	DWORD PerformanceNitrousLevel2Item2;
	DWORD PerformanceNitrousLevel2Item3;
	DWORD PerformanceNitrousLevel3Item1;
	DWORD PerformanceNitrousLevel3Item2;
	DWORD PerformanceNitrousLevel3Item3;
	DWORD PerformanceNitrousJunkmanItem;
	DWORD PerformanceTiresLevel1Item1;
	DWORD PerformanceTiresLevel1Item2;
	DWORD PerformanceTiresLevel1Item3;
	DWORD PerformanceTiresLevel2Item1;
	DWORD PerformanceTiresLevel2Item2;
	DWORD PerformanceTiresLevel2Item3;
	DWORD PerformanceTiresLevel3Item1;
	DWORD PerformanceTiresLevel3Item2;
	DWORD PerformanceTiresLevel3Item3;
	DWORD PerformanceTiresJunkmanItem;
	DWORD PerformanceBrakesLevel1Item1;
	DWORD PerformanceBrakesLevel1Item2;
	DWORD PerformanceBrakesLevel1Item3;
	DWORD PerformanceBrakesLevel2Item1;
	DWORD PerformanceBrakesLevel2Item2;
	DWORD PerformanceBrakesLevel2Item3;
	DWORD PerformanceBrakesLevel3Item1;
	DWORD PerformanceBrakesLevel3Item2;
	DWORD PerformanceBrakesLevel3Item3;
	DWORD PerformanceBrakesLevel4Item1;
	DWORD PerformanceBrakesLevel4Item2;
	DWORD PerformanceBrakesLevel4Item3;
	DWORD PerformanceBrakesJunkmanItem;
	DWORD PerformanceTurboLevel1Item1;
	DWORD PerformanceTurboLevel1Item2;
	DWORD PerformanceTurboLevel1Item3;
	DWORD PerformanceTurboLevel2Item1;
	DWORD PerformanceTurboLevel2Item2;
	DWORD PerformanceTurboLevel2Item3;
	DWORD PerformanceTurboLevel3Item1;
	DWORD PerformanceTurboLevel3Item2;
	DWORD PerformanceTurboLevel3Item3;
	DWORD PerformanceTurboJunkmanItem;
	DWORD PerformanceSuperchargerLevel1Item1;
	DWORD PerformanceSuperchargerLevel1Item2;
	DWORD PerformanceSuperchargerLevel1Item3;
	DWORD PerformanceSuperchargerLevel2Item1;
	DWORD PerformanceSuperchargerLevel2Item2;
	DWORD PerformanceSuperchargerLevel2Item3;
	DWORD PerformanceSuperchargerLevel3Item1;
	DWORD PerformanceSuperchargerLevel3Item2;
	DWORD PerformanceSuperchargerLevel3Item3;
	DWORD PerformanceSuperchargerJunkmanItem;
} IconsSection;
typedef struct
{
	DWORD Parts;
	DWORD PartsBodyKits;
	DWORD PartsSpoilers;
	DWORD PartsRims;
	DWORD PartsRimsBrand;
	DWORD PartsRimsCustom;
	DWORD PartsHoods;
	DWORD PartsRoofScoops;
	DWORD PartsInterior;
	DWORD PartsRoof;
	DWORD PartsBrakes;
	DWORD PartsHeadlights;
	DWORD PartsTaillights;
	DWORD PartsMirrors;
	DWORD PartsAttachments;
	DWORD PartsAttachment0;
	DWORD PartsAttachment1;
	DWORD PartsAttachment2;
	DWORD PartsAttachment3;
	DWORD PartsAttachment4;
	DWORD PartsAttachment5;
	DWORD PartsAttachment6;
	DWORD PartsAttachment7;
	DWORD PartsAttachment8;
	DWORD PartsAttachment9;
	DWORD Performance;
	DWORD PerformanceEngine;
	DWORD PerformanceTransmission;
	DWORD PerformanceChassis;
	DWORD PerformanceNitrous;
	DWORD PerformanceTires;
	DWORD PerformanceBrakes;
	DWORD PerformanceTurbo;
	DWORD PerformanceSupercharger;
	DWORD Visual;
	DWORD VisualPaint;
	DWORD VisualPaintCustom;
	DWORD VisualVinyls;
	DWORD VisualVinylsCustom;
	DWORD VisualVinylsGroup;
	DWORD VisualVinylsColor;
	DWORD VisualRimPaint;
	DWORD VisualWindowTint;
	DWORD VisualDecals;
	DWORD VisualDecalsPosition;
	DWORD VisualDecalsLocation;
	DWORD VisualDecalsWindshield;
	DWORD VisualDecalsWindshield1;
	DWORD VisualDecalsWindshield2;
	DWORD VisualDecalsWindshield3;
	DWORD VisualDecalsWindshield4;
	DWORD VisualDecalsWindshield5;
	DWORD VisualDecalsWindshield6;
	DWORD VisualDecalsWindshield7;
	DWORD VisualDecalsWindshield8;
	DWORD VisualDecalsRearWindow;
	DWORD VisualDecalsRearWindow1;
	DWORD VisualDecalsRearWindow2;
	DWORD VisualDecalsRearWindow3;
	DWORD VisualDecalsRearWindow4;
	DWORD VisualDecalsRearWindow5;
	DWORD VisualDecalsRearWindow6;
	DWORD VisualDecalsRearWindow7;
	DWORD VisualDecalsRearWindow8;
	DWORD VisualDecalsLeftDoor;
	DWORD VisualDecalsLeftDoor1;
	DWORD VisualDecalsLeftDoor2;
	DWORD VisualDecalsLeftDoor3;
	DWORD VisualDecalsLeftDoor4;
	DWORD VisualDecalsLeftDoor5;
	DWORD VisualDecalsLeftDoor6;
	DWORD VisualDecalsRightDoor;
	DWORD VisualDecalsRightDoor1;
	DWORD VisualDecalsRightDoor2;
	DWORD VisualDecalsRightDoor3;
	DWORD VisualDecalsRightDoor4;
	DWORD VisualDecalsRightDoor5;
	DWORD VisualDecalsRightDoor6;
	DWORD VisualDecalsLeftQuarter;
	DWORD VisualDecalsLeftQuarter1;
	DWORD VisualDecalsLeftQuarter2;
	DWORD VisualDecalsLeftQuarter3;
	DWORD VisualDecalsLeftQuarter4;
	DWORD VisualDecalsLeftQuarter5;
	DWORD VisualDecalsLeftQuarter6;
	DWORD VisualDecalsLeftQuarter7;
	DWORD VisualDecalsLeftQuarter8;
	DWORD VisualDecalsRightQuarter;
	DWORD VisualDecalsRightQuarter1;
	DWORD VisualDecalsRightQuarter2;
	DWORD VisualDecalsRightQuarter3;
	DWORD VisualDecalsRightQuarter4;
	DWORD VisualDecalsRightQuarter5;
	DWORD VisualDecalsRightQuarter6;
	DWORD VisualDecalsRightQuarter7;
	DWORD VisualDecalsRightQuarter8;
	DWORD VisualNumbers;
	DWORD VisualCustomGauges;
	DWORD VisualDriver;
	DWORD VisualLicensePlate;
	DWORD VisualTires;
	DWORD VisualNeon;
	DWORD BackroomParts;
	DWORD BackroomPerformance;
	DWORD BackroomVisual;
	DWORD PerformanceEngineStock;
	DWORD PerformanceEngineStreet;
	DWORD PerformanceEngineSuperStreet;
	DWORD PerformanceEngineRace;
	DWORD PerformanceEnginePro;
	DWORD PerformanceEngineSuperPro;
	DWORD PerformanceEngineUltimate;
	DWORD PerformanceEngineJunkman;
	DWORD PerformanceTransmissionStock;
	DWORD PerformanceTransmissionStreet;
	DWORD PerformanceTransmissionSuperStreet;
	DWORD PerformanceTransmissionRace;
	DWORD PerformanceTransmissionPro;
	DWORD PerformanceTransmissionSuperPro;
	DWORD PerformanceTransmissionUltimate;
	DWORD PerformanceTransmissionJunkman;
	DWORD PerformanceChassisStock;
	DWORD PerformanceChassisStreet;
	DWORD PerformanceChassisSuperStreet;
	DWORD PerformanceChassisRace;
	DWORD PerformanceChassisPro;
	DWORD PerformanceChassisSuperPro;
	DWORD PerformanceChassisUltimate;
	DWORD PerformanceChassisJunkman;
	DWORD PerformanceNitrousStock;
	DWORD PerformanceNitrousStreet;
	DWORD PerformanceNitrousSuperStreet;
	DWORD PerformanceNitrousRace;
	DWORD PerformanceNitrousPro;
	DWORD PerformanceNitrousSuperPro;
	DWORD PerformanceNitrousUltimate;
	DWORD PerformanceNitrousJunkman;
	DWORD PerformanceTiresStock;
	DWORD PerformanceTiresStreet;
	DWORD PerformanceTiresSuperStreet;
	DWORD PerformanceTiresRace;
	DWORD PerformanceTiresPro;
	DWORD PerformanceTiresSuperPro;
	DWORD PerformanceTiresUltimate;
	DWORD PerformanceTiresJunkman;
	DWORD PerformanceBrakesStock;
	DWORD PerformanceBrakesStreet;
	DWORD PerformanceBrakesSuperStreet;
	DWORD PerformanceBrakesRace;
	DWORD PerformanceBrakesPro;
	DWORD PerformanceBrakesSuperPro;
	DWORD PerformanceBrakesUltimate;
	DWORD PerformanceBrakesJunkman;
	DWORD PerformanceTurboStock;
	DWORD PerformanceTurboStreet;
	DWORD PerformanceTurboSuperStreet;
	DWORD PerformanceTurboRace;
	DWORD PerformanceTurboPro;
	DWORD PerformanceTurboSuperPro;
	DWORD PerformanceTurboUltimate;
	DWORD PerformanceTurboJunkman;
	DWORD PerformanceSuperchargerStock;
	DWORD PerformanceSuperchargerStreet;
	DWORD PerformanceSuperchargerSuperStreet;
	DWORD PerformanceSuperchargerRace;
	DWORD PerformanceSuperchargerPro;
	DWORD PerformanceSuperchargerSuperPro;
	DWORD PerformanceSuperchargerUltimate;
	DWORD PerformanceSuperchargerJunkman;
	DWORD PerformanceEngineLevel1Item1;
	DWORD PerformanceEngineLevel1Item2;
	DWORD PerformanceEngineLevel1Item3;
	DWORD PerformanceEngineLevel2Item1;
	DWORD PerformanceEngineLevel2Item2;
	DWORD PerformanceEngineLevel2Item3;
	DWORD PerformanceEngineLevel3Item1;
	DWORD PerformanceEngineLevel3Item2;
	DWORD PerformanceEngineLevel3Item3;
	DWORD PerformanceEngineLevel4Item1;
	DWORD PerformanceEngineLevel4Item2;
	DWORD PerformanceEngineLevel4Item3;
	DWORD PerformanceEngineLevel2Item1Rotary;
	DWORD PerformanceEngineLevel4Item1Rotary;
	DWORD PerformanceEngineLevel4Item3Castrol;
	DWORD PerformanceEngineJunkmanItem;
	DWORD PerformanceTransmissionLevel1Item1;
	DWORD PerformanceTransmissionLevel1Item2;
	DWORD PerformanceTransmissionLevel1Item3;
	DWORD PerformanceTransmissionLevel2Item1;
	DWORD PerformanceTransmissionLevel2Item2;
	DWORD PerformanceTransmissionLevel2Item3;
	DWORD PerformanceTransmissionLevel3Item1;
	DWORD PerformanceTransmissionLevel3Item2;
	DWORD PerformanceTransmissionLevel3Item3;
	DWORD PerformanceTransmissionLevel4Item1;
	DWORD PerformanceTransmissionLevel4Item2;
	DWORD PerformanceTransmissionLevel4Item3;
	DWORD PerformanceTransmissionJunkmanItem;
	DWORD PerformanceChassisLevel1Item1;
	DWORD PerformanceChassisLevel1Item2;
	DWORD PerformanceChassisLevel1Item3;
	DWORD PerformanceChassisLevel2Item1;
	DWORD PerformanceChassisLevel2Item2;
	DWORD PerformanceChassisLevel2Item3;
	DWORD PerformanceChassisLevel3Item1;
	DWORD PerformanceChassisLevel3Item2;
	DWORD PerformanceChassisLevel3Item3;
	DWORD PerformanceChassisJunkmanItem;
	DWORD PerformanceNitrousLevel1Item1;
	DWORD PerformanceNitrousLevel1Item2;
	DWORD PerformanceNitrousLevel1Item3;
	DWORD PerformanceNitrousLevel2Item1;
	DWORD PerformanceNitrousLevel2Item2;
	DWORD PerformanceNitrousLevel2Item3;
	DWORD PerformanceNitrousLevel3Item1;
	DWORD PerformanceNitrousLevel3Item2;
	DWORD PerformanceNitrousLevel3Item3;
	DWORD PerformanceNitrousJunkmanItem;
	DWORD PerformanceTiresLevel1Item1;
	DWORD PerformanceTiresLevel1Item2;
	DWORD PerformanceTiresLevel1Item3;
	DWORD PerformanceTiresLevel2Item1;
	DWORD PerformanceTiresLevel2Item2;
	DWORD PerformanceTiresLevel2Item3;
	DWORD PerformanceTiresLevel3Item1;
	DWORD PerformanceTiresLevel3Item2;
	DWORD PerformanceTiresLevel3Item3;
	DWORD PerformanceTiresJunkmanItem;
	DWORD PerformanceBrakesLevel1Item1;
	DWORD PerformanceBrakesLevel1Item2;
	DWORD PerformanceBrakesLevel1Item3;
	DWORD PerformanceBrakesLevel2Item1;
	DWORD PerformanceBrakesLevel2Item2;
	DWORD PerformanceBrakesLevel2Item3;
	DWORD PerformanceBrakesLevel3Item1;
	DWORD PerformanceBrakesLevel3Item2;
	DWORD PerformanceBrakesLevel3Item3;
	DWORD PerformanceBrakesLevel4Item1;
	DWORD PerformanceBrakesLevel4Item2;
	DWORD PerformanceBrakesLevel4Item3;
	DWORD PerformanceBrakesJunkmanItem;
	DWORD PerformanceTurboLevel1Item1;
	DWORD PerformanceTurboLevel1Item2;
	DWORD PerformanceTurboLevel1Item3;
	DWORD PerformanceTurboLevel2Item1;
	DWORD PerformanceTurboLevel2Item2;
	DWORD PerformanceTurboLevel2Item3;
	DWORD PerformanceTurboLevel3Item1;
	DWORD PerformanceTurboLevel3Item2;
	DWORD PerformanceTurboLevel3Item3;
	DWORD PerformanceTurboJunkmanItem;
	DWORD PerformanceSuperchargerLevel1Item1;
	DWORD PerformanceSuperchargerLevel1Item2;
	DWORD PerformanceSuperchargerLevel1Item3;
	DWORD PerformanceSuperchargerLevel2Item1;
	DWORD PerformanceSuperchargerLevel2Item2;
	DWORD PerformanceSuperchargerLevel2Item3;
	DWORD PerformanceSuperchargerLevel3Item1;
	DWORD PerformanceSuperchargerLevel3Item2;
	DWORD PerformanceSuperchargerLevel3Item3;
	DWORD PerformanceSuperchargerJunkmanItem;
} NamesSection;
typedef struct
{
	DWORD PartsBodyKits;
	DWORD PartsSpoilers;
	DWORD PartsRims;
	DWORD PartsRimsBrand;
	DWORD PartsRimsBrandRear;
	DWORD PartsRimsBrandAll;
	DWORD PartsHoods;
	DWORD PartsRoofScoops;
	DWORD PartsInterior;
	DWORD PartsRoof;
	DWORD PartsBrakes;
	DWORD PartsHeadlights;
	DWORD PartsTaillights;
	DWORD PartsMirrors;
	DWORD PartsAttachments;
	DWORD PartsAttachment0;
	DWORD PartsAttachment1;
	DWORD PartsAttachment2;
	DWORD PartsAttachment3;
	DWORD PartsAttachment4;
	DWORD PartsAttachment5;
	DWORD PartsAttachment6;
	DWORD PartsAttachment7;
	DWORD PartsAttachment8;
	DWORD PartsAttachment9;
	DWORD VisualPaint;
	DWORD VisualVinyls;
	DWORD VisualVinylsGroup;
	DWORD VisualRimPaint;
	DWORD VisualWindowTint;
	DWORD VisualDecals;
	DWORD VisualDecalsWindshield;
	DWORD VisualDecalsWindshield1;
	DWORD VisualDecalsWindshield2;
	DWORD VisualDecalsWindshield3;
	DWORD VisualDecalsWindshield4;
	DWORD VisualDecalsWindshield5;
	DWORD VisualDecalsWindshield6;
	DWORD VisualDecalsWindshield7;
	DWORD VisualDecalsWindshield8;
	DWORD VisualDecalsRearWindow;
	DWORD VisualDecalsRearWindow1;
	DWORD VisualDecalsRearWindow2;
	DWORD VisualDecalsRearWindow3;
	DWORD VisualDecalsRearWindow4;
	DWORD VisualDecalsRearWindow5;
	DWORD VisualDecalsRearWindow6;
	DWORD VisualDecalsRearWindow7;
	DWORD VisualDecalsRearWindow8;
	DWORD VisualDecalsLeftDoor;
	DWORD VisualDecalsLeftDoor1;
	DWORD VisualDecalsLeftDoor2;
	DWORD VisualDecalsLeftDoor3;
	DWORD VisualDecalsLeftDoor4;
	DWORD VisualDecalsLeftDoor5;
	DWORD VisualDecalsLeftDoor6;
	DWORD VisualDecalsRightDoor;
	DWORD VisualDecalsRightDoor1;
	DWORD VisualDecalsRightDoor2;
	DWORD VisualDecalsRightDoor3;
	DWORD VisualDecalsRightDoor4;
	DWORD VisualDecalsRightDoor5;
	DWORD VisualDecalsRightDoor6;
	DWORD VisualDecalsLeftQuarter;
	DWORD VisualDecalsLeftQuarter1;
	DWORD VisualDecalsLeftQuarter2;
	DWORD VisualDecalsLeftQuarter3;
	DWORD VisualDecalsLeftQuarter4;
	DWORD VisualDecalsLeftQuarter5;
	DWORD VisualDecalsLeftQuarter6;
	DWORD VisualDecalsLeftQuarter7;
	DWORD VisualDecalsLeftQuarter8;
	DWORD VisualDecalsRightQuarter;
	DWORD VisualDecalsRightQuarter1;
	DWORD VisualDecalsRightQuarter2;
	DWORD VisualDecalsRightQuarter3;
	DWORD VisualDecalsRightQuarter4;
	DWORD VisualDecalsRightQuarter5;
	DWORD VisualDecalsRightQuarter6;
	DWORD VisualDecalsRightQuarter7;
	DWORD VisualDecalsRightQuarter8;
	DWORD VisualNumbers;
	DWORD VisualCustomGauges;
	DWORD VisualDriver;
	DWORD VisualLicensePlate;
	DWORD VisualTires;
	DWORD VisualNeon;
} CamerasSection;

typedef struct
{
	bool CustomStockParts;
	DWORD Parts[NumCarSlots];
} StockPartsSection;
typedef struct
{
	int ForceCustomizationLevel;
	bool CustomRandomParts;
	bool RandomizeInTraffic;
	bool Parts[NumCarSlots];
} RandomPartsSection;
typedef struct
{
	float BodyKits;
	float Spoilers;
	float Rims;
	float Hoods;
	float RoofScoops;
	float Interior;
	float Roof;
	float Brakes;
	float Headlights;
	float Taillights;
	float Mirrors;
	float Attachment0;
	float Attachment1;
	float Attachment2;
	float Attachment3;
	float Attachment4;
	float Attachment5;
	float Attachment6;
	float Attachment7;
	float Attachment8;
	float Attachment9;
	float Paint;
	float Vinyls;
	float RimPaint;
	float WindowTint;
	float Decals;
	float Driver;
	float LicensePlate;
	float Tires;
	float Neon;
} FECoolingSection;

typedef struct
{
	DWORD* CarTypeInfo;
	MainSection Main;
	TextureSection Textures;
	CategorySection Category;
	PartsSection Parts;
	PerformanceSection Performance;
	VisualSection Visual;
	IconsSection Icons;
	NamesSection Names;
	CamerasSection Cameras;
	StockPartsSection StockParts;
	RandomPartsSection RandomParts;
	FECoolingSection FECooling;
} CarConfig;

CarConfig DefaultCarConfig;
std::vector<CarConfig> CarConfigs;

// _FNGFixes.ini
typedef struct
{
	char Prefix[64];
} Child;

typedef struct
{
	char FNGName[64];
	char ObjectPrefix[64];
	int NumberOfObjects;
	std::vector<Child> Children;
} FNGFix;

std::vector<FNGFix> FNGFixes;

// _CopDestroyedStrings.ini
typedef struct
{
	DWORD PVehicle;
	DWORD StringHash;
} CopDestroyedString;

std::vector<CopDestroyedString> CopDestroyedStrings;

// _BonusCars.ini
typedef struct
{
	char PresetName[32];
	DWORD CarRecordID;
	DWORD Category;
	bool CEOnly;
	int UnlockConditionType;
	int Blacklist;
	DWORD UnlockConditionStringHash;
} BonusCar;

BonusCar DefaultBonusCar;
std::vector<BonusCar> BonusCars;

// _RimBrands.ini
typedef struct
{
	DWORD BrandNameHash;
	DWORD StringHash;
	DWORD TextureHash;
	bool NoRimSize;
} RimBrand;

std::vector<RimBrand> RimBrands;

// _VinylGroups.ini
typedef struct
{
	int Index;
	DWORD StringHash;
	DWORD TextureHash;
	bool UseAltCamera;
} VinylGroup;

std::vector<VinylGroup> VinylGroups;

// _PaintGroups.ini
typedef struct
{
	DWORD BrandNameHash;
	DWORD StringHash;
} PaintGroup;

std::vector<PaintGroup> PaintGroups;

DWORD *Showcase_FromColor[MaximumPaintBrandCount]; // 0x9B9E3C (only has 3 spaces)
DWORD SelectedPaints[MaximumPaintBrandCount]; // CustomizePaint[112]
DWORD* SelectedPaintParts[MaximumPaintBrandCount]; // CustomizePaint[181]

float CarSelectTireSteerAngle_Backup;

std::filesystem::path CurrentWorkingDirectory;

DWORD ColorHashes[3][4] = {
	{0x0000D99A, 0x02DDC8F0, 0x00136707, 0x026E1AC5}, // RED, GREEN, BLUE, ALPHA
	{0x001C0D0C, 0x5E96E722, 0x02804819, 0x50317397}, // RED2, GREEN2, BLUE2, ALPHA2
	{0x368A1A6A, 0x00BA7DC0, 0x07C4C1D7, 0x004ACF95} // DISPRED, DISPGREEN, DISPBLUE, DISPALPHA
};