#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

char ObjectName[64], ObjectPrefix[64];
char FNGFixName[8], FNGChildName[8];

// 0x5C4D64
bool __fastcall CloneObjectstoShowMoreItemsInMenu(DWORD* FEPackage, void* edx_unused, DWORD* FEGameInterface)
{
	bool result = FEPackage_Startup(FEPackage, FEGameInterface);
	int i;
	DWORD* CloneTarget, * CloneDest, * CloneChild, * CloneChildLast;

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
				if (!CloneTarget)
				{
					i--;
					sprintf(ObjectName, ObjectPrefix, i);
					CloneTarget = FEPackage_FindObjectByHash(FEPackage, bStringHash(ObjectName));
					break;
				}
			}

			// Make enough clones of that object
			if (CloneTarget)
			{
				for (int j = 1; (i + j) <= NewNumberOfObjects; j++)
				{
					CloneDest = (*(DWORD * (__thiscall**)(DWORD*, bool))(*(DWORD*)CloneTarget + 4))(CloneTarget, false); // FE...::Clone

					sprintf(ObjectName, ObjectPrefix, i + j);
					CloneDest[4] = bStringHash(ObjectName); // FEObject -> NameHash
					CloneDest[22] = 0; // FEObject -> Cached (Fix crash at FERenderObject::Clear)
					//FEMinList_AddNode(&(FEPackage[17]), (DWORD*)(FEPackage[20]), CloneDest); // &FEPackage -> Objects, FEPackage -> Objects.Tail

					CloneDest[2] = (DWORD)CloneTarget; // FEobject -> Prev
					CloneDest[1] = CloneTarget[1]; // FEObject -> Next
					CloneTarget[1] = (DWORD)CloneDest; // FEObject -> Next

					// FEObject -> objects.NumElements
					FEPackage[18]++;

					// Check for children if it's a group
					if (CloneDest[0] == _FEGroup_vtbl)
					{
						int ChildrenCount = CloneDest[24]; // FEGroup -> children.NumElements
						CloneChild = (DWORD*)CloneDest[25]; // FEGroup -> children.Head
						CloneChildLast = (DWORD*)CloneDest[26]; // FEGroup -> children.Tail

						for (int c = 1; c <= ChildrenCount; c++)
						{
							if (CloneChild)
							{
								sprintf(FNGChildName, "Child%d", c);

								sprintf(ObjectPrefix, FNGFixesINI.ReadString(FNGFixName, FNGChildName, ""));
								if (strcmp(ObjectPrefix, ""))
								{
									strcat(ObjectPrefix, "%d");
									sprintf(ObjectName, ObjectPrefix, i + j);
									CloneChild[4] = bStringHash(ObjectName); // FEObject -> NameHash
								}

								if (CloneChild == CloneChildLast) break;

								CloneChild = (DWORD*)CloneChild[1]; // FEObject -> Next
							}
						}
					}

					// Clone the new object for the next one
					CloneTarget = CloneDest;
				}
			}

			FEPackage_ConnectObjectResources(FEPackage);
			FEPackage_BuildMouseObjectStateList(FEPackage);
		}
	}

	return result;
}