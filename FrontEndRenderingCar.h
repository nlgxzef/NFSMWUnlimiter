#include "stdio.h"
#include "InGameFunctions.h"

bool __fastcall FrontEndRenderingCar_LookupWheelPosition(DWORD* _FrontEndRenderingCar, void* EDX_Unused, unsigned int index, float* position)
{
    DWORD* _CarRenderInfo; // eax
    float* v4; // edi
    float* AttrPtr; // eax
    float FECompression = 0; // st7

    _CarRenderInfo = (DWORD*)_FrontEndRenderingCar[198];
    if (!_CarRenderInfo || !position)
        return 0;
    v4 = (float*)(_CarRenderInfo[1517] + 16 * (index + 1));
    position[0] = v4[0]; // x
    position[1] = v4[1]; // y
    position[2] = v4[2]; // z
    position[3] = v4[3]; // w
    
    AttrPtr = (float*)Attrib_Instance_GetAttributePointer((DWORD*)(_CarRenderInfo + 1515), 0x8D5BEB72, index >> 1); // FECompressions
    if (!AttrPtr)
        AttrPtr = (float*)Attrib_DefaultDataArea();
    FECompression = *AttrPtr;

    // Get value from custom attribute
    DWORD* TheRideInfo = (DWORD*)_CarRenderInfo[33]; // CarRenderInfo->pRideInfo
    if (TheRideInfo)
    {
        DWORD* BodyKitCarPart = RideInfo_GetPart(TheRideInfo, 23); // BODY_KIT
        if (BodyKitCarPart)
        {
            // Read offset attributes from body kit
            FECompression = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, index >> 1 ? bStringHash("REAR_FECOMPRESSION") : bStringHash("FRONT_FECOMPRESSION"), FECompression);
        }
    }

    position[3] = 1.0;
    position[2] = FECompression + position[2];

    return 1;
}