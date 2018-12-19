// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "XRResourceModule.h"
#include "SlateOptMacros.h"

DEFINE_LOG_CATEGORY(ResLog);

FXRResourceModule* FXRResourceModule::Singleton = NULL;

void FXRResourceModule::StartupModule()
{
	Singleton = this;
	if (!ResourceManager)
	{
		ResourceManager = NewObject<UXRResourceManager>();
		ResourceManager->AddToRoot();
		ResourceManager->Init();
	}
}

void FXRResourceModule::ShutdownModule()
{
// 	if (ResourceManager)
// 	{
// 		ResourceManager->RemoveFromRoot();
// 	}
}

XRRESOURCE_API FXRResourceModule& FXRResourceModule::Get()
{
	if (Singleton == NULL)
	{
		check(IsInGameThread());
		FModuleManager::LoadModuleChecked<FXRResourceModule>("XRResource");
	}
	check(Singleton != NULL);
	return *Singleton;
}

IMPLEMENT_MODULE(FXRResourceModule, XRResource);
