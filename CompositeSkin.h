#pragma once

#define CarSkinCount 20
#define NumValuesInParamCache 20

DWORD SkinCompositeParameterCache[CarSkinCount][NumValuesInParamCache]; // 20 skins, 20x DWORD values (0x50/80 bytes in size)
char DummySkinBuf[16];

int SwatchOffsetCount[CarSkinCount];
int SwatchOffsetCache[CarSkinCount][16];


// 0 references in exe
DWORD* GetSkinCompositeParams(DWORD SkinTextureHash) 
{
    // try to figure out the texture
    for (int i = 1; i <= CarSkinCount; i++)
    {
        sprintf(DummySkinBuf, "DUMMY_SKIN%d", i);

        if (SkinTextureHash == bStringHash(DummySkinBuf)) return (DWORD*)(SkinCompositeParameterCache[i-1]);
    }

    return 0; // Return the cache for the skin
}

bool IsInSkinCompositeCache(DWORD* SkinCompositeParams)
{
    DWORD* SkinTexture = (DWORD*)SkinCompositeParams[0];
    DWORD* SkinCompParamCache = GetSkinCompositeParams(SkinTexture[9]);

    if (SkinCompParamCache)
        return CompareCompositeParams(SkinCompParamCache, SkinCompositeParams);
    
    return 0;
}

void UpdateSkinCompositeCache(DWORD* SkinCompositeParams)
{
    DWORD* SkinTexture = (DWORD*)SkinCompositeParams[0];
    DWORD* SkinCompParamCache = GetSkinCompositeParams(SkinTexture[9]);

    if (SkinCompParamCache)
        memcpy(SkinCompParamCache, SkinCompositeParams, 4 * NumValuesInParamCache);
}

void FlushFromSkinCompositeCache(DWORD TextureHash)
{
    DWORD* SkinCompParamCache = GetSkinCompositeParams(TextureHash);

    if (SkinCompParamCache)
        memset(SkinCompParamCache, 0, 4 * NumValuesInParamCache);
}