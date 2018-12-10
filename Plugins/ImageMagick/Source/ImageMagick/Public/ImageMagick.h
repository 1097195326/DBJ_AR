// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "ModuleManager.h"
DECLARE_LOG_CATEGORY_EXTERN(ImageMagick, Log, All);
DECLARE_DELEGATE_FiveParams(FOnOpenReresult, bool /*isSuccess*/, FString /*inIconName*/, FString /*inFileName*/, FVector2D /*inDPI*/, FVector2D /*inRes*/);
class IMAGEMAGICK_API IImageMagickModule : public IModuleInterface
{
public:
	static IImageMagickModule& Get();
public:
	/* Return : is can operate , return true, otherwise return false : for example, an open perator is runing */
	virtual bool OpenSelectPattern(FOnOpenReresult inDelegate) = 0;
	virtual bool OpenCamera(FOnOpenReresult inDelegate) = 0;
	virtual bool CopyTo(const FString &inSrcFile, const FString &inTarFile) = 0;
};