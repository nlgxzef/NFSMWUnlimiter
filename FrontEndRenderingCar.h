#include "stdio.h"
#include "InGameFunctions.h"

#pragma pack(push, 1)
typedef struct FrontEndRenderingCar
{
    /* 0x0000 */ FrontEndRenderingCar* Next;
    /* 0x0004 */ FrontEndRenderingCar* Prev;
    /* 0x0008 */ DWORD mRideInfo[0xC4];
    /* 0x0318 */ DWORD* RenderInfo;
    /* 0x031C */ int ViewID;
    /* 0x0320 */ bVector3 Position;
    /* 0x0330 */ bMatrix4 BodyMatrix;
    /* 0x0370 */ bMatrix4 TireMatrices[4];
    /* 0x0470 */ bMatrix4 BrakeMatrices[4];
    /* 0x0570 */ DWORD* OverrideModel;
    /* 0x0574 */ int Visible;
    /* 0x0578 */ int nPasses;
    /* 0x057C */ int Reflection;
    /* 0x0580 */ int LightsOn;
    /* 0x0584 */ int CopLightsOn;
    /* 0x0588 */ float ExtraPitch;
    /* 0x058C */ BYTE padding[4];
} FrontEndRenderingCar; /* size: 0x0590 */
#pragma pack(pop)

bool __fastcall FrontEndRenderingCar_LookupWheelPosition(FrontEndRenderingCar* _car, void* EDX_Unused, unsigned int index, bVector4 *position)
{
    DWORD* _CarRenderInfo; // eax
    DWORD* TheRideInfo;
    DWORD* BodyKitCarPart;
    float* AttrPtr; // eax
    float FECompression = 0; // st7
    float ExtraPitch = 0; // st7

    _CarRenderInfo = _car->RenderInfo;
    if (!_CarRenderInfo || !position)
        return 0;

    // Write tire offsets
    Attrib_Gen_ecar_LayoutStruct* eCarAttributes = (Attrib_Gen_ecar_LayoutStruct*)_CarRenderInfo[1517];
    bVector4 TireOffsets = eCarAttributes->TireOffsets[index];
    position->x = TireOffsets.x; // x
    position->y = TireOffsets.y; // y
    position->z = TireOffsets.z; // z
    position->w = TireOffsets.w; // w
    
    // Handle FECompressions
    AttrPtr = (float*)Attrib_Instance_GetAttributePointer((DWORD*)(_CarRenderInfo + 1515), 0x8D5BEB72, index >> 1); // FECompressions
    if (!AttrPtr)
        AttrPtr = (float*)Attrib_DefaultDataArea();
    FECompression = *AttrPtr;

    // Get value from custom attribute
    TheRideInfo = (DWORD*)_CarRenderInfo[33]; // CarRenderInfo->pRideInfo
    if (TheRideInfo)
    {
        BodyKitCarPart = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::BODY); // BODY_KIT
        if (BodyKitCarPart)
        {
            // Read offset attributes from body kit
            FECompression = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, index >> 1 ? bStringHash((char*)"REAR_FECOMPRESSION") : bStringHash((char*)"FRONT_FECOMPRESSION"), FECompression);
        }
    }
    // Write FECompression
    position->w = 1.0;
    position->z += FECompression;

    
    // Handle ExtraPitch
    AttrPtr = (float*)Attrib_Instance_GetAttributePointer((DWORD*)(_CarRenderInfo + 1515), 0xE95257C2, index >> 1); // ExtraPitch
    if (!AttrPtr)
        AttrPtr = (float*)Attrib_DefaultDataArea();
    ExtraPitch = *AttrPtr;

    if (TheRideInfo && BodyKitCarPart)
        ExtraPitch = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, bStringHash((char*)"EXTRA_PITCH"), ExtraPitch);

    _car->ExtraPitch = ExtraPitch;

    // Calculate ExtraPitch (better without??)
    //ExtraPitch *= 0.017453; // deg to rad
    //float ExtraPitchCalculated = tan(ExtraPitch) * (eCarAttributes->TireOffsets[0].x - eCarAttributes->TireOffsets[2].x);
    //if (index >> 1) ExtraPitchCalculated = 0;

    // Write ExtraPitch
    //position->z += ExtraPitchCalculated;

    return 1;
}

bool __fastcall FrontEndRenderingCar_LookupWheelRadius(FrontEndRenderingCar* _car, void* EDX_Unused, unsigned int index, bVector4* position)
{
    DWORD* _CarRenderInfo; // eax
    DWORD* TheRideInfo;
    DWORD* BodyKitCarPart;
    float Radius = 0; // st7

    _CarRenderInfo = _car->RenderInfo;
    if (!_CarRenderInfo || !position)
        return 0;

    // Write tire offsets
    Attrib_Gen_ecar_LayoutStruct* eCarAttributes = (Attrib_Gen_ecar_LayoutStruct*)_CarRenderInfo[1517];
    bVector4 TireOffsets = eCarAttributes->TireOffsets[index];
    Radius = TireOffsets.w;

    // Get value from custom attribute
    TheRideInfo = (DWORD*)_CarRenderInfo[33]; // CarRenderInfo->pRideInfo
    if (TheRideInfo)
    {
        BodyKitCarPart = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::BODY); // BODY_KIT
        if (BodyKitCarPart)
        {
            // Read offset attributes from body kit
            Radius = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, index >> 1 ? bStringHash((char*)"REAR_TIRE_RADIUS") : bStringHash((char*)"FRONT_TIRE_RADIUS"), Radius);
        }
    }

    // Write radius
    position->x = Radius;

    return 1;
}

void __fastcall FrontEndRenderingCar_ApplyExtraPitch(FrontEndRenderingCar* _car, bMatrix4* a)
{
    bMatrix4 RotationMatrix;
    RotationMatrix.v0.x = 1.0f;
    RotationMatrix.v1.y = 1.0f;
    RotationMatrix.v2.z = 1.0f;
    RotationMatrix.v3.w = 1.0f;

    eRotateY(&RotationMatrix, &RotationMatrix, bDegToShort(_car->ExtraPitch));
    
    bCopy(a, &RotationMatrix);
}

// 0x7A99AD
void __declspec(naked) ExtraPitchCave_GarageMainScreen_UpdateRenderingCarParameters()
{
    _asm
    {
        mov dword ptr ds: [esp + 0x7C], 0x3F800000
        lea edx, dword ptr ds: [esp + 0x40]
        mov ecx, dword ptr ds: [ebp + 0x8]
        call FrontEndRenderingCar_ApplyExtraPitch

        push 0x7A99B5
        retn
    }
}