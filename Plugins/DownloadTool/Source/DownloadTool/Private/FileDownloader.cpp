#include "DownloadTool.h"
#include "FileDownloader.h"



FileDownloadHelper* FileDownloadHelper::m_Instance = nullptr;

FileDownloadHelper* FileDownloadHelper::GetInstance()
{
	if (m_Instance==nullptr)
	{
		m_Instance = new FileDownloadHelper();
	}
	return m_Instance;
}

void FileDownloadHelper::ReleaseInstance()
{
	if (m_Instance!=nullptr)
	{
	   delete m_Instance;
	   m_Instance = nullptr;
	}
}

UFileDownloader* FileDownloadHelper::GetDownloader()
{
	check(m_FileDownlaoder);
	return m_FileDownlaoder;
}

FileDownloadHelper::FileDownloadHelper()
{
	m_FileDownlaoder = NewObject<UFileDownloader>();
	m_FileDownlaoder->AddToRoot();
}

FileDownloadHelper::~FileDownloadHelper()
{
	m_FileDownlaoder->RemoveFromRoot();
	//m_FileDownlaoder = nullptr;
}

UFileDownloader::UFileDownloader()
{

}

void UFileDownloader::Download(FTask &_Task)
{
	
	if (m_CurrentTask.TaskInfo.m_DownloadState==EDownloadState::No || m_CurrentTask.TaskInfo.m_DownloadState == EDownloadState::Failed)
	{
		m_CurrentTask=_Task;
		m_CurrentTask.TaskInfo.m_DownloadState = EDownloadState::Downloading;
		ReqDownLoad(m_CurrentTask);
	}
	else
	{
		m_CurrentTask.TaskInfo.m_DownloadState = EDownloadState::Wait;
		//如队列.
		m_Tasks_WaitQueue.Enqueue(_Task);
	}
	
}



void UFileDownloader::ReqDownLoad(FTask &_Task)
{

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(_Task.TaskInfo.m_FileInfo.Url);
	HttpRequest->SetVerb("Get");

	HttpRequest->OnRequestProgress().BindUObject(this, &UFileDownloader::DownloadFileProgressCallback);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UFileDownloader::DownloadFileCompleteCallback);
	HttpRequest->ProcessRequest();
}

void UFileDownloader::DownloadFileCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		m_CurrentTask.TaskInfo.m_DownloadState = EDownloadState::Completed;
		//获取Pak数据.
		TArray<uint8> mPakData = Response->GetContent();
		m_CurrentTask.OnDownloadCompleted.Execute(m_CurrentTask.TaskInfo, mPakData);

		//下一个任务.
		m_CurrentTask.Reset();
		if (!m_Tasks_WaitQueue.IsEmpty())
		{
			//出队列.
			m_Tasks_WaitQueue.Dequeue(m_CurrentTask);
			ReqDownLoad(m_CurrentTask);
		}
	}
	else
	{
		//下载失败处理.
		m_CurrentTask.TaskInfo.m_DownloadState = EDownloadState::Failed;
		TArray<uint8> mPakData;
		m_CurrentTask.OnDownloadCompleted.Execute(m_CurrentTask.TaskInfo, mPakData);
	}
}

void UFileDownloader::DownloadFileProgressCallback(FHttpRequestPtr Request, int32, int32 DownSize)
{
	int32 Progress = DownSize * 100 / (m_CurrentTask.TaskInfo.m_FileInfo.FileSize);
	if (Progress >= 100)
	{
		m_CurrentTask.TaskInfo.m_Progress = 100;
	}
	else if (Progress < 0)
	{
		m_CurrentTask.TaskInfo.m_Progress = 0;
	}
	else
	{
		m_CurrentTask.TaskInfo.m_Progress = Progress;
	}
	m_CurrentTask.OnDownloadProgress.Execute(m_CurrentTask.TaskInfo);
}

