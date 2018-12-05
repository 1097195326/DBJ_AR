// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInfo.h"
#include "Misc/SecureHash.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include <iostream>
#include "FileHelper.h"
#include "PlatformFilemanager.h"
//#include "EncryptDecryptTool.h"
#include "Serialization/JsonSerializer.h"
#include "FileDownloadManager.h"

using namespace std;
UserInfo *UserInfo::instance = nullptr;
UserInfo::UserInfo()
{
	m_SaveName = FString(TEXT("UserData.data"));
    
    FString SavePath = UFileDownloadManager::Get()->GetAppPath();
    
	m_SavePath = FPaths::Combine(SavePath, m_SaveName);
	m_LocalDataPath = FPaths::Combine(SavePath, TEXT("LocalUserData.data"));

    UE_LOG(LogTemp,Log,TEXT("zhx : user info save path : %s"),*m_SavePath);
    
    //m_SavePath = FPaths::ConvertRelativePathToFull(m_SavePath);
	ReadLocalData();
	ReadUserData();
}

UserInfo::~UserInfo()
{
	
}


UserInfo * UserInfo::Get()
{
	static UserInfo info;
	return &info;
}


FString UserInfo::GetCookie()
{
	 return FString::Printf(TEXT("AR_BTAONY_MGW_TOKEN=%s"), *m_SaveUserData.token); 
}
FString UserInfo::GetToken()
{
	return m_SaveUserData.token;
}
bool UserInfo::SaveToLocal(TSharedPtr<FJsonObject> _JsonObj)
{
	
	//序列化.
	FString mJson_Str;
	TSharedRef<TJsonWriter<>> mWriter = TJsonWriterFactory<>::Create(&mJson_Str);
	if (!FJsonSerializer::Serialize(_JsonObj.ToSharedRef(), mWriter))
	{
		UE_LOG(LogTemp, Error, TEXT("Method UserInfo::SaveLocalData Serialize  failed"));
		return false;
	}
	//保存到本地.
	//mJson_Str = EncryptAndDecryptTool::Encrypt(mJson_Str, EncryptKey);

    UE_LOG(LogTemp,Log,TEXT("zhx : User INFO Write : %s"),*mJson_Str);
    
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
		UE_LOG(LogTemp, Error, TEXT("zhx path: %s not extist"), *m_SavePath);
		return false;
	}

	if (!FFileHelper::LoadFileToString(mjson_Str, *m_SavePath))
	{
		return false;
	}
    UE_LOG(LogTemp,Log,TEXT("zhx : User INFO read : %s"),*mjson_Str);
	//mjson_Str = EncryptAndDecryptTool::Decrypt(mjson_Str, EncryptKey);
	//反序列化.
	TSharedPtr<FJsonObject> mJsonObj = MakeShareable(new FJsonObject);
	TSharedRef<TJsonReader<>> mReader = TJsonReaderFactory<>::Create(mjson_Str);
	if (!FJsonSerializer::Deserialize(mReader, mJsonObj))
	{
		UE_LOG(LogTemp, Error, TEXT("Method UserInfo::ReadLocalData Deserialize  failed"));
		return false;
	}
	//解析json组装data.
	TSharedPtr<FJsonObject> data = mJsonObj->GetObjectField(TEXT("data"));
	m_SaveUserData.token = data->GetStringField(TEXT("token"));
	TSharedPtr<FJsonObject> mRentVO = data->GetObjectField(TEXT("userRentVO"));
	m_SaveUserData.id = mRentVO->GetIntegerField(TEXT("id"));
	m_SaveUserData.phone = mRentVO->GetStringField(TEXT("phone"));
	m_SaveUserData.name = mRentVO->GetStringField(TEXT("name"));
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
bool UserInfo::SaveUserData(FString key, int value)
{
	FString mjson_Str;
	TSharedPtr<FJsonObject> mJsonObj = MakeShareable(new FJsonObject);
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*m_LocalDataPath))
	{
		if (!FFileHelper::LoadFileToString(mjson_Str, *m_LocalDataPath))
		{
			return false;
		}
		TSharedRef<TJsonReader<>> mReader = TJsonReaderFactory<>::Create(mjson_Str);
		if (!FJsonSerializer::Deserialize(mReader, mJsonObj))
		{
			UE_LOG(LogTemp, Error, TEXT("Method UserInfo::ReadLocalData Deserialize  failed"));
			return false;
		}
	}
	mJsonObj->SetNumberField(*key, value);

	TSharedRef<TJsonWriter<>> mWriter = TJsonWriterFactory<>::Create(&mjson_Str);
	if (!FJsonSerializer::Serialize(mJsonObj.ToSharedRef(), mWriter))
	{
		UE_LOG(LogTemp, Error, TEXT("Method UserInfo::SaveLocalData Serialize  failed"));
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("zhx : User INFO Write : %s"), *mjson_Str);

	if (!FFileHelper::SaveStringToFile(mjson_Str, *m_LocalDataPath))
	{
		return false;
	}
	ReadUserData();
	return true;
}
bool UserInfo::ReadUserData()
{
	//
	FString mjson_Str;
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*m_LocalDataPath))
	{
		UE_LOG(LogTemp, Error, TEXT("zhx path: %s not extist"), *m_LocalDataPath);
		m_SaveUserData.Allow4G = 1;
		return false;
	}

	if (!FFileHelper::LoadFileToString(mjson_Str, *m_LocalDataPath))
	{
		return false;
	}
	UE_LOG(LogTemp, Log, TEXT("zhx : User INFO read : %s"), *mjson_Str);
	//mjson_Str = EncryptAndDecryptTool::Decrypt(mjson_Str, EncryptKey);
	//反序列化.
	TSharedPtr<FJsonObject> mJsonObj = MakeShareable(new FJsonObject);
	TSharedRef<TJsonReader<>> mReader = TJsonReaderFactory<>::Create(mjson_Str);
	if (!FJsonSerializer::Deserialize(mReader, mJsonObj))
	{
		UE_LOG(LogTemp, Error, TEXT("Method UserInfo::ReadLocalData Deserialize  failed"));
		return false;
	}
	//解析json组装data.
	m_SaveUserData.Allow4G = mJsonObj->GetIntegerField(TEXT("Allow4G"));

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
bool UserInfo::IsAllow4G()
{
	return m_SaveUserData.Allow4G == 1 ? true : false;
}
void UserInfo::SetUserName(const FString & _userName)
{
	m_SaveUserData.name = _userName;
}