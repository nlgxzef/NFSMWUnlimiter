#include "stdio.h"
#include "InGameFunctions.h"

void __declspec(naked) SimConnectionService()
{
	_asm
	{
		mov eax, [ecx+8]
		test eax, eax
		jz NoService
		mov edx, [eax]
		test edx, edx
		jz NoService

		push esi
		mov esi, [esp+8]
		push esi
		push ecx
		mov ecx, eax
		call dword ptr ds: [edx+4]
		pop esi
		retn 4

		NoService:
			xor al,al
			retn 4
	}
}