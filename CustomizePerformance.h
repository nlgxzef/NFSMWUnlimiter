#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

#include "CarCustomizeManager.h"
#include "FEShoppingCartItem.h"

DWORD __fastcall CustomizePerformance_GetPerfPkgDesc(DWORD* _CustomizePerformance, void* EDX_Unused, int PerformancePartType, int UpgradePackage, int UpgradePart, bool IsTurbo)
{
    unsigned int result; // eax
    char buf[64];
    char bufd[64];

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    if (UpgradePackage)
    {
        switch (PerformancePartType)
        {
        case 0: // Tires
            sprintf(bufd, "PD_TIRES_%d_%d", UpgradePackage, UpgradePart);
            sprintf(buf, "PerformanceTiresLevel%dItem%d", UpgradePackage, UpgradePart);
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", buf, bufd);
            break;
        case 1: // Brakes
            sprintf(bufd, "PD_BRAKES_%d_%d", UpgradePackage, UpgradePart);
            sprintf(buf, "PerformanceBrakesLevel%dItem%d", UpgradePackage, UpgradePart);
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", buf, bufd);
            break;
        case 2: // Suspension
            sprintf(bufd, "PD_CHASSIS_%d_%d", UpgradePackage, UpgradePart);
            sprintf(buf, "PerformanceChassisLevel%dItem%d", UpgradePackage, UpgradePart);
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", buf, bufd);
            break;
        case 3: // Transmission
            sprintf(bufd, "PD_TRANSMISSION_%d_%d", UpgradePackage, UpgradePart);
            sprintf(buf, "PerformanceTransmissionLevel%dItem%d", UpgradePackage, UpgradePart);
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", buf, bufd);
            break;
        case 4: // Engine
            if (CarCustomizeManager_IsCastrolCar((DWORD*)_gCarCustomizeManager, 0) && UpgradePackage == 4 && UpgradePart == 3)
            {
                sprintf(bufd, "PD_ENGINE_%d_%d_CASTROL", UpgradePackage, UpgradePart);
                sprintf(buf, "PerformanceEngineLevel%dItem%dCastrol", UpgradePackage, UpgradePart);
                result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", buf, bufd);
            }
            else if (CarCustomizeManager_IsRotaryCar((DWORD*)_gCarCustomizeManager, 0) && (UpgradePackage == 2 || UpgradePackage == 4) && UpgradePart == 1)
            {
                sprintf(bufd, "PD_ENGINE_%d_%d_ROTARY", UpgradePackage, UpgradePart);
                sprintf(buf, "PerformanceEngineLevel%dItem%dRotary", UpgradePackage, UpgradePart);
                result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", buf, bufd);
            }
            else
            {
                sprintf(bufd, "PD_ENGINE_%d_%d", UpgradePackage, UpgradePart);
                sprintf(buf, "PerformanceEngineLevel%dItem%d", UpgradePackage, UpgradePart);
                result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", buf, bufd);
            }
            break;
        case 5: // Turbo/Supercharger
            if (IsTurbo)
            {
                sprintf(bufd, "PD_TURBO_%d_%d", UpgradePackage, UpgradePart);
                sprintf(buf, "PerformanceTurboLevel%dItem%d", UpgradePackage, UpgradePart);
                result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", buf, bufd);
            }
            else
            {
                sprintf(bufd, "PD_SUPERCHARGER_%d_%d", UpgradePackage, UpgradePart);
                sprintf(buf, "PerformanceSuperchargerLevel%dItem%d", UpgradePackage, UpgradePart);
                result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", buf, bufd);
            }
            break;
        case 6: // Nitrous
            sprintf(bufd, "PD_NITROUS_%d_%d", UpgradePackage, UpgradePart);
            sprintf(buf, "PerformanceNitrousLevel%dItem%d", UpgradePackage, UpgradePart);
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", buf, bufd);
            break;
        default:
            result = 0;
            break;
        }
    }
    else // Junkman Package
    {
        switch (PerformancePartType)
        {
        case 0: // Tires
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceTiresJunkmanItem", "PD_TIRES_JUNKMAN"); // PD_TIRES_JUNKMAN
            break;
        case 1: // Brakes
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceBrakesJunkmanItem", "PD_BRAKES_JUNKMAN"); // PD_BRAKES_JUNKMAN
            break;
        case 2: // Suspension
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceChassisJunkmanItem", "PD_CHASSIS_JUNKMAN"); // PD_CHASSIS_JUNKMAN
            break;
        case 3: // Transmission
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceTransmissionJunkmanItem", "PD_TRANSMISSION_JUNKMAN"); // PD_TRANSMISSION_JUNKMAN
            break;
        case 4: // Engine
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceEngineJunkmanItem", "PD_ENGINE_JUNKMAN"); // PD_ENGINE_JUNKMAN
            break;
        case 5: // Turbo/Supercharger
            result = IsTurbo ? GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceTurboJunkmanItem", "PD_TURBO_JUNKMAN") // PD_TURBO_JUNKMAN
            : GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceSuperchargerJunkmanItem", "PD_SUPERCHARGER_JUNKMAN"); // PD_SUPERCHARGER_JUNKMAN
            break;
        case 6: // Nitrous
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceNitrousJunkmanItem", "PD_NITROUS_JUNKMAN"); // PD_NITROUS_JUNKMAN
            break;
        default:
            result = 0;
            break;
        }
    }
    return result;
}

