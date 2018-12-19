// Fill out your copyright notice in the Description page of Project Settings.

#include "FolderConfigure.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "MultPakTool.h"
template<typename InStructType>
void SaveUStructArrayToJsonFile(const FString inPath,const TArray<InStructType>& inStructs)
{
	FString arrayJsonString;
	FString objectJsonString;
	for (const InStructType &item : inStructs)
	{
		if (FJsonObjectConverter::UStructToJsonObjectString(item, objectJsonString, 0, 0))
		{
			arrayJsonString.Append(objectJsonString + ",\n");
		}
	}
	FFileHelper::SaveStringToFile("[\n" + arrayJsonString + "\n]", *inPath);
}

// 加载jsonArray到TArray<UStruct>.
template<typename InStructType>
void _LoadJsonArrayFileToUStructArray(const FString inPath, TArray<InStructType>& outUStruct)
{
	if (!FPaths::FileExists(inPath))
	{
		UE_LOG(LogPakTool, Warning, TEXT("file descriptor is not exists: %s"), *inPath);
		return;
	}

	outUStruct.Empty();

	FString jsonArrayString;
	FFileHelper::LoadFileToString(jsonArrayString, *inPath);


	if (!FJsonObjectConverter::JsonArrayStringToUStruct(jsonArrayString, &outUStruct, 0, 0))
	{
		UE_LOG(LogPakTool, Warning, TEXT("properties matched but failed to deserialize."));
		return;
	}
	UE_LOG(LogPakTool, Log, TEXT("has read %d records from %s"), outUStruct.Num(), *inPath);
}


// Struct to json file
template<typename InStructType>
void _SaveUStructToJsonFile(const FString inFolder, const InStructType& InStruct)
{
	FString objectJsonString;
	FJsonObjectConverter::UStructToJsonObjectString(InStruct, objectJsonString, 0, 0);
	FFileHelper::SaveStringToFile(objectJsonString, *inFolder);
}

// json file to struct
template<typename InStructType>
bool _LoadJsonFileToUStruct(const FString &inFolder, InStructType& outStruct)
{
	if (!FPaths::FileExists(inFolder))
	{
		UE_LOG(LogPakTool, Warning, TEXT("file is not exists: %s"), *inFolder);
		return false;
	}

	FString jsonObjectString;
	FFileHelper::LoadFileToString(jsonObjectString, *inFolder);

	if (!FJsonObjectConverter::JsonObjectStringToUStruct(jsonObjectString, &outStruct, 0, 0))
	{
		UE_LOG(LogPakTool, Warning, TEXT("properties matched but failed to deserialize."));
		return false;
	}
	UE_LOG(LogPakTool, Log, TEXT("load json file %s"), *inFolder);

	return true;
}


void UFolderConfigure::SaveConfigure()
{
	FSaveConfigHelper helper;
	helper.PakSaveTo = PakSaveTo;
	helper.PakList = PakList;
	helper.PakRootDir = PakRootDir;
	helper.NeverCook = NeverCook;
	_SaveUStructToJsonFile(FPaths::Combine(FPaths::GameConfigDir(), TEXT("pakConfig.ini")), helper);
}

void UFolderConfigure::LoadConfigure()
{
	FSaveConfigHelper helper;
	_LoadJsonFileToUStruct(FPaths::Combine(FPaths::GameConfigDir(), TEXT("pakConfig.ini")), helper);
	PakList = helper.PakList;
	PakSaveTo = helper.PakSaveTo;
	PakRootDir = helper.PakRootDir;
	NeverCook = helper.NeverCook;
}

void UFolderConfigure::GetMiniPakPaths(TArray<FString> &outPath)
{
	FString outPakName;
	for (const FPakHelper &elem : PakList)
	{
		if (!elem.SourceFolder.Path.Contains(PakRootDir.Path))
		{
			continue;
		}
		elem.SourceFolder.Path.Split(PakRootDir.Path, nullptr, &outPakName);
		if (outPakName.Len() == 0)
		{
			continue;
		}
		if (outPakName[0] == '/' || outPakName[0] == '\\')
		{
			outPakName.RemoveAt(0);
		}
		outPakName.ReplaceInline(TEXT("\\"), TEXT("/"));
		outPath.Add(outPakName);
	}
}
