#pragma once

enum ResourceFileType : __int32
{
	RESOURCE_FILE_NONE = 0x0,
	RESOURCE_FILE_GLOBAL = 0x1,
	RESOURCE_FILE_FRONTEND = 0x2,
	RESOURCE_FILE_INGAME = 0x3,
	RESOURCE_FILE_TRACK = 0x4,
	RESOURCE_FILE_NIS = 0x5,
	RESOURCE_FILE_CAR = 0x6,
	RESOURCE_FILE_LANGUAGE = 0x7,
	RESOURCE_FILE_REPLAY = 0x8,
};

struct LoadedHotFileEntry
{
	bChunk* pChunk;
	int OriginalSize;
	int MaxSize;
	unsigned int Checksum;
};

struct ResourceFile : bTNode<ResourceFile>
{
	bool mEnableFreeMemory;
	ResourceFileType Type;
	int Flags;
	int FileOffset;
	int FileSize;
	const char* Filename;
	const char* HotFilename;
	const char* AllocationName;
	int AllocationParams;
	int FileTransfersInProgress;
	int LoadingFinishedFlag;
	void (*Callback)(void*);
	void* CallbackParam;
	bChunk* pFirstChunk;
	int SizeofChunks;
	LoadedHotFileEntry* pLoadedHotFileEntries;
	int NumLoadedHotFileEntries;
	int HotFileNumber;
};

enum ePlayerHudType : __int32
{
	PHT_NONE = 0x0,
	PHT_STANDARD = 0x1,
	PHT_DRAG = 0x2,
	PHT_SPLIT1 = 0x3,
	PHT_SPLIT2 = 0x4,
	PHT_DRAG_SPLIT1 = 0x5,
	PHT_DRAG_SPLIT2 = 0x6,
};