DWORD __fastcall CustomizePerformance_GetPerfPkgBrand(DWORD* _CustomizePerformance, void* EDX_Unused, int PerformancePartType, int UpgradePackage, int UpgradePart, bool IsTurbo)
{
    unsigned int result; // eax
    char buf[64];

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    if (UpgradePackage)
    {
        switch (PerformancePartType)
        {
        case 0: // Tires
            sprintf(buf, "PerformanceTiresLevel%dItem%d", UpgradePackage, UpgradePart);
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "");
            break;
        case 1: // Brakes
            sprintf(buf, "PerformanceBrakesLevel%dItem%d", UpgradePackage, UpgradePart);
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "");
            break;
        case 2: // Suspension
            sprintf(buf, "PerformanceChassisLevel%dItem%d", UpgradePackage, UpgradePart);
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "");
            break;
        case 3: // Transmission
            sprintf(buf, "PerformanceTransmissionLevel%dItem%d", UpgradePackage, UpgradePart);
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "");
            break;
        case 4: // Engine
            if (CarCustomizeManager_IsCastrolCar((DWORD*)_gCarCustomizeManager, 0) && UpgradePackage == 4 && UpgradePart == 3)
            {
                sprintf(buf, "PerformanceEngineLevel%dItem%dCastrol", UpgradePackage, UpgradePart);
                result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "");
            }
            else if (CarCustomizeManager_IsRotaryCar((DWORD*)_gCarCustomizeManager, 0) && (UpgradePackage == 2 || UpgradePackage == 4) && UpgradePart == 1)
            {
                sprintf(buf, "PerformanceEngineLevel%dItem%dRotary", UpgradePackage, UpgradePart);
                result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "");
            }
            else
            {
                sprintf(buf, "PerformanceEngineLevel%dItem%d", UpgradePackage, UpgradePart);
                result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "");
            }
            break;
        case 5: // Turbo/Supercharger
            if (IsTurbo)
            {
                sprintf(buf, "PerformanceTurboLevel%dItem%d", UpgradePackage, UpgradePart);
                result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "");
            }
            else
            {
                sprintf(buf, "PerformanceSuperchargerLevel%dItem%d", UpgradePackage, UpgradePart);
                result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "");
            }
            break;
        case 6: // Nitrous
            sprintf(buf, "PerformanceNitrousLevel%dItem%d", UpgradePackage, UpgradePart);
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "");
            break;
        default:
            result = -1;
            break;
        }
    }
    else // Junkman Package
    {
        switch (PerformancePartType)
        {
        case 0: // Tires
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceTiresJunkmanItem", "");
            break;
        case 1: // Brakes
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceBrakesJunkmanItem", "");
            break;
        case 2: // Suspension
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceChassisJunkmanItem", "");
            break;
        case 3: // Transmission
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceTransmissionJunkmanItem", "");
            break;
        case 4: // Engine
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceEngineJunkmanItem", "");
            break;
        case 5: // Turbo/Supercharger
            result = IsTurbo ? GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceTurboJunkmanItem", "")
                : GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceSuperchargerJunkmanItem", "");
            break;
        case 6: // Nitrous
            result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceNitrousJunkmanItem", "");
            break;
        default:
            result = -1;
            break;
        }
    }

    if (result == -1) result = CustomizePerformance_GetPerfPkgBrand_Game(_CustomizePerformance, PerformancePartType, UpgradePackage, UpgradePart - 1);

    return result;
}

