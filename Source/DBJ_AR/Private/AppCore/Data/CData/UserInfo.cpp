// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInfo.h"
#include "Misc/SecureHash.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include <iostream>
#include "FileHelper.h"
#include "PlatformFilemanager.h"
//#include "EncryptDecryptTool.h"
#include "Serialization/JsonSerializer.h"

using namespace std;
UserInfo *UserInfo::instance = nullptr;
UserInfo::UserInfo()
{
	m_SaveName = FString(TEXT("UserData.data"));
	m_SavePath = FPaths::Combine(FPaths::ProjectDir(), m_SaveName);
	//m_SavePath = FPaths::ConvertRelativePathToFull(m_SavePath);
	ReadLocalData();
}

UserInfo::~UserInfo()
{
	
}


UserInfo * UserInfo::Get()
{
	static UserInfo info;
	return &info;
}


FString UserInfo::GetCookieFromToken(FString &token)
{
	 return FString::Printf(TEXT("AR_BTAONY_MGW_TOKEN=%s"), *token); 
}

bool UserInfo::SaveToLocal(TSharedPtr<FJsonObject> *_JsonObj)
{
	//序列化.
	FString mJson_Str;
	TSharedRef<TJsonWriter<>> mWriter = TJsonWriterFactory<>::Create(&mJson_Str);
	if (!FJsonSerializer::Serialize(_JsonObj->ToSharedRef(), mWriter))
	{
		UE_LOG(LogTemp, Error, TEXT("Method UserInfo::SaveLocalData Serialize  failed"));
		return false;
	}
	//保存到本地.
	//mJson_Str = EncryptAndDecryptTool::Encrypt(mJson_Str, EncryptKey);

	if (!FFileHelper::SaveStringToFile(mJson_Str, *m_SavePath))
	{
		return false;
	}
	ReadLocalData();
	return true;
}

bool UserInfo::ReadLocalData()
{
	//
	FString mjson_Str;
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*m_SavePath))
	{
		UE_LOG(LogTemp, Error, TEXT("path: %s not extist"), *m_SavePath);
		return false;
	}

	if (!FFileHelper::LoadFileToString(mjson_Str, *m_SavePath))
	{
		return false;
	}
	//mjson_Str = EncryptAndDecryptTool::Decrypt(mjson_Str, EncryptKey);
	//反序列化.
	TSharedPtr<FJsonObject> mJsonObj = MakeShareable(new FJsonObject);
	TSharedRef<TJsonReader<>> mReader = TJsonReaderFactory<>::Create(mjson_Str);
	if (!FJsonSerializer::Deserialize(mReader, mJsonObj))
	{
		UE_LOG(LogTemp, Error, TEXT("Method UserInfo::ReadLocalData Deserialize  failed"));
		return false;
	}
	/*
		{
		"code": 200,
		"msg": "成功",
		"data": {
			"token": "e53a4e2adeda4887864c8eaf7c9cd050",
			"rentVO": {
				"id": 4,
				"phone": "17701088634",
				"renterName": "",
				"companyName": "",
				"provinceId": 0,
				"cityId": 0,
				"districtId": 0,
				"address": "",
				"detailAddress": "",
				"limit": true,
				"gmtCreate": "2018-09-19 18:04"
			}
		}
	}*/
	//解析json组装data.
	TSharedPtr<FJsonObject> data = mJsonObj->GetObjectField(TEXT("data"));
	m_SaveUserData.token = data->GetStringField(TEXT("token"));
	TSharedPtr<FJsonObject> mRentVO = data->GetObjectField(TEXT("rentVO"));
	m_SaveUserData.id = mRentVO->GetIntegerField(TEXT("id"));
	m_SaveUserData.phone = mRentVO->GetStringField(TEXT("phone"));
	m_SaveUserData.renterName = mRentVO->GetStringField(TEXT("renterName"));
	m_SaveUserData.companyName = mRentVO->GetStringField(TEXT("companyName"));
	m_SaveUserData.provinceId = mRentVO->GetIntegerField(TEXT("provinceId"));
	m_SaveUserData.cityId = mRentVO->GetIntegerField(TEXT("cityId"));
	m_SaveUserData.districtId = mRentVO->GetIntegerField(TEXT("districtId"));
	m_SaveUserData.address = mRentVO->GetStringField(TEXT("address"));
	m_SaveUserData.detailAddress = mRentVO->GetStringField(TEXT("detailAddress"));
	m_SaveUserData.limit = mRentVO->GetBoolField(TEXT("limit"));
	m_SaveUserData.gmtCreate = mRentVO->GetStringField(TEXT("gmtCreate"));
	return true;
}



FString UserInfo::GetSaveName()
{
	return m_SaveName;
}

FString UserInfo::GetSavePath()
{
	return m_SavePath;
}

void UserInfo::ClearLocalData()
{
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*m_SavePath))
	{
		FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*m_SavePath);
	}
}


const FSaveUserData& UserInfo::GetLocalData()
{
	return m_SaveUserData;
}

bool UserInfo::IsExistLocalFile()
{
	return  FPlatformFileManager::Get().GetPlatformFile().FileExists(*m_SavePath);
}
