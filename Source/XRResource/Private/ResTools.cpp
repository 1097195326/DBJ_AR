// Fill out your copyright notice in the Description page of Project Settings.

#include "ResTools.h"
#include "Regex.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "AES.h"
#include "PhysicsEngine/BodySetup.h"
#include "XRResourceModule.h"
#include "PlatformFilemanager.h"

FResTools::FResTools()
{
}

bool FResTools::RemoveFileNameExtension(FString& _FileName)
{
	int32 pos = _FileName.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (pos != -1)
	{
		_FileName = _FileName.Mid(0, pos);
		return true;
	}
	return false;
}

FString FResTools::GetFileExtension(FString& _FileName)
{
	int32 pos = _FileName.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (pos != -1)
	{
		return _FileName.RightChop(pos + 1);
	}
	return TEXT("");
}

FString FResTools::GetDrawHomeDir(bool _Test /*= false*/)
{
	return FPaths::ProjectContentDir() + TEXT("DBJCache/DrawHome/");
}

FString FResTools::GetCookedHomeDir(bool _Test)
{
	if (_Test)
		return FPaths::ProjectContentDir() + TEXT("TESTPAK/Home/");
	else
		return FPaths::ProjectContentDir() + TEXT("DBJCache/CookedHome/");
}

FString FResTools::GetModelDir(bool _Test /*= false*/)
{
	return FPaths::ProjectContentDir() + TEXT("DBJCache/Model/");
}

FString FResTools::GetGroupPlanDir(bool _Test /*= false*/)
{
	if (_Test)
		return FPaths::ProjectContentDir() + TEXT("TESTPAK/GroupPlan/");
	else
		return FPaths::ProjectContentDir() + TEXT("DBJCache/GroupPlan/");
}

FString FResTools::GetAutoDesignGroupPlanDir(bool _Test /*= false*/)
{
	if (_Test)
		return FPaths::ProjectContentDir() + TEXT("TESTPAK/AutoDesignGroupPlan/");
	else
		return FPaths::ProjectContentDir() + TEXT("DBJCache/AutoDesignGroupPlan/");
}

FString FResTools::GetLevelPlanDir(bool _Test /*= false*/)
{
	if (_Test)
		return FPaths::ProjectContentDir() + TEXT("TESTPAK/LevelPlan/");
	else
		return FPaths::ProjectContentDir() + TEXT("DBJCache/LevelPlan/");
}

