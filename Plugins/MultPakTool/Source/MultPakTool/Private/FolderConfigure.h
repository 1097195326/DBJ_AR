// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"

#include "FolderConfigure.generated.h"
/** package source config , 
	PakName : the package file name, 
	FolderList : pointed the folder will be package into the package.
*/
USTRUCT(BlueprintType)
struct FPakHelper
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category=Path, meta=(DisplayName="Folder will be package into Pak File"))
	FDirectoryPath SourceFolder;
};

USTRUCT()
struct FSaveConfigHelper
{
	GENERATED_BODY()

	UPROPERTY()
	FDirectoryPath PakSaveTo;
	
	UPROPERTY()
	FDirectoryPath PakRootDir;
	
	UPROPERTY()
	TArray<FPakHelper> PakList;

	UPROPERTY()
	TArray<FDirectoryPath> NeverCook;
};

UCLASS(config = Game)
class UFolderConfigure : public UObject
{
	GENERATED_BODY()
public:
	void SaveConfigure();
	void LoadConfigure();
	void GetMiniPakPaths(TArray<FString> &outPath);

	UPROPERTY(EditAnywhere, meta=(DisplayName="all pak file will be saved to this directory."))
	FDirectoryPath PakSaveTo;

	//"file root directory, play a decisive role about the mount target path, very important!!!."
	UPROPERTY(EditAnywhere, meta = (DisplayName = "RootDir"))
	FDirectoryPath PakRootDir;

	// package list.
	UPROPERTY(EditAnywhere,Config)
	TArray<FPakHelper> PakList;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Never Cook", RelativeToGameContentDir))
	TArray<FDirectoryPath> NeverCook;
};
