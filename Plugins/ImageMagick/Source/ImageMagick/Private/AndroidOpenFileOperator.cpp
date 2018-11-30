// Fill out your copyright notice in the Description page of Project Settings.

#include "AndroidOpenFileOperator.h"
#include "ImageMagick.h"
#include <string>
#include <string.h>
#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
extern "C"
{
	void Java_com_oss_dachengshidai_OSSModuleNative_onOpenPattern(JNIEnv* inEnv, jobject, jstring inIconPath,jstring inPatternPath,jint inDpiX, jint inDpiY,jint inResX, jint inResY)
	{
		const char* iconfilePath = inEnv->GetStringUTFChars(inIconPath, 0);
		const char* patternfilePath = inEnv->GetStringUTFChars(inPatternPath, 0);
		int dx = inDpiX;
		int dy = inDpiY;
		int rx = inResX;
		int ry = inResY;
		FAndroidOpenFileOperator::Get()->SetRes(FVector2D((float)rx, (float)ry));
		FAndroidOpenFileOperator::Get()->SetDPI(FVector2D((float)dx, (float)dy));
		FAndroidOpenFileOperator::Get()->SetPatternFileName(UTF8_TO_TCHAR(patternfilePath));
		FAndroidOpenFileOperator::Get()->SetIconFileName(UTF8_TO_TCHAR(iconfilePath));//UTF8_TO_TCHAR(iconfilePath).Len()
		FAndroidOpenFileOperator::Get()->SetResultCode(strlen(patternfilePath)== 0 ? E_CANCEL : E_OK);
		FAndroidOpenFileOperator::Get()->SetReturn();
		inEnv->ReleaseStringUTFChars(inIconPath,iconfilePath );
		inEnv->ReleaseStringUTFChars(inPatternPath,patternfilePath);

		UE_LOG(ImageMagick, Log, 
			TEXT("zhoujia:OnOpenPattern:%d,%d,%d,%d,%s,%s,%s,%s"), 
			dx, dy, rx, ry, 
			*FVector2D((float)dx, (float)dy).ToString(), *FVector2D((float)rx, (float)ry).ToString(), 
			UTF8_TO_TCHAR(iconfilePath), UTF8_TO_TCHAR(patternfilePath));
	}
}
#endif

FAndroidOpenFileOperator::FAndroidOpenFileOperator() :
	IsReturn(false)
{

}

void FAndroidOpenFileOperator::OpenFile()
{
#if PLATFORM_ANDROID
	JNIEnv *Env = FAndroidApplication::GetJavaEnv();
	if (Env)
	{
		jclass Class = FAndroidApplication::FindJavaClass("com/epicgames/ue4/GameActivity");
		if (nullptr != Class)
		{
			static jmethodID Method = Env->GetStaticMethodID(Class, "Anroid_OpenLocalImage", "()Z");
			UE_LOG(ImageMagick, Log, TEXT("Upload pattern get system pattern file"));
			Env->CallStaticBooleanMethod(Class, Method);
		}
		Env->DeleteLocalRef(Class);
	}
	else {
		UE_LOG(ImageMagick, Log, TEXT("OSS : failed to get jave environment"));
	}
	// 标识，等待返回.
	IsReturn = false;
#endif
}

void FAndroidOpenFileOperator::OpenCamera()
{
#if PLATFORM_ANDROID
	JNIEnv *Env = FAndroidApplication::GetJavaEnv();
	if (Env)
	{
		jclass Class = FAndroidApplication::FindJavaClass("com/epicgames/ue4/GameActivity");
		if (nullptr != Class)
		{
			static jmethodID Method = Env->GetStaticMethodID(Class, "Android_OpenCamera", "()Z");
			UE_LOG(ImageMagick, Log, TEXT("Upload pattern get system pattern file"));
			Env->CallStaticBooleanMethod(Class, Method);
		}
		Env->DeleteLocalRef(Class);
	}
	else {
		UE_LOG(ImageMagick, Log, TEXT("OSS : failed to get jave environment"));
	}
	// 标识，等待返回.
	IsReturn = false;
#endif
}

bool FAndroidOpenFileOperator::IsFinish()
{
	return IsReturn;
}

void FAndroidOpenFileOperator::GetOpenResultAndClean(FOpenResult&outResult)
{
	outResult = OpenResult;
	OpenResult.Reset();
}

void FAndroidOpenFileOperator::SetPatternFileName(const FString &inFileName)
{
	OpenResult.PatternFilePath = inFileName;
}

void FAndroidOpenFileOperator::SetIconFileName(const FString &inFileName)
{
	OpenResult.IconFilePath = inFileName;
}

void FAndroidOpenFileOperator::SetDPI(const FVector2D &inDPI)
{
	OpenResult.DPI = inDPI;
}

void FAndroidOpenFileOperator::SetRes(const FVector2D &inRes)
{
	OpenResult.RES = inRes;
}

void FAndroidOpenFileOperator::SetResultCode(EOpenReturnCode inCode)
{
	OpenResult.ResultCode = inCode;
}

FAndroidOpenFileOperator::~FAndroidOpenFileOperator()
{
}
