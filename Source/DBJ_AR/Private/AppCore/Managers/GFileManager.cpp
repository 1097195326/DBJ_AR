#include "GFileManager.h"
#include "FileHelper.h"
#include "Paths.h"
#include "PlatformFilemanager.h"
#include "PackageName.h"
#include "Engine/StreamableManager.h"

GFileManager * GFileManager::GetInstance()
{
	static GFileManager m;
	return &m;
}
void GFileManager::On_Init()
{
	m_LocalPlatformFile = &FPlatformFileManager::Get().GetPlatformFile();
	m_PakPlatformFile = new FPakPlatformFile();

	if (m_LocalPlatformFile != nullptr)
	{
		m_PakPlatformFile->Initialize(m_LocalPlatformFile, TEXT("PakPlatformFile"));
		m_PakPlatformFile->InitializeNewAsyncIO();
	}
//    FPlatformFileManager::Get().SetPlatformFile(*m_PakPlatformFile);
}
bool GFileManager::FileIsExist(FString _path)
{
	return FPaths::FileExists(_path);
}
void GFileManager::TestPak()
{
	PakMount(9, TEXT("01d222cb4f9f18fd1316328e4bb2a007"));

}
PakInfo GFileManager::PakMount(int _id, FString _md5)
{
	PakInfo info;
	FString pakKey = GetPakKey(_id, _md5);
	if (m_LoadPak.Contains(pakKey))
	{
		info = *m_LoadPak.Find(pakKey);
	}
	else
	{
		FString filePath = GetPakFilePath(_id, _md5);

		if (FileIsExist(filePath))
		{
			if (PakMount(filePath, info))
			{
				info.ID = _id;
				info.MD5 = _md5;
				info.FilePath = filePath;
				m_LoadPak.Add(pakKey, info);
			}
			
		}
	}
	
	return info;
}

bool GFileManager::PakMount(FString _filePath,PakInfo & info)
{
	FPlatformFileManager::Get().SetPlatformFile(*m_PakPlatformFile);

	FPakFile PakFile(m_PakPlatformFile, *_filePath, false);

	//FString MP = PakFile.GetMountPoint();
	//UE_LOG(LogTemp, Log, TEXT("zhx : pak file mout point : %s"), *MP);

	//int32 pos1 = MP.Find(TEXT("/Content/"), ESearchCase::IgnoreCase);
	//FString MP2 = MP.RightChop(pos1 + 9);
	//MP = FPaths::ProjectContentDir() + MP2;


	FString MP = PakFile.GetMountPoint();
	int32 pos1 = MP.Find(TEXT("/Content/"), ESearchCase::IgnoreCase);
	FString MP2 = MP.RightChop(pos1);
	MP = TEXT("../../../DBJ_AR") + MP2;

	if (m_PakPlatformFile->Mount(*_filePath, 0, *MP))
	{
		/*FString VirtualMountPoint(FString::Printf(TEXT("/Game/%s"), *MP2));
		FPackageName::RegisterMountPoint(VirtualMountPoint, MP);
		UE_LOG(LogTemp, Warning, TEXT("zhx %s mount to %s success"), *_filePath, *VirtualMountPoint);*/
		UE_LOG(LogTemp, Log, TEXT("zhx : pak mount fail : %s"), *_filePath);
	}
	
	TArray<FString> files;
	PakFile.FindFilesAtPath(files, *PakFile.GetMountPoint(), true, false, true);
	
	//FStreamableManager streamableManager;

	for (int32 FileIndex = 0; FileIndex < files.Num(); FileIndex++)
	{
		//UE_LOG(LogTemp, Log, TEXT("zhx : file name : %s"), *files[FileIndex]);
		if (files[FileIndex].EndsWith(TEXT(".uasset")))
		{
			FString fileName(files[FileIndex]);
			//UE_LOG(LogTemp, Log, TEXT("zhx : file name : %s"), *fileName);
			FString shortName = FPackageName::GetShortName(fileName);
			//UE_LOG(LogTemp, Log, TEXT("zhx : file name : %s"), *shortName);
			if (shortName.Equals(TEXT("AR_HuaPen_181026013.uasset")))
			{
				//拼出UObject的加载路径
				fileName.RemoveFromEnd(TEXT(".uasset"), ESearchCase::IgnoreCase);
				int32 pos = fileName.Find(TEXT("/Content/"), ESearchCase::IgnoreCase);
				fileName = fileName.RightChop(pos + 8);
				fileName = TEXT("/Game") + fileName;
				info.GamePath = fileName;
//               UObject* object = LoadObject<UStaticMesh>(nullptr, *fileName);
				
				/*FStreamableManager StreamableManager;
				UObject* obj = StreamableManager.LoadSynchronous(FStringAssetReference(ps), true);
				if (obj)
				{
				}*/
//                info.Object = object;
				UE_LOG(LogTemp, Log, TEXT("zhx : pak mount game path : %s"), *fileName);
			}
			
		}
	}

    FPlatformFileManager::Get().SetPlatformFile(*m_LocalPlatformFile);

	return true;
}
FString GFileManager::GetPakFilePath(int _id, FString _md5)
{
	FString pakPath = FString::Printf(TEXT("%sdlc/paks/%d_%s.pak"), *FPaths::ProjectSavedDir(), _id, *_md5);
	return pakPath;
}
FString GFileManager::GetPakKey(int _id, FString _md5)
{
	return FString::Printf(TEXT("%d_%s"), _id, *_md5);
}