FString FResTools::GetFileNameFromURL(FString& _URL)
{
	int32 pos = _URL.Find(TEXT("/"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	FString FileName = _URL.RightChop(pos + 1);
	return FileName;
}

FString FResTools::GetXMLNameFromPath(FString& _XMLPath)
{
	int32 pos = _XMLPath.Find(TEXT("/"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	FString XMLName = _XMLPath.RightChop(pos + 1);
	return XMLName;
}

FString FResTools::GetFileNameFromPath(FString& _FilePath, FString _FileExtention)
{
	int32 pos = _FilePath.Find(TEXT("/"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	FString FileName = _FilePath.RightChop(pos + 1);
	if (!_FileExtention.IsEmpty())
	{
		FileName.RemoveFromEnd(_FileExtention, ESearchCase::IgnoreCase);
	}
	return FileName;
}

FString FResTools::GetFolderFromPath(FString& _FilePath)
{
	int32 pos = _FilePath.Find(TEXT("/"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (pos != -1)
	{
		return _FilePath.Mid(0, pos);
	}
	return "";
}

FString FResTools::GetMD5FromFileName(FString _FileName)
{
	RemoveFileNameExtension(_FileName);
	//_FileName.RemoveFromEnd(TEXT(".pak"));
	int32 pos = _FileName.Find(TEXT("_&"), ESearchCase::IgnoreCase, ESearchDir::FromStart);
	if (pos != -1)
		return _FileName.RightChop(pos + 2);
	return TEXT("");
}

FString FResTools::GetMD5FromFilePath(FString _FilePath)
{
	int32 pos = _FilePath.Find(TEXT("_&"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (pos != -1)
	{
		_FilePath = _FilePath.RightChop(pos + 2);
		RemoveFileNameExtension(_FilePath);
		_FilePath.RemoveFromEnd(TEXT(".pak"));
		return _FilePath;
	}
	return TEXT("");
}

FString FResTools::GetExtFromFilePath(FString _FilePath)
{
	int32 pos = _FilePath.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	FString Ext = _FilePath.RightChop(pos);
	return Ext;
}

int32 FResTools::GetPakIDFromPakName(FString _FileNameWithMD5)
{
	int32 pos = _FileNameWithMD5.Find(TEXT("_&"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (pos != -1)
	{
		return FCString::Atoi(*_FileNameWithMD5.Mid(0, pos));
	}
	return FCString::Atoi(*_FileNameWithMD5);
}

int32 FResTools::GetFileIDFromName(FString _FileNameWithMD5)
{
	int32 pos = _FileNameWithMD5.Find(TEXT("_"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (pos != -1)
	{
		return FCString::Atoi(*_FileNameWithMD5.Mid(0, pos));
	}
	return FCString::Atoi(*_FileNameWithMD5);
}

FString FResTools::GetPureItemID(FString _OldItemID)
{
	//原来版本ID格式为M_5001，新版本需要转换为5001
	int32 pos = -1;
	_OldItemID.FindChar('_', pos);
	if (pos != -1)
	{
		return _OldItemID.RightChop(pos + 1);
	}
	return _OldItemID;
}

bool FResTools::CheckTeleNumberValid(FString _str)
{
	const FRegexPattern Pattern(TEXT("^(1)\\d{10}$"));
	FRegexMatcher Matcher(Pattern, _str);
	if (Matcher.FindNext())
		return true;
	else
		return false;
}

bool FResTools::CheckNumberValid(FString _str)
{
	const FRegexPattern Pattern(TEXT("^(0|[1-9][0-9]*)$"));
	FRegexMatcher Matcher(Pattern, _str);
	if (Matcher.FindNext())
		return true;
	else
		return false;
}

bool FResTools::CheckIDCodeValid(FString _str)
{
	const FRegexPattern Pattern(TEXT("^\\d{17}(\\d|X|x)$"));
	FRegexMatcher Matcher(Pattern, _str);
	if (Matcher.FindNext())
		return true;

	return false;
}

bool FResTools::CheckPasswordValid(FString _str)
{
	//字母开头，字母数字下划线组成，6-18长度
	//const FRegexPattern Pattern(TEXT("^[a-zA-Z]\\w{5,17}$"));
	//密码有6-18个字母、数字组成
	const FRegexPattern Pattern(TEXT("^\\w{6,18}$"));
	FRegexMatcher Matcher(Pattern, _str);
	if (Matcher.FindNext())
		return true;

	return false;
}

bool FResTools::CheckEmpty(FString _str)
{
	const FRegexPattern Pattern(TEXT("^\\s*|\\s*$"));
	FRegexMatcher Matcher(Pattern, _str);
	if (Matcher.FindNext())
		return false;

	return true;
}

bool FResTools::CheckAreaValid(FString _str)
{
	const FRegexPattern Pattern(TEXT("^([1-9][0-9]*)$"));
	FRegexMatcher Matcher(Pattern, _str);
	if (Matcher.FindNext())
		return true;

	return false;
}

FString FResTools::GetSaveDirExcel()
{
	return FPaths::ProjectSavedDir() + TEXT("SaveExcel/");
}

FString FResTools::GetSaveDirPlan()
{
	return FPaths::ProjectSavedDir() + TEXT("SavePlan/");
}

FString FResTools::GetSaveDirDIYHome()
{
	return FPaths::ProjectSavedDir() + TEXT("SaveDIYHome/");
}

FString FResTools::GetSaveDirDatabase()
{
	return FPaths::ProjectSavedDir() + TEXT("SaveDatabase/");
}

FString FResTools::GetSaveDirHomeStat()
{
	return FPaths::ProjectSavedDir() + TEXT("SaveHomeStat/");
}

FString FResTools::GetExternalDir()
{
	return FPaths::ProjectContentDir() + TEXT("External/");
}

FString FResTools::GetSaveScreenshot()
{
	return FPaths::ProjectSavedDir() + TEXT("SaveScreenshot/");
}

FString FResTools::GetVR360SixFacesDir()
{
	return FPaths::ProjectSavedDir() + TEXT("VR360/");
}

FString FResTools::GetPlanNameFromXMLName(FString _XMLName)
{
	FString result = _XMLName;
	int32 pos;
	result.FindChar('_', pos);
	result = result.RightChop(pos + 1);
	result.FindChar('_', pos);
	result = result.RightChop(pos + 1);

	pos = result.Find(TEXT("_"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	result = result.Mid(0, pos);

	return result;
}

FString FResTools::GetDayHourMinStringFromSeconds(int32 _Seconds)
{
	int32 days = _Seconds / 86400;
	int32 hours = _Seconds % 86400 / 3600;
	int32 mins = _Seconds - days * 86400 - hours * 3600;
	int32 secs = mins % 60;
	mins = mins / 60;
	//int32 mins = _Seconds % 86400 & 3600 / 60;
	return FString::Printf(TEXT("%d天%d小时%d分%d秒"), days, hours, mins, secs);
}

FString FResTools::EncryptString(FString _Str)
{
	return _Str;
	//TArray<uint8> UserNameBufferEncrypt;
	//UserNameBufferEncrypt.SetNum(_Str.Len());
	//memcpy(UserNameBufferEncrypt.GetData(), TCHAR_TO_ANSI(*_Str), _Str.Len());
	////Encrypt
	//FString UserNameEncrypt;
	//FAES::EncryptData(UserNameBufferEncrypt.GetData(), 16);
	//FFileHelper::BufferToString(UserNameEncrypt, UserNameBufferEncrypt.GetData(), UserNameBufferEncrypt.Num());
	////memcpy((void*)(*UserNameEncrypt), UserNameBufferEncrypt.GetData(), UserNameBufferEncrypt.Num());
	////UserNameEncrypt = UTF8_TO_TCHAR(UserNameBufferEncrypt.GetData());
	////TArray<uint8> UserNameBufferDecrypt;
	////UserNameBufferDecrypt.SetNum(UserNameEncrypt.Len());
	////memcpy(UserNameBufferDecrypt.GetData(), TCHAR_TO_ANSI(*UserNameEncrypt), UserNameEncrypt.Len());

	//TArray<uint8> UserNameBufferDecrypt;
	//UserNameBufferDecrypt.SetNum(UserNameEncrypt.Len());
	//memcpy(UserNameBufferDecrypt.GetData(), TCHAR_TO_ANSI(*UserNameEncrypt), UserNameEncrypt.Len());
	////UserNameBufferDecrypt.GetData() = TCHAR_TO_UTF8(*UserNameEncrypt);

	////Decrypt
	//FString UserNameDecrypt;
	//FAES::DecryptData(UserNameBufferDecrypt.GetData(), 16);
	//FFileHelper::BufferToString(UserNameDecrypt, UserNameBufferDecrypt.GetData(), UserNameBufferDecrypt.Num());
	////memcpy(TCHAR_TO_ANSI(*UserNameDecrypt), UserNameBufferDecrypt.GetData(), UserNameBufferDecrypt.Num());
	////UserNameDecrypt = UTF8_TO_TCHAR(UserNameBufferDecrypt.GetData());
	//return UserNameEncrypt;
}

FString FResTools::DecryptString(FString _Str)
{
	return _Str;
	//TArray<uint8> UserNameBufferEncrypt;
	//UserNameBufferEncrypt.SetNum(_Str.Len());
	//memcpy(UserNameBufferEncrypt.GetData(), TCHAR_TO_ANSI(*_Str), _Str.Len());
	////Encrypt
	//FString UserNameDecrypt;
	//FAES::DecryptData(UserNameBufferEncrypt.GetData(), 16);
	//UserNameDecrypt = UTF8_TO_TCHAR(UserNameBufferEncrypt.GetData());

	//return UserNameDecrypt;
}

void FResTools::RedirectHttp(FString _URL)
{
	if (_URL == TEXT(""))
		return;
	FPlatformMisc::OsExecute(TEXT("open"), *_URL);
}

void FResTools::VRSWriteLog(FString _str)
{
	UE_LOG(ResLog, Warning, TEXT("%s"), *_str);
}

bool FResTools::XROpenDirectoryDialog(const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName)
{
#if PLATFORM_WINDOWS
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		void* ParentWindowWindowHandle = NULL;
		ParentWindowWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
		FString FolderName;
		const bool bFolderSelected = DesktopPlatform->OpenDirectoryDialog(
			ParentWindowWindowHandle,
			DialogTitle,
			DefaultPath,
			OutFolderName
		);

		if (bFolderSelected)
		{
			return true;
		}
	}
	return false;
#endif
	return false;
}

bool FResTools::XROpenFileDialog(TSharedPtr<SWindow> InParentWindow, const FString& DialogTitle, const FString& DefaultPath, TArray<FString>& OutFileNames, FString _FileType, bool _bMulty)
{
#if PLATFORM_WINDOWS
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		//void* ParentWindowWindowHandle = NULL;
		//ParentWindowWindowHandle = InParentWindow->GetNativeWindow()->GetOSWindowHandle();
		const void* ParentWindowWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
		FString FolderName;
		const bool bFolderSelected = DesktopPlatform->OpenFileDialog(
			ParentWindowWindowHandle,
			DialogTitle,
			DefaultPath,
			TEXT(""),
			_FileType,//TEXT("Pictures (*.jpg)|*.jpg;*.jpeg|Pictures (*.png)|*.png"),
			_bMulty ? EFileDialogFlags::Multiple : EFileDialogFlags::None,
			OutFileNames
		);

		if (bFolderSelected)
		{
			return true;
		}
	}
	return false;
#endif
	return false;
}

FString FResTools::AddCommaForNumber(FString _Number)
{
	int32 pos = _Number.Find(TEXT("."));
	if (pos != -1)
	{
		pos -= 3;
		while (pos >= 1)
		{
			_Number.InsertAt(pos, TEXT(","));
			pos -= 3;
		}
		return _Number;
	}
	else
	{
		pos = _Number.Len();
		pos -= 3;
		while (pos >= 1)
		{
			_Number.InsertAt(pos, TEXT(","));
			pos -= 3;
		}
		return _Number;
	}
}

FString FResTools::AddCommaForNumber(float _Number)
{
	FString str = FString::Printf(TEXT("%.2f"), _Number);
	int32 pos = str.Find(TEXT("."));
	if (pos != -1)
	{
		pos -= 3;
		while (pos >= 1)
		{
			str.InsertAt(pos, TEXT(","));
			pos -= 3;
		}
		return str;
	}
	else
	{
		pos = str.Len();
		pos -= 3;
		while (pos >= 1)
		{
			str.InsertAt(pos, TEXT(","));
			pos -= 3;
		}
		return str;
	}
}

void FResTools::DeleteFile(FString& Filename)
{
	if (!FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*Filename))
	{
		UE_LOG(ResLog, Warning, TEXT("Failed to delete temp file: %s"), *Filename);
	}
}

bool FResTools::ContainsPointLightComponent(AActor* _Actor)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					UPointLightComponent* LightCOM = Cast<UPointLightComponent>(SceneComp);
// 					USpotLightComponent* LightCOM2 = Cast<USpotLightComponent>(SceneComp);
// 					if (LightCOM && !LightCOM2)
// 					{
// 						return true;
// 					}
// 				}
// 			}
// 		}
// 	}
	return false;
}

bool FResTools::ContainsSpotLightComponent(AActor* _Actor)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 					if (LightCOM)
// 					{
// 						return true;
// 					}
// 				}
// 			}
// 		}
// 	}
	return false;
}

bool FResTools::ContainsLightComponent(AActor* _Actor)
{
// 	if (_Actor)
// 	{
// 		TInlineComponentArray<USceneComponent*> SceneComponents;
// 		_Actor->GetComponents(SceneComponents);
// 		for (USceneComponent* SceneComp : SceneComponents)
// 		{
// 			UPointLightComponent* LightCOM = Cast<UPointLightComponent>(SceneComp);
// 			if (LightCOM)
// 			{
// 				return true;
// 			}
// 		}
// 	}
	return false;
}

bool FResTools::GetLightComponentCastShadow(bool _bPointLight, AActor* _Actor)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					if (_bPointLight)
// 					{
// 						UPointLightComponent* LightCOM = Cast<UPointLightComponent>(SceneComp);
// 						USpotLightComponent* LightCOM2 = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM && !LightCOM2)
// 						{
// 							return LightCOM->CastShadows;
// 						}
// 					}
// 					else
// 					{
// 						USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM)
// 						{
// 							return LightCOM->CastShadows;
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
	return false;
}

float FResTools::GetLightComponentIntensity(bool _bPointLight, AActor* _Actor)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					if (_bPointLight)
// 					{
// 						UPointLightComponent* LightCOM = Cast<UPointLightComponent>(SceneComp);
// 						USpotLightComponent* LightCOM2 = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM && !LightCOM2)
// 						{
// 							return LightCOM->Intensity;
// 						}
// 					}
// 					else
// 					{
// 						USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM)
// 						{
// 							return LightCOM->Intensity;
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
	return 0.f;
}

FLinearColor FResTools::GetLightComponentColor(bool _bPointLight, AActor* _Actor)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					if (_bPointLight)
// 					{
// 						UPointLightComponent* LightCOM = Cast<UPointLightComponent>(SceneComp);
// 						USpotLightComponent* LightCOM2 = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM && !LightCOM2)
// 						{
// 							return LightCOM->LightColor;
// 						}
// 					}
// 					else
// 					{
// 						USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM)
// 						{
// 							return LightCOM->LightColor;
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
	return FLinearColor(1,1,1,1);
}

float FResTools::GetLightComponentRadius(bool _bPointLight, AActor* _Actor)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					if (_bPointLight)
// 					{
// 						UPointLightComponent* LightCOM = Cast<UPointLightComponent>(SceneComp);
// 						USpotLightComponent* LightCOM2 = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM && !LightCOM2)
// 						{
// 							return LightCOM->AttenuationRadius;
// 						}
// 					}
// 					else
// 					{
// 						USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM)
// 						{
// 							return LightCOM->AttenuationRadius;
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
	return 0.f;
}


float FResTools::GetSpotLightComponentRadius(AActor* _Actor)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 					if (LightCOM)
// 					{
// 						return LightCOM->AttenuationRadius;
// 					}
// 				}
// 			}
// 		}
// 	}
	return 0.f;
}

float FResTools::GetSpotLightComponentInnerAngle(AActor* _Actor)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 					if (LightCOM)
// 					{
// 						return LightCOM->InnerConeAngle;
// 					}
// 				}
// 			}
// 		}
// 	}
	return 0.f;
}

float FResTools::GetSpotLightComponentOutterAngle(AActor* _Actor)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 					if (LightCOM)
// 					{
// 						return LightCOM->OuterConeAngle;
// 					}
// 				}
// 			}
// 		}
// 	}
	return 0.f;
}

UTextureLightProfile* FResTools::GetSpotLightComponentIES(AActor* _Actor)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					ULightComponent* LightCOM = Cast<ULightComponent>(SceneComp);
// 					if (LightCOM && LightCOM->IESTexture)
// 					{
// 						return LightCOM->IESTexture;
// 					}
// 				}
// 			}
// 		}
// 	}
	return NULL;
}

//Set
void FResTools::SetLightComponentCastShadow(bool _bPointLight, AActor* _Actor, bool _CastShadow)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					if (_bPointLight)
// 					{
// 						UPointLightComponent* LightCOM = Cast<UPointLightComponent>(SceneComp);
// 						USpotLightComponent* LightCOM2 = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM && !LightCOM2)
// 						{
// 							LightCOM->SetCastShadows(_CastShadow);
// 						}
// 					}
// 					else
// 					{
// 						USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM)
// 						{
// 							LightCOM->SetCastShadows(_CastShadow);
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
}

void FResTools::SetLightComponentIntensity(bool _bPointLight, AActor* _Actor, float _Intensity)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					if (_bPointLight)
// 					{
// 						UPointLightComponent* LightCOM = Cast<UPointLightComponent>(SceneComp);
// 						USpotLightComponent* LightCOM2 = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM && !LightCOM2)
// 						{
// 							LightCOM->SetIntensity(_Intensity);
// 						}
// 					}
// 					else
// 					{
// 						USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM)
// 						{
// 							LightCOM->SetIntensity(_Intensity);
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
}

void FResTools::SetLightComponentColor(bool _bPointLight, AActor* _Actor, FLinearColor _Color)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					if (_bPointLight)
// 					{
// 						UPointLightComponent* LightCOM = Cast<UPointLightComponent>(SceneComp);
// 						USpotLightComponent* LightCOM2 = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM && !LightCOM2)
// 						{
// 							LightCOM->SetLightColor(_Color);
// 						}
// 					}
// 					else
// 					{
// 						USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM)
// 						{
// 							LightCOM->SetLightColor(_Color);
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
}

