#pragma once

#include "GObject.h"
#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "IPlatformFilePak.h"
#include "GoodsData.h"


//enum PakType
//{
//	P_StaticMesh,
//	P_Material,
//	P_Blueprint,
//
//};
//struct PakInfo
//{
//	int			ID;
//	FString		MD5;
//	FString		GamePath;
//	FString		FilePath;
//	PakType		Type;
//	UObject *	Object;
////    PakInfo():ID(0),MD5(TEXT("")),FilePath(TEXT("")),GamePath(TEXT("")){}
//
//};

class DBJAR_API GFileManager : public GObject
{
private:
	//TMap<FString, GoodsData*>	m_LoadPak;

	FPakPlatformFile *				m_PakPlatformFile;
	IPlatformFile*					m_LocalPlatformFile;
    
    TMap<FString,FString>               m_MountedFiles;
public:
	virtual void On_Init() override;
	static GFileManager * GetInstance();

	bool FileIsExist(FString _path);
    bool FileIsExist(int _id, FString _md5);
	bool FileIsExist(GoodsData * _data);

	bool PakMount(GoodsData* _goodsData);
	UStaticMesh * LoadMesh(GoodsData * _goodsData);

	FString GetPakFilePath(int _id, FString _md5);
	FString GetPakKey(int _id, FString _md5);
	// exec test pak
	void TestPak();
};
