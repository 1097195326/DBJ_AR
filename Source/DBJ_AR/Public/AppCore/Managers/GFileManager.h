#pragma once

#include "GObject.h"
#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "IPlatformFilePak.h"


enum PakType
{
	P_StaticMesh,
	P_Material,
	P_Blueprint,

};
struct PakInfo
{
	int			ID;
	FString		MD5;
	FString		GamePath;
	FString		FilePath;
	PakType		Type;
	UObject *	Object;
//    PakInfo():ID(0),MD5(TEXT("")),FilePath(TEXT("")),GamePath(TEXT("")){}

};

class DBJ_AR_API GFileManager : public GObject
{
private:
	TMap<FString, PakInfo>	m_LoadPak;

	FPakPlatformFile *				m_PakPlatformFile;
	IPlatformFile*					m_LocalPlatformFile;
public:
	virtual void On_Init() override;
	static GFileManager * GetInstance();

	bool FileIsExist(FString _path);

	bool PakMount(FString _filePath,PakInfo & info);
	PakInfo PakMount(int _id, FString _md5);

	FString GetPakFilePath(int _id, FString _md5);
	FString GetPakKey(int _id, FString _md5);

     
    
	void TestPak();
};
