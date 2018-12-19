// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "RenderUtils.h"
#include "Engine/Texture2D.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "PlatformFileManager.h"
#include <string>
#if PLATFORM_WINDOWS
//#include <Magick++.h>
#endif
#if PLATFORM_IOS
#include <Magick++.h>
#endif
#include "ImageMagickBPLibrary.generated.h"


struct FImageInfo
{
	FVector2D DPI;				//dpi
	FVector2D RES;				//分辨率
	FString IconPath;			//iconPath
	bool IsSuccess;
	FImageInfo() { IsSuccess = false; }
};
class UTexture2D;
//define UE_LOG first property
UCLASS(BlueprintType)
class IMAGEMAGICK_API UImageMagickBPLibrary : public UObject
{
	GENERATED_BODY()
	static FString GetExtPart(FString inFilePath);
	static FString GetNamePart(FString inFilePath);
	static FString ChangeName(FString inFilePath,FString inNewName);
public:
	static	FImageInfo HandleImage(FString PatternFilePath);
	static FString ConvertPngToJpg(FString inFilePath);
	//// 转变后缀为inNewExt的路径..
	static FString ChangeExt(FString inFilePath, FString inNewExt);
	static bool GFileExit(const FString & _path);
};
 
