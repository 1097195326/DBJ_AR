// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "ResManager.h"

DECLARE_LOG_CATEGORY_EXTERN(ResLog, Log, All);

class FXRResourceModule
	: public IModuleInterface
{
public:

	// IModuleInterface interface

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	XRRESOURCE_API static FXRResourceModule& Get();
	inline UXRResourceManager* GetResourceManager()
	{
		return ResourceManager;
	}

private:
	static FXRResourceModule* Singleton;
	UXRResourceManager* ResourceManager;
};
