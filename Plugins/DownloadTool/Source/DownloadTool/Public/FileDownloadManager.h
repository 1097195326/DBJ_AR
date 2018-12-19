// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Queue.h"
#include "WebImageCache.h"
#include "FileDownloader.h"
#include <string>
#include "FileDownloadManager.generated.h"


using namespace std;

struct FDownloadTask
{
	FFileInfo   DownloadInfo;
	EDownloadState      DownloadState;
	int32           Progress;
	EDownloadType   Type;

};
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFileDownloadCompleted, int32 /*state*/, const FFileInfo);
DECLARE_DELEGATE_TwoParams(FOnPlanDownloadCompleted, int32 /*state*/,int32 /*PlanId*/);


//DECLARE_DELEGATE_OneParams(FOnDownloadCompleted, FDownloadTask );
//DECLARE_DELEGATE_OneParams(FOnDownloadProgress, FDownloadTask);
/**
 * 
 */
UCLASS()
class DOWNLOADTOOL_API UFileDownloadManager :public UObject
{
	GENERATED_BODY()

public:
    
    UFileDownloadManager();
    static UFileDownloadManager* Get();
   
	FWebImageCache	m_ImageCache;
 
    //单个模型下载
    bool RequestDownloadFile(FFileInfo  NewDownloadInfo);
    EDownloadState GetDownloadState(int32 Id);
    int32 GetDownloadProgress(int32 Id);
    int32 GetDownloadNum(){return DownloadNum;};
    
    FOnFileDownloadCompleted& OnFileDownloadCompleted(){ return FileDownloadCompletedDelegate;}
    
    //下载xml方案
    void DownloadXmlPlan(FString XmlUrl);
    void DownloadXmlPlanCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response,bool bWasSuccessful);
    //下载方案中所有模型
    bool DownloadPlanModel(TArray<FFileInfo>& ModelList,int32 InPlanId,FString XmlPlanUrl);
    int32 GetPlanProgress(int32& OutPlanId);
    FOnPlanDownloadCompleted& OnPlanDownloadCompleted(){ return PlanDownloadCompletedDelegate;}
    
    FString ProjectHotloadDownloadDir();
    string ExtractIOSDir(const string &DirPath);
    FString ExtractIOSDir(const TCHAR * DirPath);
    FString GetIOSDir();
    FString GetAppPath(const TCHAR * appPath = TEXT(""));
private:
    
      static UFileDownloadManager* FileDownloadManager;
    
    void Init();
    bool AddFileToDownload();
    void DownloadFileCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response,bool bWasSuccessful);
    void DownloadFileProgressCallback(FHttpRequestPtr Request, int32,int32);
    

    
    FDownloadTask* CreateNewTask(FFileInfo&  NewDownloadInfo);
    
    TMap<int32, FDownloadTask*> DownloadTaskMap;
    TQueue<FDownloadTask*> WaitTasks;
    
    int32   DownloadNum;//列表
    FDownloadTask* DoingTask;
    int32 DownloadMax;
    
    TArray<FDownloadTask*> DownloadTaskPool;
    static int32 PoolMax;
    
    FOnFileDownloadCompleted FileDownloadCompletedDelegate;
    
    TSet<FDownloadTask*> XmlModels;
    int32     PlanId;
    FString   XmlUrl;
    int64     PlanTotalSize;
    int32     PlanDownloadSize;
    int32     PlanProgress;
    int32     PlanNum;
    
    FOnPlanDownloadCompleted PlanDownloadCompletedDelegate;
};
