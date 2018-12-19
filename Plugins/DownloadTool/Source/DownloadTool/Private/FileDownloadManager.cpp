// Fill out your copyright notice in the Description page of Project Settings.

#include "DownloadTool.h"
#include "FileDownloadManager.h"
#include "Engine.h"

FString CalculateMd5(FString filePath)
{
    
    FMD5 Md5Gen;
    TArray<uint8> fileContent;
    FFileHelper::LoadFileToArray(fileContent, *filePath);
    
    Md5Gen.Update(fileContent.GetData(), fileContent.Num());
    uint8 Digest[16];
    Md5Gen.Final(Digest);
    FString MD5;
    for (int32 i = 0; i < 16; i++ ) {
        MD5 += FString::Printf(TEXT("%02x"),Digest[i]);
    }
    
    return MD5;
}
FString CalculateMd5(TArray<uint8>& fileContent)
{
    FMD5 Md5Gen;
    Md5Gen.Update(fileContent.GetData(), fileContent.Num());
    uint8 Digest[16];
    Md5Gen.Final(Digest);
    FString MD5;
    for (int32 i = 0; i < 16; i++ ) {
        MD5 += FString::Printf(TEXT("%02x"),Digest[i]);
    }
    
    return MD5;
}


int32 UFileDownloadManager::PoolMax = 6;
UFileDownloadManager* UFileDownloadManager::FileDownloadManager = nullptr;

UFileDownloadManager* UFileDownloadManager::Get()
{
	if (FileDownloadManager == nullptr)
	{
		FileDownloadManager = NewObject<UFileDownloadManager>();
		FileDownloadManager->AddToRoot();
		FileDownloadManager->Init();
	}
    return FileDownloadManager;
}
 
UFileDownloadManager::UFileDownloadManager()
{
  
}

void UFileDownloadManager::Init()
{
    DownloadMax = PoolMax;
    for (int32 i = 0; i< PoolMax;i++)
    {
        DownloadTaskPool.Add(new FDownloadTask());
    }
    
    DownloadNum = 0;
    PlanId = -1;
}

FDownloadTask* UFileDownloadManager::CreateNewTask(FFileInfo&  NewDownloadInfo)
{
    FDownloadTask* Task = nullptr;
    if (DownloadTaskPool.Num() > 0)
    {
        Task = DownloadTaskPool.Pop();
    }
    else
    {
        Task = new FDownloadTask();
    }
    Task->DownloadInfo = NewDownloadInfo;
    Task->DownloadState = Wait;
    Task->Progress = 0;
    Task->Type = PakFile;
    
    return Task;
    
}

bool UFileDownloadManager::RequestDownloadFile(FFileInfo  NewDownloadInfo)
{
    if(DownloadNum >= DownloadMax)
    {
        return false;
    }
    
    FDownloadTask* Task = CreateNewTask(NewDownloadInfo);
    DownloadTaskMap.Add(NewDownloadInfo.Id,Task);
    WaitTasks.Enqueue(Task);
    
    ++DownloadNum;
    if (DownloadNum == 1)
    {
        AddFileToDownload();
    }
    
    return true;
}

bool UFileDownloadManager::AddFileToDownload()
{
    bool bResult = WaitTasks.Dequeue(DoingTask);
    
    DoingTask->DownloadState = Downloading;
    
    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL(DoingTask->DownloadInfo.Url);
    HttpRequest->SetVerb("Get");
    
    HttpRequest->OnRequestProgress().BindUObject(this, &UFileDownloadManager::DownloadFileProgressCallback);
    HttpRequest->OnProcessRequestComplete().BindUObject(this,&UFileDownloadManager::DownloadFileCompleteCallback);
    bool bReult = HttpRequest->ProcessRequest();
    return bReult;
    
}

void UFileDownloadManager::DownloadFileProgressCallback(FHttpRequestPtr Request, int32,int32 DownSize)
{
    //DoingTask->Prog
    //DoingTask->DownloadInfo.FileSize/100
    int32 Progress = DownSize*100 / (DoingTask->DownloadInfo.FileSize);
    if(Progress >= 100)
    {
        DoingTask->Progress = 100;
    }
    else if(Progress < 0)
    {
        DoingTask->Progress = 0;
    }
    else
    {
        DoingTask->Progress = Progress;
    }
    
    if (DoingTask->Type == PlanList)
    {
        PlanProgress = (PlanDownloadSize + DownSize)*100/PlanTotalSize;
    }
}


