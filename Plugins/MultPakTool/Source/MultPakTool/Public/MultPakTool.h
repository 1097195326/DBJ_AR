// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPakTool, Log, All);

class FToolBarBuilder;
class FMenuBuilder;

class FMultPakToolModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	FReply OnClickSaveConfig();
	FReply OnClickDoPack();
	FReply OnConfigMini();
	FReply OnConfigFull();


private:
	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedPtr<class IDetailsView> ConfigDetailView;

	class FPackAction *PackAction;
};