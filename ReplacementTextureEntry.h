#pragma once

#include "stdafx.h"
#include "stdio.h"

#pragma pack(push, 1)

typedef struct
{
	/* 0x0000 */ DWORD hOldNameHash;
	/* 0x0004 */ DWORD hNewNameHash;
	/* 0x0008 */ DWORD* pTextureInfo;
} ReplacementTextureEntry;

#pragma pack(pop)

int ReplacementTextureTable_Find(ReplacementTextureEntry* table, DWORD src, int size)
{
	int result = -1;

	for (int i = 0; i < size; i++)
	{
		if (table[i].hOldNameHash == src)
		{
			result = i;
			break;
		}
	}

	return result;
}

int ReplacementTextureTable_FindFirstEmpty(ReplacementTextureEntry* table, int size)
{
	int result = -1;

	for (int i = 0; i < size; i++)
	{
		if (!table[i].hOldNameHash && !table[i].hNewNameHash)
		{
			result = i;
			break;
		}
	}

	return result;
}

void ReplacementTextureTable_UpdateEntry(ReplacementTextureEntry* table, int index, DWORD dest, int size)
{
	if (index > size) return;

	if (index != -1 && table[index].hNewNameHash != dest)
	{
		table[index].hNewNameHash = dest;
		table[index].pTextureInfo = (DWORD*)-1;
	}
}

void ReplacementTextureTable_WriteEntry(ReplacementTextureEntry* table, int index, DWORD src, DWORD dest, int size)
{
	if (index > size) return;

	if (index != -1 && table[index].hNewNameHash != dest)
	{
		table[index].hOldNameHash = src;
		table[index].hNewNameHash = dest;
		table[index].pTextureInfo = (DWORD*)-1;
	}
}

void ReplacementTextureTable_AddEntry(ReplacementTextureEntry* table, DWORD src, DWORD dest, int size)
{
	int index = ReplacementTextureTable_Find(table, src, size); // Find the entry with src to replace dest
	if (index == -1) index = ReplacementTextureTable_FindFirstEmpty(table, size); // Find first empty entry

	ReplacementTextureTable_WriteEntry(table, index, src, dest, size); // Write entry
}
