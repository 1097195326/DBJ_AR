#pragma once
#include "CoreMinimal.h"
#include "Http.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Queue.h"
#include "FileDownloader.generated.h"

enum EDownloadState
{
	No = 0,
	Wait,
	Downloading,
	Completed,
	Failed,
	DownloadStateMax
};
enum EDownloadType
{
	PakFile = 0,
	XmlFile,
	PlanList
};

struct  FFileInfo
{
	int32       Id;
	int32       FileSize;
	FString     Url;
	FString     Md5;
	FFileInfo() {}
	FFileInfo(int32 _id, int32 _FileSize, const FString &_Url,const FString &_Md5) { Id = _id;FileSize = _FileSize;Url = _Url;Md5 = _Md5; }
};
struct FTaskInfo
{
	int32 m_Progress=-1;
	EDownloadType m_DownloadType;
	EDownloadState m_DownloadState;
	FFileInfo m_FileInfo;
	FTaskInfo() {}
	FTaskInfo(const FFileInfo &_FileInfo) {
		m_FileInfo = _FileInfo;
	}
};

DECLARE_DELEGATE_TwoParams(FOnDownloadCompleted, FTaskInfo&/*progress and model info*/,TArray<uint8> &/*pak Data*/);
DECLARE_DELEGATE_OneParam(FOnDownloadProgress, FTaskInfo&);


struct FTask
{
public:
	FTaskInfo TaskInfo;
	FOnDownloadProgress OnDownloadProgress;
	FOnDownloadCompleted OnDownloadCompleted;
	FTask(FTaskInfo &_TaskInfo, FOnDownloadProgress &_OnDownloadProgress, FOnDownloadCompleted& _OnDownloadCompleted)
	{
		TaskInfo = _TaskInfo;
		OnDownloadProgress = _OnDownloadProgress;
		OnDownloadCompleted = _OnDownloadCompleted;
	}
	FTask() {}
	void Reset() 
	{
		TaskInfo = FTaskInfo();
		if (OnDownloadProgress.IsBound()) OnDownloadProgress.Unbind();
		if (OnDownloadCompleted.IsBound()) OnDownloadCompleted.Unbind();
	}
};

UCLASS()
class  DOWNLOADTOOL_API UFileDownloader:public UObject
{
	GENERATED_BODY()
public:
	UFileDownloader();
	void Download(FTask &_Task);
private:
	void ReqDownLoad(FTask &_Task);
	FTask m_CurrentTask;
	TQueue<FTask> m_Tasks_WaitQueue;
	void DownloadFileCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void DownloadFileProgressCallback(FHttpRequestPtr Request, int32, int32);
};


class DOWNLOADTOOL_API FileDownloadHelper
{
public:
	static FileDownloadHelper* GetInstance();
	static void ReleaseInstance();
	UFileDownloader* GetDownloader();
private:
	static FileDownloadHelper *m_Instance;
	UFileDownloader *m_FileDownlaoder;
	FileDownloadHelper();
	~FileDownloadHelper();
};