unsigned int CustomizePerformance_GetPerfPkgLevelIconHash(int PerfPkgType, int PerfPkgLevel)
{
    unsigned int result; // eax
    char buf[64];

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    sprintf(buf, "Performance");

    switch (PerfPkgType)
    {
    case 0:
        strcat(buf, "Tires");
        break;
    case 1:
        strcat(buf, "Brakes");
        break;
    case 2:
        strcat(buf, "Chassis");
        break;
    case 3:
        strcat(buf, "Transmission");
        break;
    case 4:
        strcat(buf, "Engine");
        break;
    case 5:
        strcat(buf, CarCustomizeManager_IsTurbo((DWORD*)_gCarCustomizeManager) ? "Turbo" : "Supercharger");
        break;
    case 6:
        strcat(buf, "Nitrous");
        break;
    default:
        break;
    }

    switch (PerfPkgLevel)
    {
    case 0:
    default:
        strcat(buf, "Stock");
        result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "PERFORMANCE_ICON_BASE_PACKAGE");
        break;
    case 1:
        strcat(buf, "Street");
        result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "PERFORMANCE_ICON_PACKAGE_1");
        break;
    case 2:
        strcat(buf, "SuperStreet");
        result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "PERFORMANCE_ICON_PACKAGE_1");
        break;
    case 3:
        strcat(buf, "Race");
        result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "PERFORMANCE_ICON_PACKAGE_1");
        break;
    case 4:
        strcat(buf, "Pro");
        result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "PERFORMANCE_ICON_PACKAGE_1");
        break;
    case 5:
        strcat(buf, "SuperPro");
        result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "PERFORMANCE_ICON_PACKAGE_1");
        break;
    case 6:
        strcat(buf, "Ultimate");
        result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "PERFORMANCE_ICON_PACKAGE_1");
        break;
    case 7:
        strcat(buf, "Junkman");
        result = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", buf, "PERFORMANCE_ICON_PACKAGE_1");
        break;
    }

    return result;
}

