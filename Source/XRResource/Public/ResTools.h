// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ImageUtils.h"
#include "IImageWrapper.h"
#include "engine/TextureLightProfile.h"
#include "Engine.h"
#include "Core.h"
#include "IImageWrapperModule.h"

/**
 * 
 */
class XRRESOURCE_API FResTools
{
public:
	FResTools();
	static bool RemoveFileNameExtension(FString& _FileName);
	static FString GetFileExtension(FString& _FileName);

	static FString GetDrawHomeDir(bool _Test = false);
	static FString GetCookedHomeDir(bool _Test = false);
	static FString GetModelDir(bool _Test = false);
	static FString GetGroupPlanDir(bool _Test = false);
	static FString GetAutoDesignGroupPlanDir(bool _Test = false);
	static FString GetLevelPlanDir(bool _Test = false);
	//  ../../../XR/Game/DBJCache/LR/LR_0.pak  =====>>  LR_0
	static FString GetFileNameFromURL(FString& _URL);
	static FString GetXMLNameFromPath(FString& _XMLPath);
	static FString GetFileNameFromPath(FString& _FilePath, FString _FileExtention = TEXT(""));
	static FString GetFolderFromPath(FString& _FilePath);
	static FString GetMD5FromFileName(FString _FileName);
	static FString GetMD5FromFilePath(FString _FilePath);
	static FString GetExtFromFilePath(FString _FilePath);
	//M_001_&0eb24bbe70206ce7b704d00cacab4d65.pak =====>> M_001
	static int32 GetPakIDFromPakName(FString _FileNameWithMD5);
	static int32 GetFileIDFromName(FString _FileNameWithMD5);
	//M_001 ====>> 001
	static FString GetPureItemID(FString _OldItemID);
	

	static bool CheckTeleNumberValid(FString _str);
	static bool CheckNumberValid(FString _str);
	static bool CheckIDCodeValid(FString _str);
	static bool CheckPasswordValid(FString _str);
	static bool CheckEmpty(FString _str);
	static bool CheckAreaValid(FString _str);
	static FString GetSaveDirExcel();
	static FString GetSaveDirPlan();
	static FString GetSaveDirDIYHome();
	static FString GetSaveDirDatabase();
	static FString GetSaveDirHomeStat();
	static FString GetExternalDir();
	static FString GetSaveScreenshot();
	static FString GetVR360SixFacesDir();
	static FString GetPlanNameFromXMLName(FString _XMLName);
	static FString GetDayHourMinStringFromSeconds(int32 _Seconds);
	static FString EncryptString(FString _Str);
	static FString DecryptString(FString _Str);
	
	static void RedirectHttp(FString _URL);
	static void VRSWriteLog(FString _str);
	bool XROpenDirectoryDialog(const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName);
	static bool XROpenFileDialog(TSharedPtr<SWindow> InParentWindow, const FString& DialogTitle, const FString& DefaultPath, TArray<FString>& OutFileNames, FString _FileType, bool _bMulty);
	
	static FString AddCommaForNumber(FString _Number);
	static FString AddCommaForNumber(float _Number);
	static void DeleteFile(FString& Filename);

	
	static bool ContainsPointLightComponent(AActor* _Actor);
	static bool ContainsSpotLightComponent(AActor* _Actor);
	static bool ContainsLightComponent(AActor* _Actor);
	//光源组件通用Get函数
	bool GetLightComponentCastShadow(bool _bPointLight, AActor* _Actor);
	float GetLightComponentIntensity(bool _bPointLight, AActor* _Actor);
	FLinearColor GetLightComponentColor(bool _bPointLight, AActor* _Actor);
	float GetLightComponentRadius(bool _bPointLight, AActor* _Actor);
	//射灯组件Get函数
	float GetSpotLightComponentRadius(AActor* _Actor);
	float GetSpotLightComponentInnerAngle(AActor* _Actor);
	float GetSpotLightComponentOutterAngle(AActor* _Actor);
	UTextureLightProfile* GetSpotLightComponentIES(AActor* _Actor);

	//光源组件通用Set函数
	void SetLightComponentCastShadow(bool _bPointLight, AActor* _Actor, bool _CastShadow);
	void SetLightComponentIntensity(bool _bPointLight, AActor* _Actor, float _Intensity);
	void SetLightComponentColor(bool _bPointLight, AActor* _Actor, FLinearColor _Color);
	void SetLightComponentRadius(bool _bPointLight, AActor* _Actor, float _Radius);
	//射灯组件Set函数
	void SetSpotLightComponentRadius(AActor* _Actor, float _Raidus);
	void SetSpotLightComponentInnerAngle(AActor* _Actor, float _InnerAngle);
	void SetSpotLightComponentOutterAngle(AActor* _Actor, float _OutterAngle);
	void SetSpotLightComponentIES(AActor* _Actor, UTextureLightProfile* _IES);
};
