// Fill out your copyright notice in the Description page of Project Settings.

#include "WindowsOpenFileOperator.h"
#include "ImageMagickBPLibrary.h"
#include "ImageMagick.h"


FWindowsOpenFileOperator::FWindowsOpenFileOperator():
	isReturn(false)
{
}

FWindowsOpenFileOperator::~FWindowsOpenFileOperator()
{

}
	
void FWindowsOpenFileOperator::OpenFile()
{
#if PLATFORM_WINDOWS
	bool ret = false;
	const FString DialogTitle = FString(TEXT("选择花型"));
	const FString DefaultPath = FPaths::ProjectDir();
	std::string TargetFile;
	FString outFileDir = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectDir(), TEXT("datas"), TEXT("customs"), FGuid::NewGuid().ToString()));
	CreateDir(outFileDir);
	char outFileFullName[1024] = { 0 };
	ret = OpenFileToCopy(TCHAR_TO_ANSI(*DialogTitle), TCHAR_TO_ANSI(*DefaultPath), TCHAR_TO_ANSI(*outFileDir), outFileFullName, 1024);
	TargetFile = outFileFullName;
	UE_LOG(ImageMagick, Log, TEXT("targetFilePath: %s"), ANSI_TO_TCHAR(outFileFullName));
	if (!ret)
	{
		OpenResult.ResultCode = E_CANCEL;
	}
	else
	{
		//TODO Icon , Pattern process
		OpenResult.PatternFilePath = UTF8_TO_TCHAR(outFileFullName);
		FImageInfo imageInfo = UImageMagickBPLibrary::HandleImage(outFileFullName);
		if (imageInfo.IsSuccess)
		{
			OpenResult.IconFilePath = imageInfo.IconPath;
			//TODO DPI,RES
			OpenResult.DPI = FVector2D(imageInfo.DPI.X, imageInfo.DPI.Y);
			OpenResult.RES = FVector2D(imageInfo.RES.X, imageInfo.RES.Y);
			UE_LOG(ImageMagick, Log, TEXT("targetPatternPath: %s"), *OpenResult.PatternFilePath);
			UE_LOG(ImageMagick, Log, TEXT("targetIconPath: %s"), *OpenResult.IconFilePath);
		}
		else
		{
			UE_LOG(ImageMagick, Log, TEXT("WindowsPlatform handle image failed"));
		}
	
		OpenResult.ResultCode = E_OK;
	}
#else
	OpenResult.ResultCode = E_CANCEL;
#endif
	isReturn = true;
}

bool FWindowsOpenFileOperator::IsFinish()
{
	return isReturn;
}

void FWindowsOpenFileOperator::GetOpenResultAndClean(FOpenResult&outResult)
{
	outResult = OpenResult;
	OpenResult.Reset();
}
