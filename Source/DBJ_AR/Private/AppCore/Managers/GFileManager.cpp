#include "GFileManager.h"
#include "FileHelper.h"
#include "Paths.h"
#include "PlatformFilemanager.h"
#include "PackageName.h"
#include "Engine/StreamableManager.h"
#include "FileDownloadManager.h"


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
}
bool GFileManager::FileIsExist(FString _path)
{
	return FPaths::FileExists(_path);
}
bool GFileManager::FileIsExist(int _id, FString _md5)
{
    FString pakPath = GetPakFilePath(_id,_md5);
    return FileIsExist(pakPath);
}
void GFileManager::TestPak()
{
	//PakMount(9, TEXT("01d222cb4f9f18fd1316328e4bb2a007"));

}
bool GFileManager::PakMount(GoodsData* _goodsData)
{
	FString _filePath = GetPakFilePath(_goodsData->modelId, _goodsData->pakMd5);
	if (!FileIsExist(_filePath))
	{
		return false;
	}
    FString _fileKey = GetPakKey(_goodsData->modelId, _goodsData->pakMd5);
    if(m_MountedFiles.Contains(_fileKey))
    {
        _goodsData->GamePath = *m_MountedFiles.Find(_fileKey);
        return true;
    }
	FPlatformFileManager::Get().SetPlatformFile(*m_PakPlatformFile);

	FPakFile PakFile(m_PakPlatformFile, *_filePath, false);

	FString MP = PakFile.GetMountPoint();
	int32 pos1 = MP.Find(TEXT("/Content/"), ESearchCase::IgnoreCase);
	FString MP2 = MP.RightChop(pos1 + 9);
	MP = FPaths::ProjectContentDir() + MP2;

	/*FString MP = PakFile.GetMountPoint();
	int32 pos1 = MP.Find(TEXT("/Content/"), ESearchCase::IgnoreCase);
	FString MP2 = MP.RightChop(pos1);
	MP = TEXT("../../../DBJ_AR") + MP2;*/

	if (m_PakPlatformFile->Mount(*_filePath, 0, *MP))
	{
		/*FString VirtualMountPoint(FString::Printf(TEXT("/Game/%s"), *MP2));
		FPackageName::RegisterMountPoint(VirtualMountPoint, MP);*/
        UE_LOG(LogTemp, Warning, TEXT("zhx %s mount to %s success"), *_filePath, *MP);
	}
	
	TArray<FString> files;
	PakFile.FindFilesAtPath(files, *PakFile.GetMountPoint(), true, false, true);
	
	//FStreamableManager streamableManager;

	for (int32 FileIndex = 0; FileIndex < files.Num(); FileIndex++)
	{
		UE_LOG(LogTemp, Log, TEXT("zhx : file name : %s"), *files[FileIndex]);
		if (files[FileIndex].EndsWith(TEXT(".uasset")))
		{
			FString fileName(files[FileIndex]);
			UE_LOG(LogTemp, Log, TEXT("zhx : file name : %s"), *fileName);
			FString shortName = FPackageName::GetShortName(fileName);
			UE_LOG(LogTemp, Log, TEXT("zhx : file name : %s"), *shortName);
			//if (shortName.Equals(_goodsData->modelName))
			if (shortName.Equals(FString::Printf(TEXT("%s.uasset"),*_goodsData->modelName)))
			{
				//拼出UObject的加载路径
				fileName.RemoveFromEnd(TEXT(".uasset"), ESearchCase::IgnoreCase);
				int32 pos = fileName.Find(TEXT("/Content/"), ESearchCase::IgnoreCase);
				fileName = fileName.RightChop(pos + 8);
				fileName = TEXT("/Game") + fileName;
				_goodsData->GamePath = fileName;
				UE_LOG(LogTemp, Log, TEXT("zhx : pak mount game path : %s"), *fileName);
			}
		}
	}
    FPlatformFileManager::Get().SetPlatformFile(*m_LocalPlatformFile);

	return true;
}
FString GFileManager::GetPakFilePath(int _id, FString _md5)
{
    FString iosDir = UFileDownloadManager::Get()->GetIOSDir();
	FString pakPath = FString::Printf(TEXT("%s%d_%s.pak"), *iosDir, _id, *_md5);
	return pakPath;
}
FString GFileManager::GetPakKey(int _id, FString _md5)
{
	return FString::Printf(TEXT("%d_%s"), _id, *_md5);
}