void __fastcall CustomizePerformance_RefreshHeader(DWORD* _CustomizePerformance, void* EDX_Unused)
{
    int BrandID = 0;
    float EstimatedValues[3];

    DWORD Attrib[8];
    Attrib[6] = 0x883128;
    Attrib[7] = -1;

    DWORD* Slider1 = _CustomizePerformance + 117;
    DWORD* Slider2 = _CustomizePerformance + 134;
    DWORD* Slider3 = _CustomizePerformance + 151;

    DWORD PackageLevelHash = bStringHash("PN_LEVEL_0");

    DWORD* FECarRecord = *(DWORD**)_FECarRecord;

    if (bList_TraversebList(_CustomizePerformance + 12, 0) == _CustomizePerformance[59])
    {
        cSlider_SetValue(Slider1, 0.5f);
        cSlider_SetValue(Slider2, 0.33f);
        cSlider_SetValue(Slider3, 0.17f);
        TwoStageSlider_Draw(Slider1);
        TwoStageSlider_Draw(Slider2);
        TwoStageSlider_Draw(Slider3);

        for (BrandID = 1; BrandID <= 3; BrandID++)
        {
            FEngSetInvisible((DWORD*)_CustomizePerformance[110 + BrandID]);
            FEngSetInvisible((DWORD*)_CustomizePerformance[113 + BrandID]);
            DWORD* BrandIconObj = FEngFindObject((char const*)_CustomizePerformance[4], FEngHashString("BRAND_ICON_%d", BrandID));
            FEngSetInvisible(BrandIconObj);
        }

        DWORD* CostGroup = FEngFindObject((char const*)_CustomizePerformance[4], 0x8D1559A4);
        FEngSetInvisible(CostGroup);
    }
    else
    {
        DWORD* SelectedPart = CustomizationScreen_GetSelectedPart(_CustomizePerformance);
        int PackageLevel = SelectedPart[5];
        int PackageType = SelectedPart[6];
        CarCustomizeManager_PreviewPerfPkg((DWORD*)_gCarCustomizeManager, PackageType, PackageLevel);

        EstimatedValues[0] = 0.0f;
        EstimatedValues[1] = 0.0f;
        EstimatedValues[2] = 0.0f;
        Physics_Info_EstimatePerformance((DWORD*)_PhysicsUpgrades, EstimatedValues);

        cSlider_SetValue(Slider1, EstimatedValues[2]);
        cSlider_SetValue(Slider2, EstimatedValues[1]);
        cSlider_SetValue(Slider3, EstimatedValues[0]);
        TwoStageSlider_Draw(Slider1);
        TwoStageSlider_Draw(Slider2);
        TwoStageSlider_Draw(Slider3);

        switch (SelectedPart[5])
        {
        case 0: // Stock
            PackageLevelHash = FEShoppingCartItem_GetPerfPkgLevelHash(PackageType, 0);
            FEngSetInvisible(FEngFindObject((char const*)_CustomizePerformance[4], 0x957FC90)); // Info area
            FEngSetInvisible(FEngFindObject((char const*)_CustomizePerformance[4], 0x21DCC127)); // Info area bg
            break;
        case 7: // Junkman
            PackageLevelHash = FEShoppingCartItem_GetPerfPkgLevelHash(PackageType, 7);
            FEngSetVisible(FEngFindObject((char const*)_CustomizePerformance[4], 0x957FC90)); // Info area
            FEngSetVisible(FEngFindObject((char const*)_CustomizePerformance[4], 0x21DCC127)); // Info area bg
            break;
        default:
            PackageLevelHash = FEShoppingCartItem_GetPerfPkgLevelHash(PackageType, 6 - Physics_Upgrades_GetMaxLevel((DWORD*)_PhysicsUpgrades, PackageType) + PackageLevel);
            FEngSetVisible(FEngFindObject((char const*)_CustomizePerformance[4], 0x957FC90)); // Info area
            FEngSetVisible(FEngFindObject((char const*)_CustomizePerformance[4], 0x21DCC127)); // Info area bg
            break;
        }

        if (SelectedPart[5]) // Not stock
        {
            int MaxPackages = CarCustomizeManager_GetMaxPackages((DWORD*)_gCarCustomizeManager, PackageType);
            int NumPartsInPackage = 3;

            int RealPackageLevel = MaxPackages + PackageLevel - Physics_Upgrades_GetMaxLevel((DWORD*)_PhysicsUpgrades, PackageType);
            if (CustomizeIsInBackRoom() || PackageLevel == 7) // Junkman
            {
                PackageLevel = 0;
                RealPackageLevel = 0;
                NumPartsInPackage = 1;
            }

            for (BrandID = 1; BrandID <= 3; BrandID++)
            {
                bool IsTurbo = CarCustomizeManager_IsTurbo((DWORD*)_gCarCustomizeManager);
                DWORD PerfPkgDesc = CustomizePerformance_GetPerfPkgDesc(_CustomizePerformance, EDX_Unused, PackageType, RealPackageLevel, BrandID, IsTurbo);

                if (DoesStringExist(PerfPkgDesc))
                {
                    FEngSetVisible((DWORD*)_CustomizePerformance[110 + BrandID]);
                    FEngSetVisible((DWORD*)_CustomizePerformance[113 + BrandID]);
                    FEngSetLanguageHash_obj((DWORD*)_CustomizePerformance[110 + BrandID], PerfPkgDesc);
                }
                else
                {
                    FEngSetInvisible((DWORD*)_CustomizePerformance[110 + BrandID]);
                    FEngSetInvisible((DWORD*)_CustomizePerformance[113 + BrandID]);
                }
                Attrib_Gen_frontend_frontend(Attrib, FECarRecord[1], 0, 0);
                Attrib[7] = 3;

                DWORD BrandIconTexHash = CustomizePerformance_GetPerfPkgBrand(_CustomizePerformance, EDX_Unused, PackageType, RealPackageLevel, BrandID, IsTurbo);
                DWORD BrandIconObjHash = FEngHashString("BRAND_ICON_%d", BrandID);
                DWORD* BrandIconObj = FEngFindObject((char const*)_CustomizePerformance[4], BrandIconObjHash);
                DWORD* BrandIconTexInfo = GetTextureInfo(BrandIconTexHash, 0, 0);

                if (BrandIconTexInfo)
                {
                    FEngSetVisible(BrandIconObj);
                    FEngSetTextureHash_obj(BrandIconObj, BrandIconTexHash);
                }
                else
                {
                    FEngSetInvisible(BrandIconObj);
                }
                Attrib[7] = -1;
                Attrib_Instance_dtInstance(Attrib);

                if (BrandID > NumPartsInPackage)
                {
                    FEngSetInvisible((DWORD*)_CustomizePerformance[110 + BrandID]);
                    FEngSetInvisible((DWORD*)_CustomizePerformance[113 + BrandID]);
                    FEngSetInvisible(BrandIconObj);
                }
            }
        }
    }

    CustomizationScreen_RefreshHeader(_CustomizePerformance);
    FEngSetLanguageHash_obj((DWORD*)_CustomizePerformance[75], PackageLevelHash);
}