void UFileDownloadManager::DownloadFileCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response,bool bWasSuccessful)
{
    if (bWasSuccessful)
    {

        TArray<uint8> pak = Response->GetContent();
        if (CalculateMd5(pak) == DoingTask->DownloadInfo.Md5)
        {
            FString iosDir = GetIOSDir();
            
            FString tmpPath = FString::Printf(TEXT("%s%d_%s.pak"),*iosDir,DoingTask->DownloadInfo.Id,*DoingTask->DownloadInfo.Md5);
           
            FArchive* ar = IFileManager::Get().CreateFileWriter(*tmpPath,0);
   
            ar->Serialize(pak.GetData(),pak.Num());
            ar->FlushCache();
            delete ar;
            ar = nullptr;
        }
        else
        {
            
        }
        
        if (FileDownloadCompletedDelegate.IsBound())
        {
            FileDownloadCompletedDelegate.Broadcast(0,DoingTask->DownloadInfo);
        }
        
        if(XmlModels.Find(DoingTask) != NULL)
        {
            PlanDownloadSize += DoingTask->DownloadInfo.FileSize;
            PlanProgress = PlanDownloadSize*100/PlanTotalSize;
            
            XmlModels.Remove(DoingTask);
            if (XmlModels.Num() == 0) {
                //完成方案下载
                DownloadXmlPlan(XmlUrl);
            }
        }

        
    }
    else
    {
        if (FileDownloadCompletedDelegate.IsBound())
        {
            FileDownloadCompletedDelegate.Broadcast(1,DoingTask->DownloadInfo);
        }
    }
    
    //回收下载任务
    DownloadTaskMap.Remove(DoingTask->DownloadInfo.Id);
    DownloadTaskPool.Add(DoingTask);
    DoingTask = nullptr;
    --DownloadNum;
    if (DownloadNum > 0)
    {
        AddFileToDownload();
    }
}



EDownloadState UFileDownloadManager::GetDownloadState(int32 Id)
{
    FDownloadTask** Task = DownloadTaskMap.Find(Id);
    if(Task == nullptr)
    {
        return No;
    }
    
    return (*Task)->DownloadState;
        
}

int32 UFileDownloadManager::GetDownloadProgress(int32 Id)
{
    FDownloadTask** Task = DownloadTaskMap.Find(Id);
    if(Task == nullptr)
    {
        return -1;
    }
    
    return (*Task)->Progress;
}


void UFileDownloadManager::DownloadXmlPlan(FString InXmlUrl)
{
    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL(InXmlUrl);
    HttpRequest->SetVerb("Get");
    
    //HttpRequest->OnRequestProgress().BindUObject(this, &UFileDownloadManager::DownloadXmlPlanCompleteCallback);
    HttpRequest->OnProcessRequestComplete().BindUObject(this,&UFileDownloadManager::DownloadXmlPlanCompleteCallback);
    bool bReult = HttpRequest->ProcessRequest();
}

void UFileDownloadManager::DownloadXmlPlanCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response,bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        TArray<uint8> xml = Response->GetContent();
        FString xmlName = FPaths::GetBaseFilename(XmlUrl);
        FString tmpPath = FString::Printf(TEXT("%sDlc/Xml/%s.xml"),*FPaths::ProjectSavedDir(),*xmlName);
        FArchive* ar = IFileManager::Get().CreateFileWriter(*tmpPath,0);
        
        ar->Serialize(xml.GetData(),xml.Num());
        ar->FlushCache();
        delete ar;
        ar = nullptr;
        
        PlanDownloadCompletedDelegate.ExecuteIfBound(0,PlanId);
        
        PlanId = -1;
        
        
        return;
    }
}

