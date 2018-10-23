// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FolderConfigure.h"
/**
 * 
 */
class FPackAction
{
public:
	FPackAction();
	~FPackAction();
	void DoPackage();
	UFolderConfigure *GetConfigure() { return FolderConfigure; }
	void SaveConfig();
protected:
	void CookContent();
	bool GenerateCookTargetFile();
	bool GeneratePakFiles();
	bool GeneratePakName(FString &outPakName,FString inPakName);
private:
	UFolderConfigure * FolderConfigure;
	TMap<FString, FString> PakTargetInfo;// <PakName, Target File Name>
};