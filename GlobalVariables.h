#pragma once

#define CarTypeInfoArray 0x9B09D8
#define SingleCarTypeInfoBlockSize 0xD0
#define SingleCarPartSize 0xE

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
#define _IsCollectorsEdition 0x8F8718
#define _UnlockAllThings 0x926124
#define _TweakKitWheelOffsetFront 0x9B0960
#define _TweakKitWheelOffsetRear 0x9B0964
#define _Showcase_FromIndex 0x9B9E84
#define _Showcase_FromFilter 0x905E38
#define _DrawCars 0x903320
#define _DrawLightFlares 0x8F2918
#define _FrontEndRenderingCarList 0x9B27EC
#define _EnableReleasePrintf 0x90E630
#define _MemoryCard_s_pThis 0x91CB20
#define _gTradeInFactor 0x89F71C

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

// Default values for Rim Brands if _RimBrands.ini is N/A
#define DefaultRimBrandCount 10

char* DefaultRimBrandNames[]
{
	"",
	"5ZIGEN",
	"ADR",
	"BBS",
	"ENKEI",
	"KONIG",
	"LOWENHART",
	"RACINGHART",
	"OZ",
	"VOLK",
	"ROJA"
};

char* DefaultRimBrandStrings[]
{
	"CO_RIM_BRAND_CUSTOM",
	"CO_RIM_BRAND_5_ZIGEN",
	"CO_RIM_BRAND_ADR",
	"CO_RIM_BRAND_BBS",
	"CO_RIM_BRAND_ENKEI",
	"CO_RIM_BRAND_KONIG",
	"CO_RIM_BRAND_LOWENHART",
	"CO_RIM_BRAND_RACING_HART",
	"CO_RIM_BRAND_OZ",
	"CO_RIM_BRAND_VOLK",
	"CO_RIM_BRAND_ROJA"
};

char* DefaultRimBrandTextures[]
{
	"VISUAL_RIMS_BRAND_CUSTOM",
	"VISUAL_RIMS_BRAND_5ZIGEN",
	"VISUAL_RIMS_BRAND_ADR",
	"VISUAL_RIMS_BRAND_BBS",
	"VISUAL_RIMS_BRAND_ENKEI",
	"VISUAL_RIMS_BRAND_KONIG",
	"VISUAL_RIMS_BRAND_LOWENHEART",
	"VISUAL_RIMS_BRAND_RACINGHART",
	"VISUAL_RIMS_BRAND_OZ",
	"VISUAL_RIMS_BRAND_VOLK",
	"VISUAL_RIMS_BRAND_RAJA"
};

// Default values for Vinyl Groups if _VinylGroups.ini is N/A
#define DefaultVinylGroupCount 9

int DefaultVinylGroupIndexes[]
{
	31, 0, 1, 2, 3, 4, 5, 6, 7, 8
};

char* DefaultVinylGroupStrings[]
{
	"CO_VINYL_CUSTOM",
	"CO_VINYL_FLAME",
	"CO_VINYL_TRIBAL",
	"CO_VINYL_STRIPE",
	"CO_VINYL_RACE_FLAG",
	"CO_VINYL_NATIONAL_FLAG",
	"CO_VINYL_BODY",
	"CO_VINYL_UNIQUE",
	"CO_VINYL_CONTEST",
	"CO_VINYL_SPECIAL"
};

char* DefaultVinylGroupTextures[]
{
	"VINYL_GROUP_CUSTOM",
	"VINYL_GROUP_FLAMES",
	"VINYL_GROUP_TRIBAL",
	"VINYL_GROUP_STRIPES",
	"VINYL_GROUP_RACING_FLAG",
	"VINYL_GROUP_NATIONAL_FLAG",
	"VINYL_GROUP_BODY",
	"VINYL_GROUP_UNIQUE",
	"VINYL_GROUP_CONTEST",
	"VINYL_GROUP_SPECIAL"
};