bool UFileDownloadManager::DownloadPlanModel(TArray<FFileInfo>& ModelList,int32 InPlanId,FString XmlPlanUrl)
{
    //if (PlanId != -1) {
    //    return false;
    //}
    //
    //for (int i = 0; i<ModelList.Num(); i++)
    //{
    //    if(UPakManager::Get()->IsPakExist(ModelList[i].Id,ModelList[i].Md5))
    //    {
    //        continue;
    //    }
    //    
    //    if(GetDownloadState(ModelList[i].Id) == None)
    //    {
    //        FDownloadTask* Task = CreateNewTask(ModelList[i]);
    //        Task->Type = PlanList;
    //        DownloadTaskMap.Add(ModelList[i].Id,Task);
    //        WaitTasks.Enqueue(Task);
    //        ++DownloadNum;
    //        if (DownloadNum == 1)
    //        {
    //            AddFileToDownload();
    //        }
    //        XmlModels.Add(Task);
    //        PlanTotalSize += Task->DownloadInfo.FileSize;
    //    }
    // 
    //}
    //
    //PlanId = InPlanId;
    //XmlUrl = XmlPlanUrl;
    //PlanDownloadSize = 0;
    //PlanProgress = 0;
    //if (XmlModels.Num() == 0)
    //{
    //    DownloadXmlPlan(XmlUrl);
    //}
    
    return true;
}

int32 UFileDownloadManager::GetPlanProgress(int32& OutPlanId)
{
    OutPlanId = PlanId;
    return PlanProgress;
}

FString UFileDownloadManager::ExtractIOSDir(const TCHAR * DirPath)
{
    string cDirPath = TCHAR_TO_UTF8(DirPath);
    string cSource = ExtractIOSDir(cDirPath);

    return FString(UTF8_TO_TCHAR(cSource.c_str()));
}
string UFileDownloadManager::ExtractIOSDir(const string &DirPath)
{
#if PLATFORM_IOS
    FString rootDir = IFileManager::Get().ConvertToAbsolutePathForExternalAppForWrite(TEXT(""));
    std::string sRootDir(TCHAR_TO_UTF8(*rootDir));
    int len = DirPath.length();
    string folder = DirPath.substr(0, len);
    if(string::npos != DirPath.find(sRootDir))
    {
        int flen = sRootDir.length();
        folder = DirPath.substr(flen,len);
    }
    return folder;
#else
    return DirPath;
#endif
}
FString UFileDownloadManager::ProjectHotloadDownloadDir()
{
#if PLATFORM_WINDOWS
    static FString persistentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir(), TEXT("dlc/paks/"));
#elif PLATFORM_ANDROID
    static FString persistentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectPersistentDownloadDir(), TEXT("dlc/paks/"));
#else
    IPlatformFile &  pf = FPlatformFileManager::Get().GetPlatformFile();
    FString AppendPath = FPaths::Combine(FPaths::ProjectSavedDir(),TEXT("dlc/paks/"));
    static FString persistentDir = pf.ConvertToAbsolutePathForExternalAppForWrite(*AppendPath);
#endif
    //UE_LOG(LogTemp,Log,TEXT("zhx : ProjectHotloadDownloadDir : %s"),*persistentDir);

    return persistentDir;
}
FString UFileDownloadManager::GetIOSDir()
{
    FString downDir = ProjectHotloadDownloadDir();
    //UE_LOG(LogTemp,Log,TEXT("zhx : downDir : %s"),*downDir);
    FString iosDir = ExtractIOSDir(*downDir);
    //UE_LOG(LogTemp,Log,TEXT("zhx : iosDir : %s"),*iosDir);

    return iosDir;
}
FString UFileDownloadManager::GetAppPath(const TCHAR * appPath)
{
    IPlatformFile &  pf = FPlatformFileManager::Get().GetPlatformFile();
    FString AppendPath = FPaths::Combine(FPaths::ProjectDir(),appPath);
    
#if PLATFORM_WINDOWS
    return AppendPath;
#elif PLATFORM_ANDROID
    Rp = FPaths::ConvertRelativePathToFull(FPaths::ProjectPersistentDownloadDir(), appPath);
#else
    FString iosAbsPath = pf.ConvertToAbsolutePathForExternalAppForWrite(*AppendPath);
    
    return ExtractIOSDir(*iosAbsPath);
#endif
    
}
