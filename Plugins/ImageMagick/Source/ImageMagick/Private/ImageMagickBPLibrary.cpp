// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#include "ImageMagickBPLibrary.h"
#include "ImageMagick.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "HighResScreenshot.h"

#if PLATFORM_WINDOWS
#include "OpenFileDlg/OpenFileDlgWTF.h"
#elif PLATFORM_MAC
#include "OpenFileDialogLib.h"
#include "CocoaThread.h"
#elif PLATFORM_ANDROID
#include "HaoshaSDKBPLibrary.h"
#endif

using namespace std;

float resX;
float resY;
bool isNear = true;
int32 temp;
bool xOK;
bool yOK;


FImageInfo UImageMagickBPLibrary::HandleImage(FString PatternFilePath)
{
	FImageInfo imageInfo;
#if PLATFORM_WINDOWS || PLATFORM_IOS
	if (!GFileExit(PatternFilePath))
	{
		return imageInfo;
	}
	string patternPath(TCHAR_TO_UTF8(*PatternFilePath));
	FString iconFilePath=ChangeName(PatternFilePath, FGuid::NewGuid().ToString());
	string iconPath(TCHAR_TO_UTF8(*iconFilePath));
	Magick::Image pattern(patternPath);
	
	//会崩溃
	// inputImage.read(path);
	//DPI.X = inputImage.xResolution();
	//DPI.Y = inputImage.yResolution();
	imageInfo.DPI.X = pattern.density().x();
	imageInfo.DPI.Y= pattern.density().y();
	if (imageInfo.DPI.X == 0.0f)
	{
		imageInfo.DPI.X = 300.0f;
	}
	if (imageInfo.DPI.Y == 0.0f)
	{
		imageInfo.DPI.Y = 300.0f;
	}
    
    //GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::Printf(TEXT("读取dpi:x=%f,y=%f"),imageInfo.DPI.X,imageInfo.DPI.Y));
    

	resX = pattern.size().width();
	resY = pattern.size().height();
	/*xOK = false;
	yOK = false;
	for (int i = 12; i > -1; --i)
	{
		if (xOK && yOK) break;

		temp = pow(2, i);
		if (!xOK && ((int)(resX / temp) == 1))
		{
			if (isNear)
			{
				if (resX > temp*1.5)
				{
					resX = temp * 2;
				}
				else
				{
					resX = temp;
				}
			}
			else
			{
				resX = temp;
			}

			xOK = true;
		}
		if (!yOK && ((int)(resY / temp) == 1))
		{
			if (isNear)
			{
				if (resY > temp*1.5)
				{
					resY = temp * 2;
				}
				else
				{
					resY = temp;
				}
			}
			else
			{
				resY = temp;
			}

			yOK = true;
		}
	}*/
	if (resX > 4096) resX = 4096;
	if (resY > 4096) resY = 4096;

	string resolution = std::to_string(resX) + "x" + std::to_string(resY) + "!";
	imageInfo.RES.X = resX;
	imageInfo.RES.Y = resY;
	pattern.resize(Magick::Geometry(resolution));
	pattern.write(patternPath);
	//
	pattern.resize(Magick::Geometry("64x64!"));
	pattern.write(iconPath);
	imageInfo.IconPath = iconFilePath;
	imageInfo.IsSuccess = true;
#endif
	return imageInfo;
}


FString UImageMagickBPLibrary::ConvertPngToJpg(FString inFilePath)
{
	
	FString outFilePath = ChangeExt(inFilePath,"jpg");
	
#if PLATFORM_ANDROID
	UHaoshaSDKBPLibrary::ConvertToJPG(inFilePath,outFilePath);

#endif
#if PLATFORM_WINDOWS
	if (GFileExit(inFilePath))
	{
		Magick::Image pattern(TCHAR_TO_UTF8(*inFilePath));
		pattern.write(TCHAR_TO_UTF8(*outFilePath));
	
	}
#endif
#if PLATFORM_IOS
	if (GFileExit(inFilePath))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::Printf(TEXT("IOS 进入111！！！")));
		Magick::Image pattern(TCHAR_TO_UTF8(*inFilePath));
		pattern.write(TCHAR_TO_UTF8(*outFilePath));
		//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::Printf(TEXT("IOS 进入222！！！")));
		
	}
#endif
	return outFilePath;
}
bool UImageMagickBPLibrary::GFileExit(const FString & _path)
{
    return true;//GPlatformFileManager::FileExists(*_path);
}


FString UImageMagickBPLibrary::ChangeExt(FString inFilePath, FString inNewExt)
{
	FString namepart;
	FString pathpart;
	FString extpart;
	FString ret;
	if (FPaths::ValidatePath(inFilePath))
	{
		FPaths::Split(inFilePath, pathpart, namepart, extpart);
		ret = FPaths::Combine(pathpart, namepart) + "." + inNewExt;
	}

	return ret;
}

FString UImageMagickBPLibrary::GetExtPart(FString inFilePath)
{
	FString namepart;
	FString pathpart;
	FString extpart;
	if (FPaths::ValidatePath(inFilePath))
	{
		FPaths::Split(inFilePath, pathpart, namepart, extpart);
	}

	return extpart;
}


FString UImageMagickBPLibrary::GetNamePart(FString inFilePath)
{
	FString namepart;
	FString pathpart;
	FString extpart;
	if (FPaths::ValidatePath(inFilePath))
	{
		FPaths::Split(inFilePath, pathpart, namepart, extpart);
	}

	return namepart;
}


FString UImageMagickBPLibrary::ChangeName(FString inFilePath, FString inNewName)
{
	FString ret;
	FString namepart;
	FString pathpart;
	FString extpart;
	if (FPaths::ValidatePath(inFilePath))
	{
		FPaths::Split(inFilePath, pathpart, namepart, extpart);
	}
	ret = FPaths::Combine(pathpart, inNewName) + "." + extpart;
	return ret;
} 

