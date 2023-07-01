#include "stdio.h"
#include "InGameFunctions.h"

char const* __fastcall FECarRecord_GetManufacturerName(DWORD* FECarRecord, void* EDX_Unused)
{
	DWORD Attrib[5], AttribParent[5];

	Attrib_Gen_frontend_frontend(Attrib, FECarRecord[1], 0, 0);
	DWORD Parent = Attrib_Instance_GetParent(Attrib);
	Attrib_Gen_frontend_frontend(AttribParent, Parent, 0, 0);
	char const* ManufacturerName = *(const char**)(AttribParent[2] + 24);
	Attrib_Instance_dtInstance(AttribParent);
	Attrib_Instance_dtInstance(Attrib);
	return ManufacturerName;
}