void __fastcall CustomizePerformance_Setup(DWORD* _CustomizePerformance, void* EDX_Unused)
{
    const char* FEngPackage; // ebx MAPDST
    int DetailTextLineHash; // eax
    int PerformanceDetailsIconHash; // eax
    int PerformancePartType; // ebp
    unsigned int UnlockHash; // ebx MAPDST
    DWORD* ASelectablePart; // eax MAPDST
    DWORD* v16; // eax
    int v17; // ecx
    DWORD* v18; // edi
    DWORD* v19; // eax
    DWORD* v20; // edi
    int MaxPackages; // ebx
    int MaxLevel; // eax
    bool IsLocked; // al
    int v25; // eax
    bool InstalledPart; // zf
    int CarType; // eax
    int UpgradeLevel; // edi
    int PerfPartInCart; // eax
    DWORD* v34; // eax
    int v35; // ecx
    DWORD* v36; // edx
    DWORD* v37; // eax
    int unk_0a; // [esp+60h] [ebp-78h]
    int v46; // [esp+64h] [ebp-74h]
    DWORD PartList[2]; // [esp+68h] [ebp-70h] BYREF

    DWORD TheAttrib[5]; // [esp+88h] [ebp-50h] BYREF
    DWORD TheSelectablePart[11]; // [esp+9Ch] [ebp-3Ch] BYREF
    int i; // [esp+D4h] [ebp-4h]

    // Get car and customization record
    DWORD* FEDatabase = *(DWORD**)_FEDatabase;
    DWORD* FECarRecord = *(DWORD**)_FECarRecord;
    DWORD* CustomizationRecord = FEPlayerCarDB_GetCustomizationRecordByHandle((DWORD*)(*((DWORD*)FEDatabase + 4) + 0x414), ((BYTE*)FECarRecord)[16]);

    if ((*((BYTE*)FEDatabase + 300) & 1) == 0 && !*(bool*)g_bTestCareerCustomization)
        cFEng_QueuePackageMessage(*(int**)cFEng_mInstance, 0xDE511657, (const char*)_CustomizePerformance[4], 0);

    FEngPackage = (const char*)_CustomizePerformance[4];

    for (i = 1; i <= 3; i++) // Initialize part icon and strings (3)
    {
        DetailTextLineHash = FEngHashString("DETAIL_TEXT_LINE%d", i);
        _CustomizePerformance[110 + i] = (DWORD)FEngFindString(FEngPackage, DetailTextLineHash);

        PerformanceDetailsIconHash = FEngHashString("PERFORMANCE_DETAILS_ICON%d", i);
        _CustomizePerformance[113 + i] = (DWORD)FEngFindImage(FEngPackage, PerformanceDetailsIconHash);
    }


    float CurrAccel = CarCustomizeManager_GetPerformanceRating((DWORD*)_gCarCustomizeManager, 2, 1);
    float PreviewAccel = CarCustomizeManager_GetPerformanceRating((DWORD*)_gCarCustomizeManager, 2, 0);
    TwoStageSlider_Init(_CustomizePerformance + 117, FEngPackage, "ACCELERATION", 0.0, 1.0, 0.0, CurrAccel, PreviewAccel, 160.0);

    float CurrHandling = CarCustomizeManager_GetPerformanceRating((DWORD*)_gCarCustomizeManager, 1, 1);
    float PreviewHandling = CarCustomizeManager_GetPerformanceRating((DWORD*)_gCarCustomizeManager, 1, 0);
    TwoStageSlider_Init(_CustomizePerformance + 134, FEngPackage, "HANDLING", 0.0, 1.0, 0.0, CurrHandling, PreviewHandling, 160.0);

    float CurrTopSpeed = CarCustomizeManager_GetPerformanceRating((DWORD*)_gCarCustomizeManager, 0, 1);
    float PreviewTopSpeed = CarCustomizeManager_GetPerformanceRating((DWORD*)_gCarCustomizeManager, 0, 0);
    TwoStageSlider_Init(_CustomizePerformance + 151, FEngPackage, "TOPSPEED", 0.0, 1.0, 0.0, CurrTopSpeed, PreviewTopSpeed, 160.0);


    switch (_CustomizePerformance[82])
    {
    case 0x201u:
    default:
        PerformancePartType = 4;
        break;
    case 0x202u:
        PerformancePartType = 3;
        break;
    case 0x203u:
        PerformancePartType = 2;
        break;
    case 0x204u:
        PerformancePartType = 6;
        break;
    case 0x205u:
        PerformancePartType = 0;
        break;
    case 0x206u:
        PerformancePartType = 1;
        break;
    case 0x207u:
        PerformancePartType = 5;
        break;
    }

    _CustomizePerformance[87] = FEShoppingCartItem_GetPerfPkgCatHash(PerformancePartType);

    // Init part list
    PartList[0] = (DWORD)PartList;
    PartList[1] = (DWORD)PartList;

    // Stock Part (TODO: Fix stock on backroom so the user can remove a junkman part)
    if (!CustomizeIsInBackRoom())
    {
        ASelectablePart = (DWORD*)j_malloc(0x2Cu);
        if (ASelectablePart)
        {
            *ASelectablePart = SelectablePart_vtable;
            ASelectablePart[3] = 0;
            ASelectablePart[4] = 0;
            ASelectablePart[5] = 0;
            ASelectablePart[6] = PerformancePartType;
            *((BYTE*)ASelectablePart + 28) = 1; // IsPerformancePart
            ASelectablePart[8] = 1;
            ASelectablePart[9] = 0;
            *((BYTE*)ASelectablePart + 40) = 0; // IsJunkman
        }
        else
        {
            ASelectablePart = 0;
        }
        CustomizationScreen_AddPartOption(_CustomizePerformance, ASelectablePart, CustomizePerformance_GetPerfPkgLevelIconHash(PerformancePartType, 0), 0, 0, 0, 0);
    }
    
    // Junkman
    if (CustomizeIsInBackRoom())
    {
        UnlockHash = 0;
        
        ASelectablePart = (DWORD*)j_malloc(0x2Cu);
        if (ASelectablePart)
        {
            *ASelectablePart = SelectablePart_vtable;
            ASelectablePart[3] = 0;
            ASelectablePart[4] = 0;
            ASelectablePart[5] = 7;
            ASelectablePart[6] = PerformancePartType;
            *((BYTE*)ASelectablePart + 28) = 1; // IsPerformancePart
            ASelectablePart[8] = 1;
            ASelectablePart[9] = 0;
            *((BYTE*)ASelectablePart + 40) = 1; // IsJunkman
        }
        else
        {
            ASelectablePart = 0;
        }
        CustomizationScreen_AddPartOption(_CustomizePerformance, ASelectablePart, CustomizePerformance_GetPerfPkgLevelIconHash(PerformancePartType, 7), 7u, 0, UnlockHash, 0);

        if (CarCustomizeManager_IsPartInstalled((DWORD*)_gCarCustomizeManager, ASelectablePart))
        {
            ASelectablePart[8] = ASelectablePart[8] & 0xF | 0x10;
        }
        else if (CarCustomizeManager_IsPartInCart((DWORD*)_gCarCustomizeManager, ASelectablePart))
        {
            ASelectablePart[8] = ASelectablePart[8] & 0xF | 0x20;
        }
    }
    else
    {
        CarCustomizeManager_GetPerformancePartsList((DWORD*)_gCarCustomizeManager, PerformancePartType, PartList);
    }

    // Other parts
    v16 = (DWORD*)PartList[0];
    
    for (unk_0a = 1; (DWORD*)PartList[0] != PartList; ++unk_0a)
    {
        v17 = *v16;
        v18 = v16;
        v19 = (DWORD*)v16[1];
        v20 = (DWORD*)(v18 - 1);
        *v19 = v17;
        *(DWORD*)(v17 + 4) = (DWORD)v19;

        MaxPackages = CarCustomizeManager_GetMaxPackages((DWORD*)_gCarCustomizeManager, PerformancePartType);
        v46 = *((DWORD*)v20 + 5);
        MaxLevel = Physics_Upgrades_GetMaxLevel((DWORD*)_PhysicsUpgrades, PerformancePartType);
        UnlockHash = CarCustomizeManager_GetUnlockHash((DWORD*)_gCarCustomizeManager, _CustomizePerformance[82], MaxPackages + v46 - MaxLevel);
        IsLocked = CarCustomizeManager_IsPartLocked((DWORD*)_gCarCustomizeManager, v20, 0);
        CustomizationScreen_AddPartOption(_CustomizePerformance, v20, CustomizePerformance_GetPerfPkgLevelIconHash(PerformancePartType, 6 + v46 - MaxLevel), unk_0a, 0, UnlockHash, IsLocked);
        v16 = (DWORD*)PartList[0];
    }

    v25 = *((DWORD*)FEDatabase + 4);
    if (((*(DWORD*)(v25 + 172) & 0x2000) != 0 || *(BYTE*)(v25 + 37084)) && Physics_Upgrades_CanInstallJunkman((DWORD*)_PhysicsUpgrades, PerformancePartType))
    {
        ASelectablePart = (DWORD*)j_malloc(0x2Cu);
        if (ASelectablePart)
        {
            *ASelectablePart = SelectablePart_vtable;
            ASelectablePart[3] = 0;
            ASelectablePart[4] = 0;
            ASelectablePart[5] = 7;
            ASelectablePart[6] = PerformancePartType;
            *((BYTE*)ASelectablePart + 28) = 1; // IsPerformancePart
            ASelectablePart[8] = 1;
            ASelectablePart[9] = 0;
            *((BYTE*)ASelectablePart + 40) = 1; // IsJunkman
        }
        else
        {
            ASelectablePart = 0;
        }
        CustomizationScreen_AddPartOption(_CustomizePerformance, ASelectablePart, CustomizePerformance_GetPerfPkgLevelIconHash(PerformancePartType, 7), 7u, 0, 0, 0);

        if (ASelectablePart)
        {
            if (*((BYTE*)ASelectablePart + 28))
            {
                if (*((BYTE*)ASelectablePart + 40))
                {
                    if (CarCustomizeManager_IsJunkmanInstalled((DWORD*)_gCarCustomizeManager, ASelectablePart[6]))
                    {
                    LABEL_46:
                        ASelectablePart[8] = ASelectablePart[8] & 0xF | 0x10;
                        goto LABEL_51;
                    }
                    goto LABEL_49;
                } 
                InstalledPart = ASelectablePart[5] == ((BYTE*)CustomizationRecord)[4 * ASelectablePart[6] + 280];
            }
            else
            {
                CarType = FECarRecord_GetType(FECarRecord);
                InstalledPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, CarType, ASelectablePart[4]) == (DWORD*)ASelectablePart[3];
            }
            if (InstalledPart)
                goto LABEL_46;
        }
    LABEL_49:
        if (CarCustomizeManager_IsPartInCart((DWORD*)_gCarCustomizeManager, ASelectablePart))
        {
            ASelectablePart[8] = ASelectablePart[8] & 0xF | 0x20;
        }
    }
