// Fill out your copyright notice in the Description page of Project Settings.

#include "IOpenFileOperator.h"
#include "ImageMagick.h"

void IOpenFileOperator::OpenCamera()
{

}

bool IOpenFileOperator::CreateDir(const FString &inDirPath)
{
	FString parentDir = ExtractFileFolder(inDirPath);
	if (!DirIsExist(parentDir)) {
		return CreateDir(parentDir);
	}
	else {
#if PLATFORM_ANDROID
		JNIEnv *Env = FAndroidApplication::GetJavaEnv();
		if (Env)
		{
			jclass Class = FAndroidApplication::FindJavaClass("com/epicgames/ue4/GameActivity");
			if (nullptr != Class)
			{
				jmethodID Android_CreateDirMethodID = Env->GetStaticMethodID(Class, "Android_CreateDir", "(Ljava/lang/String;)Z");
				jstring folder = Env->NewStringUTF(TCHAR_TO_UTF8(*inDirPath));
				bool ret = Env->CallStaticBooleanMethod(Class, Android_CreateDirMethodID, folder);
				Env->DeleteLocalRef(folder);
				if (!ret)
				{
					UE_LOG(ImageMagick, Error, TEXT("CANNOT CREATE DIR %s"), *inDirPath);
				}
				return ret;
			}
			Env->DeleteLocalRef(Class);

		}
		return false;
#else
		IPlatformFile& mPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		bool ret = mPlatformFile.CreateDirectory(*inDirPath);
		if (!ret)
		{
			UE_LOG(ImageMagick, Error, TEXT("CANNOT CREATE DIR %s"), *inDirPath);
		}
		return ret;
#endif
	}
}

FString IOpenFileOperator::ExtractFileFolder(const FString &inFilePath)
{
	int32 beginPos = inFilePath.Find(TEXT("/"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (beginPos == INDEX_NONE)
	{
		beginPos = inFilePath.Find(TEXT("\\"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	}

	if (beginPos == INDEX_NONE)
	{
		return FString(TEXT("."));
	}

	return inFilePath.Left(beginPos);
}

bool IOpenFileOperator::DirIsExist(const FString &inDirPath)
{
	IPlatformFile& mPlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (!mPlatformFile.DirectoryExists(*inDirPath))
	{
		return false;
	}
	return true;
}
