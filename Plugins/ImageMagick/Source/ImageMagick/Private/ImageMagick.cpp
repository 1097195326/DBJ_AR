// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ImageMagick.h"
#include "Containers/Ticker.h"
#include "IOpenFileOperator.h"
#include "Misc/MessageDialog.h"
#include "PlatformFileManager.h"
#if PLATFORM_ANDROID
#include "AndroidOpenFileOperator.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#elif PLATFORM_WINDOWS
#include "WindowsOpenFileOperator.h"
#elif PLATFORM_MAC
#include "MacOpenFileOperator.h"
#elif PLATFORM_IOS
#include "IOSOpenFileOperator.h"
#endif


#define LOCTEXT_NAMESPACE "FImageMagickModule"
DEFINE_LOG_CATEGORY(ImageMagick);
class FImageMagickModule :public IImageMagickModule
{
public:
	 bool Tick(float DeltaTime);
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool OpenSelectPattern(FOnOpenReresult inDelegate) override;
	virtual bool OpenCamera(FOnOpenReresult inDelegate) override;
	virtual bool CopyTo(const FString &inSrcFile, const FString &inTarFile) override;

protected:
	FTickerDelegate TickDelegate;
	FDelegateHandle TickDelegateHandle;

private:
	IOpenFileOperator *OpenFileOperator;
	FOnOpenReresult OnOpenReresult;
};

bool FImageMagickModule::OpenCamera(FOnOpenReresult inDelegate)
{
	if (OnOpenReresult.IsBound() || OpenFileOperator == nullptr)
	{
		return false;
	}
	OnOpenReresult = inDelegate;
	OpenFileOperator->OpenCamera();

	return true;
}
bool FImageMagickModule::OpenSelectPattern(FOnOpenReresult inDelegate)
{
	// 正在处理上次打开请求.
	if (OnOpenReresult.IsBound() || OpenFileOperator == nullptr)
	{
		return false;
	}
	OnOpenReresult = inDelegate;
	OpenFileOperator->OpenFile();
	return true;
}

bool FImageMagickModule::CopyTo(const FString &inSrcFile, const FString &inTarFile)
{
    IPlatformFile & platformFile =  FPlatformFileManager::Get().GetPlatformFile();
	return platformFile.MoveFile(*inTarFile, *inSrcFile);
}

bool FImageMagickModule::Tick(float DeltaTime)
{
	if (OnOpenReresult.IsBound() && OpenFileOperator != nullptr)
	{
		if (OpenFileOperator->IsFinish())
		{
            FOpenResult result;
            OpenFileOperator->GetOpenResultAndClean(result);

            OnOpenReresult.Execute(result.ResultCode == E_OK,result.IconFilePath, result.PatternFilePath, result.DPI, result.RES);
            OnOpenReresult.Unbind();
		}
	}
	return true;
}

void FImageMagickModule::StartupModule()
{
#if PLATFORM_ANDROID
	OpenFileOperator = FAndroidOpenFileOperator::Get();
#elif PLATFORM_WINDOWS
	OpenFileOperator = FWindowsOpenFileOperator::Get();
#elif PLATFORM_MAC
    OpenFileOperator = FMacOpenFileOperator::Get();
#elif PLATFORM_IOS
    OpenFileOperator = FIOSOpenFileOperator::Get();
#endif
	if (OpenFileOperator == nullptr)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Cannot find file opetator in current platform")));
	}

	TickDelegate = FTickerDelegate::CreateRaw(this, &FImageMagickModule::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
}

void FImageMagickModule::ShutdownModule()
{
	OpenFileOperator = nullptr;
}


	
IImageMagickModule& IImageMagickModule::Get()
{
	return FModuleManager::LoadModuleChecked< FImageMagickModule >("ImageMagick");
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FImageMagickModule, ImageMagick)
