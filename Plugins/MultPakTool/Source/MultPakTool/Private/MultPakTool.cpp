// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MultPakTool.h"
#include "MultPakToolStyle.h"
#include "MultPakToolCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "PackAction.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Settings/ProjectPackagingSettings.h"
DEFINE_LOG_CATEGORY(LogPakTool)

static const FName MultPakToolTabName(TEXT("SplitTool"));

#define LOCTEXT_NAMESPACE "FMultPakToolModule"

void FMultPakToolModule::StartupModule()
{
	PackAction = new FPackAction;
	ConfigDetailView.Reset();
	FMultPakToolStyle::Initialize();
	FMultPakToolStyle::ReloadTextures();

	FMultPakToolCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMultPakToolCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMultPakToolModule::PluginButtonClicked),
		FCanExecuteAction());

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMultPakToolModule::AddMenuExtension));
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMultPakToolModule::AddToolbarExtension));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MultPakToolTabName, FOnSpawnTab::CreateRaw(this, &FMultPakToolModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMultPakToolTabTitle", "SplitTool"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FMultPakToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FMultPakToolStyle::Shutdown();

	FMultPakToolCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MultPakToolTabName);

	delete PackAction;
	PackAction = NULL;
}

TSharedRef<SDockTab> FMultPakToolModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	//FText WidgetText = FText::Format(
	//	LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
	//	FText::FromString(TEXT("FMultPakToolModule::OnSpawnPluginTab")),
	//	FText::FromString(TEXT("MultPakTool.cpp"))
	//	);

	FDetailsViewArgs detailsArgs(false, false, false, FDetailsViewArgs::HideNameArea);
	FPropertyEditorModule &propertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	ConfigDetailView = propertyEditorModule.CreateDetailView(detailsArgs);
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			ConfigDetailView.ToSharedRef()
		]
		]
	+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10)
		[
			SNew(SButton)
			.Text(LOCTEXT("SaveConfig", "Save Config"))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.OnClicked(FOnClicked::CreateRaw(this, &FMultPakToolModule::OnClickSaveConfig))
		]

	+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10)
		[
			SNew(SButton)
			.Text(LOCTEXT("ExportPackage", "Export Package"))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.OnClicked(FOnClicked::CreateRaw(this, &FMultPakToolModule::OnClickDoPack))
		]

	+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10)
		[
			SNew(SButton)
			.Text(LOCTEXT("MiniPak", "Configure For Mini pak"))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.OnClicked(FOnClicked::CreateRaw(this, &FMultPakToolModule::OnConfigMini))
		]

	+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10)
		[
			SNew(SButton)
			.Text(LOCTEXT("FullPak", "Configure Full pak (without never cook)"))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.OnClicked(FOnClicked::CreateRaw(this, &FMultPakToolModule::OnConfigFull))
		]

		]

		];
}

FReply FMultPakToolModule::OnClickSaveConfig()
{
	PackAction->SaveConfig();
	return FReply::Handled();
}

FReply FMultPakToolModule::OnClickDoPack()
{
	if (PackAction)
	{
		if (PackAction->GetConfigure()->PakRootDir.Path.Len() == 0)
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Must point Root Directory")));
		}
		else
		{
			PackAction->DoPackage();
		}
	}
	return FReply::Handled();
}



FReply FMultPakToolModule::OnConfigMini()
{
	TArray<FString> minipak;
	PackAction->GetConfigure()->GetMiniPakPaths(minipak);
	UProjectPackagingSettings* PackagingSettings = Cast<UProjectPackagingSettings>(UProjectPackagingSettings::StaticClass()->GetDefaultObject());

	for (const FString &elemPath : minipak)
	{
		bool isHave = false;
		for (FDirectoryPath &tar : PackagingSettings->DirectoriesToNeverCook)
		{
			isHave = (tar.Path == elemPath);
			if (isHave)
			{
				break;
			}
		}
		if (isHave)
		{
			continue;
		}
		FDirectoryPath dirPath; dirPath.Path = elemPath;
		PackagingSettings->DirectoriesToNeverCook.Add(dirPath);
	}

	for (const FDirectoryPath &elemPath : PackAction->GetConfigure()->NeverCook)
	{
		bool isHave = false;
		for (FDirectoryPath &tar : PackagingSettings->DirectoriesToNeverCook)
		{
			isHave = (tar.Path == elemPath.Path);
			if (isHave)
			{
				break;
			}
		}
		if (isHave)
		{
			continue;
		}

		PackagingSettings->DirectoriesToNeverCook.Add(elemPath);
		
	}
	PackagingSettings->SaveConfig();

	return FReply::Handled();
}

FReply FMultPakToolModule::OnConfigFull()
{
	TArray<FString> minipak;
	PackAction->GetConfigure()->GetMiniPakPaths(minipak);
	UProjectPackagingSettings* PackagingSettings = Cast<UProjectPackagingSettings>(UProjectPackagingSettings::StaticClass()->GetDefaultObject());

	for (const FString &elemPath : minipak)
	{
		bool isHave = false;
		for (int i = 0; i < PackagingSettings->DirectoriesToNeverCook.Num(); ++i)
		{
			isHave = (PackagingSettings->DirectoriesToNeverCook[i].Path == elemPath);
			if (isHave)
			{
				PackagingSettings->DirectoriesToNeverCook.RemoveAt(i);
				break;
			}
		}
	}

	for (const FDirectoryPath &elemPath : PackAction->GetConfigure()->NeverCook)
	{
		bool isHave = false;
		for (FDirectoryPath &tar : PackagingSettings->DirectoriesToNeverCook)
		{
			isHave = (tar.Path == elemPath.Path);
			if (isHave)
			{
				break;
			}
		}
		if (isHave)
		{
			continue;
		}

		PackagingSettings->DirectoriesToNeverCook.Add(elemPath);

	}
	PackagingSettings->SaveConfig();

	return FReply::Handled();
}

void FMultPakToolModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(MultPakToolTabName);
	ConfigDetailView->SetObject(PackAction->GetConfigure(), true);
}

void FMultPakToolModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMultPakToolCommands::Get().OpenPluginWindow);
}

void FMultPakToolModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FMultPakToolCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMultPakToolModule, MultPakTool)