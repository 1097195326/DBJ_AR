// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserData.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
//#include "EncryptDecryptTool.h"


class UserInfo 
{

public:
	static UserInfo * Get();

private:
	UserInfo();
	~UserInfo();
	static UserInfo *instance;
private:
	FSaveUserData m_SaveUserData;
	FString m_SaveName;
	FString m_SavePath;
	FString m_LocalDataPath;
	FString GetSaveName();
	FString GetSavePath();

	bool	m_IsLogin;
public:
	bool IsLogoin();
	bool ReadLocalData();
	void ClearLocalData();
	bool SaveToLocal(TSharedPtr<FJsonObject> _JsonObj);
	bool SaveUserData(FString key, int value);
	bool SaveUserData(FString key, FString value);
	bool ReadUserData();
	const FSaveUserData&  GetLocalData();
	bool IsExistLocalFile();
	FString GetCookie();
	FString GetToken();

	bool IsAllow4G();
	void	SetUserName(const FString & _userName);

};