void FResTools::SetLightComponentRadius(bool _bPointLight, AActor* _Actor, float _Radius)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					if (_bPointLight)
// 					{
// 						UPointLightComponent* LightCOM = Cast<UPointLightComponent>(SceneComp);
// 						USpotLightComponent* LightCOM2 = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM && !LightCOM2)
// 						{
// 							return LightCOM->SetAttenuationRadius(_Radius);
// 						}
// 					}
// 					else
// 					{
// 						USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 						if (LightCOM)
// 						{
// 							return LightCOM->SetAttenuationRadius(_Radius);
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
}


void FResTools::SetSpotLightComponentRadius(AActor* _Actor, float _Raidus)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 					if (LightCOM)
// 					{
// 						return LightCOM->SetAttenuationRadius(_Raidus);
// 					}
// 				}
// 			}
// 		}
// 	}
}

void FResTools::SetSpotLightComponentInnerAngle(AActor* _Actor, float _InnerAngle)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 					if (LightCOM)
// 					{
// 						return LightCOM->SetInnerConeAngle(_InnerAngle);
// 					}
// 				}
// 			}
// 		}
// 	}
}

void FResTools::SetSpotLightComponentOutterAngle(AActor* _Actor, float _OutterAngle)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 					if (LightCOM)
// 					{
// 						return LightCOM->SetOuterConeAngle(_OutterAngle);
// 					}
// 				}
// 			}
// 		}
// 	}
}

void FResTools::SetSpotLightComponentIES(AActor* _Actor, UTextureLightProfile* _IES)
{
// 	if (_Actor)
// 	{
// 		FVRSObject* ResultObj = GPak->GetObjFromObjID(_Actor->GetObjID());
// 		if (ResultObj)
// 		{
// 			TInlineComponentArray<USceneComponent*> SceneComponents;
// 			_Actor->GetComponents(SceneComponents);
// 			//如果是工具制作的标准化交互模型
// 			if (ResultObj->bNormalized)
// 			{
// 				for (USceneComponent* SceneComp : SceneComponents)
// 				{
// 					USpotLightComponent* LightCOM = Cast<USpotLightComponent>(SceneComp);
// 					if (LightCOM)
// 					{
// 						LightCOM->SetIESTexture(_IES);
// 					}
// 				}
// 			}
// 		}
// 	}
}

