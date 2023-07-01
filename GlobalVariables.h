#pragma once

#define CarTypeInfoArray 0x9B09D8
#define SingleCarTypeInfoBlockSize 0xD0
#define SingleCarPartSize 0xE

#define _nullString 0x890978
#define _SaveFolderNameString 0x901748
#define _CustomizeParts_TexturePackLoaded 0x9B9EB0
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