LABEL_51:
    if (CustomizeIsInBackRoom() && ((*((BYTE*)FEDatabase + 300) & 1) != 0 || *(bool*)g_bTestCareerCustomization))
    {
        if (*((BYTE*)_CustomizePerformance + 297))
        {
            *((BYTE*)_CustomizePerformance + 284) = 0;
            *((BYTE*)_CustomizePerformance + 281) = 1;
            *((BYTE*)_CustomizePerformance + 282) = 0;
            _CustomizePerformance[68] = 0;
        }
        (*(void(__thiscall**)(DWORD*, int))(_CustomizePerformance[11] + 64))(_CustomizePerformance + 11, 1); // IconScroller::SetInitialPos
    }
    else
    {
        UpgradeLevel = ((BYTE*)CustomizationRecord)[4 * ASelectablePart[6] + 280];
        TheSelectablePart[0] = (DWORD)SelectablePart_vtable;
            TheSelectablePart[3] = 0;
        TheSelectablePart[4] = 0;
        TheSelectablePart[5] = 0;
        TheSelectablePart[6] = PerformancePartType;
        *((BYTE*)TheSelectablePart + 28) = 1;
        TheSelectablePart[8] = 1;
        TheSelectablePart[9] = 0;
        *((BYTE*)TheSelectablePart + 40) = 0;
        PerfPartInCart = CarCustomizeManager_IsPartTypeInCart((DWORD*)_gCarCustomizeManager, TheSelectablePart);

        if (PerfPartInCart)
            UpgradeLevel = *(DWORD*)(*(DWORD*)(PerfPartInCart + 12) + 20);

        if (*((BYTE*)_CustomizePerformance + 297))
        {
            *((BYTE*)_CustomizePerformance + 284) = 0;
            *((BYTE*)_CustomizePerformance + 281) = 1;
            *((BYTE*)_CustomizePerformance + 282) = 0;
            _CustomizePerformance[68] = 0;
        }
        (*(void(__thiscall**)(DWORD*, int))(_CustomizePerformance[11] + 64))(_CustomizePerformance + 11, UpgradeLevel + 1); // IconScroller::SetInitialPos
    }
    (*(void(__thiscall**)(DWORD*))(*_CustomizePerformance + 12))(_CustomizePerformance);
    v34 = (DWORD*)PartList[0];
    for (i = -1; (DWORD*)PartList[0] != PartList; v34 = (DWORD*)PartList[0])
    {
        v35 = *v34;
        v36 = v34;
        v37 = (DWORD*)v34[1];
        *v37 = v35;
        *(DWORD*)(v35 + 4) = (DWORD)v37;
        if (v36 != (DWORD*)4)
            (*(void(__thiscall**)(DWORD*, int)) * (v36 - 1))(v36 - 1, 1);
    }
}