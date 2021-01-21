#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

char ObjectName[64], ObjectPrefix[64];
char FNGFixName[8];

// 0x5C4D64
bool __fastcall CloneObjectstoShowMoreItemsInMenu(DWORD* FEPackage, void* edx_unused, DWORD* FEGameInterface)
{
	bool result = FEPackage_Startup(FEPackage, FEGameInterface);
	int i;
	DWORD* CloneTarget;

	CIniReader FNGFixesINI("UnlimiterData\\_FNGFixes.ini");

	int FNGFixesCount = FNGFixesINI.ReadInteger("FNGFixes", "NumberOfFNGFixes", -1);
	if (FNGFixesCount == -1) return result;

	for (int FNGFixID = 1; FNGFixID <= FNGFixesCount; FNGFixID++)
	{
		sprintf(FNGFixName, "FNG%d", FNGFixID);
		if (stricmp((char*)FEPackage[3], FNGFixesINI.ReadString(FNGFixName, "FNGName", "")) == 0)
		{
			int NewNumberOfObjects = FNGFixesINI.ReadInteger(FNGFixName, "NumberOfObjects", -1);

			sprintf(ObjectPrefix, FNGFixesINI.ReadString(FNGFixName, "ObjectPrefix", ""));
			strcat(ObjectPrefix, "%d");

			// Get Last available object
			for (i = 1; i <= NewNumberOfObjects; i++)
			{
				sprintf(ObjectName, ObjectPrefix, i);
				CloneTarget = FEPackage_FindObjectByHash(FEPackage, bStringHash(ObjectName));
				if (!CloneTarget) break;
			}
			i--;

			// Make enough clones of that object
			sprintf(ObjectName, ObjectPrefix, i);
			CloneTarget = FEPackage_FindObjectByHash(FEPackage, bStringHash(ObjectName));

			if (CloneTarget) 
			{
				for (int j = 1; (i + j) <= NewNumberOfObjects; j++)
				{
					DWORD* CloneDest = FEObject_Clone(CloneTarget, false);
					sprintf(ObjectName, ObjectPrefix, i + j);
					CloneDest[4] = bStringHash(ObjectName); // FEObject -> NameHash
					CloneDest[22] = 0; // FEObject -> Cached (Fix crash at FERenderObject::Clear)
					FEMinList_AddNode(&(FEPackage[17]), CloneDest, (DWORD*)(FEPackage[20])); // &FEPackage -> Objects, FEPackage -> Objects.Tail
				}
			}
		}
	}
	
	return result;
}