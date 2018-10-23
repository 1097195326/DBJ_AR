// Fill out your copyright notice in the Description page of Project Settings.

#include "PackAction.h"
#include "Misc/MessageDialog.h"
#include "PlatformInfo.h"
#include "InstalledPlatformInfo.h"
#include "Interfaces/IProjectTargetPlatformEditorModule.h"
#include "IMainFrameModule.h"
#include "Classes/Settings/ProjectPackagingSettings.h"
#include "UnrealEdMisc.h"
#include "IUATHelperModule.h"
#include "EditorStyleSet.h"
#include "HAL/PlatformFilemanager.h"
#include "Engine.h"
#define LOCTEXT_NAMESPACE "FMultPakToolModule"



template <class FunctorType>
class PlatformFileFunctor : public IPlatformFile::FDirectoryVisitor	//GenericPlatformFile.h
{
public:

	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
	{
		return Functor(FilenameOrDirectory, bIsDirectory);
	}

	PlatformFileFunctor(FunctorType&& FunctorInstance)
		: Functor(MoveTemp(FunctorInstance))
	{
	}

private:
	FunctorType Functor;
};

template <class Functor>
PlatformFileFunctor<Functor> MakeDirectoryVisitor(Functor&& FunctorInstance)
{
	return PlatformFileFunctor<Functor>(MoveTemp(FunctorInstance));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Victory Get All Files
//      Optional File Extension Filter!!!  by Rama
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static FORCEINLINE bool GetFiles(const FString& FullPathOfBaseDir, TArray<FString>& FilenamesOut, bool Recursive = false, const FString& FilterByExtension = "")
{
	//Format File Extension, remove the "." if present
	const FString FileExt = FilterByExtension.Replace(TEXT("."), TEXT("")).ToLower();

	FString Str;
	auto FilenamesVisitor = MakeDirectoryVisitor(
		[&](const TCHAR* FilenameOrDirectory, bool bIsDirectory)
	{
		//Files
		if (!bIsDirectory)
		{
			//Filter by Extension
			if (FileExt != "")
			{
				Str = FPaths::GetCleanFilename(FilenameOrDirectory);

				//Filter by Extension
				if (FPaths::GetExtension(Str).ToLower() == FileExt)
				{
					if (Recursive)
					{
						FilenamesOut.Push(FilenameOrDirectory); //need whole path for recursive
					}
					else
					{
						FilenamesOut.Push(Str);
					}
				}
			}

			//Include All Filenames!
			else
			{
				//Just the Directory
				Str = FPaths::GetCleanFilename(FilenameOrDirectory);

				if (Recursive)
				{
					FilenamesOut.Push(FilenameOrDirectory); //need whole path for recursive
				}
				else
				{
					FilenamesOut.Push(Str);
				}
			}
		}
		return true;
	}
	);
	if (Recursive)
	{
		return FPlatformFileManager::Get().GetPlatformFile().IterateDirectoryRecursively(*FullPathOfBaseDir, FilenamesVisitor);
	}
	else
	{
		return FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*FullPathOfBaseDir, FilenamesVisitor);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Victory Get Directories
	//      Optional Search SubString!!!  by Rama
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Get Directories
static FORCEINLINE bool GetDirectories(const FString& FullPathOfBaseDir, TArray<FString>& DirsOut, bool Recursive = false, const FString& ContainsStr = "")
{
	FString Str;
	auto FilenamesVisitor = MakeDirectoryVisitor(
		[&](const TCHAR* FilenameOrDirectory, bool bIsDirectory)
	{
		if (bIsDirectory)
		{
			//Using a Contains Filter?
			if (ContainsStr != "")
			{
				Str = FPaths::GetCleanFilename(FilenameOrDirectory);

				//Only if Directory Contains Str
				if (Str.Contains(ContainsStr))
				{
					if (Recursive) DirsOut.Push(FilenameOrDirectory); //need whole path for recursive
					else DirsOut.Push(Str);
				}
			}

			//Get ALL Directories!
			else
			{
				//Just the Directory
				Str = FPaths::GetCleanFilename(FilenameOrDirectory);

				if (Recursive) DirsOut.Push(FilenameOrDirectory); //need whole path for recursive
				else DirsOut.Push(Str);
			}
		}
		return true;
	}
	);
	if (Recursive)
	{
		return FPlatformFileManager::Get().GetPlatformFile().IterateDirectoryRecursively(*FullPathOfBaseDir, FilenamesVisitor);
	}
	else
	{
		return FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*FullPathOfBaseDir, FilenamesVisitor);
	}
}

FPackAction::FPackAction()
{
	FolderConfigure = NewObject<UFolderConfigure>();
	FolderConfigure->AddToRoot();
	FolderConfigure->LoadConfigure();
}

FPackAction::~FPackAction()
{
	if (FolderConfigure)
	{
		FolderConfigure = nullptr;
	}
}

void FPackAction::DoPackage()
{
	if (FolderConfigure)
	{
		FolderConfigure->SaveConfigure();
	}
	//CookContent();

	if(GenerateCookTargetFile())
	{
		if(GeneratePakFiles())
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Pak successfully.")));
		}
	}
	else
	{
		UE_LOG(LogPakTool, Error, TEXT("GENEREATE TARGET FILE FAILED"));
	}
}

void FPackAction::SaveConfig()
{
	if (FolderConfigure)
	{
		FolderConfigure->SaveConfigure();
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("saved successfully.")));
	}
}

const TCHAR* GetUATCompilationFlags()
{
	// We never want to compile editor targets when invoking UAT in this context.
	// If we are installed or don't have a compiler, we must assume we have a precompiled UAT.
	return (FApp::GetEngineIsPromotedBuild() || FApp::IsEngineInstalled() || FPlatformMisc::IsDebuggerPresent())
		? TEXT("-nocompile -nocompileeditor")
		: TEXT("-nocompileeditor");
}

FString GetCookingOptionalParams()
{
	FString OptionalParams;
	const UProjectPackagingSettings* const PackagingSettings = GetDefault<UProjectPackagingSettings>();

	if (PackagingSettings->bSkipEditorContent)
	{
		OptionalParams += TEXT(" -SkipCookingEditorContent");
	}
	return OptionalParams;
}

void FPackAction::CookContent()
{
	const PlatformInfo::FPlatformInfo* const PlatformInfo = PlatformInfo::FindPlatformInfo("Windows");
	check(PlatformInfo);

	if (FInstalledPlatformInfo::Get().IsPlatformMissingRequiredFile(PlatformInfo->BinaryFolderName))
	{
		if (!FInstalledPlatformInfo::OpenInstallerOptions())
		{
			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("MissingPlatformFilesCook", "Missing required files to cook for this platform."));
		}
		return;
	}

	FString OptionalParams;

	if (!FModuleManager::LoadModuleChecked<IProjectTargetPlatformEditorModule>("ProjectTargetPlatformEditor").ShowUnsupportedTargetWarning(PlatformInfo->VanillaPlatformName))
	{
		return;
	}

	if (PlatformInfo->SDKStatus == PlatformInfo::EPlatformSDKStatus::NotInstalled)
	{
		IMainFrameModule& MainFrameModule = FModuleManager::GetModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
		MainFrameModule.BroadcastMainFrameSDKNotInstalled(PlatformInfo->TargetPlatformName.ToString(), PlatformInfo->SDKTutorial);
		return;
	}

	// Append any extra UAT flags specified for this platform flavor
	if (!PlatformInfo->UATCommandLine.IsEmpty())
	{
		OptionalParams += TEXT(" ");
		OptionalParams += PlatformInfo->UATCommandLine;
	}
	else
	{
		OptionalParams += TEXT(" -targetplatform=");
		OptionalParams += "Win64";//*PlatformInfo->TargetPlatformName.ToString();
	}

	OptionalParams += GetCookingOptionalParams();

	if (FApp::IsRunningDebug())
	{
		OptionalParams += TEXT(" -UseDebugParamForEditorExe");
	}

	FString ProjectPath = FPaths::IsProjectFilePathSet() ? FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath()) : FPaths::RootDir() / FApp::GetGameName() / FApp::GetGameName() + TEXT(".uproject");
	FString CommandLine = FString::Printf(TEXT("BuildCookRun %s%s -nop4 -project=\"%s\" -cook -skipstage -ue4exe=%s %s"),
		GetUATCompilationFlags(),
		FApp::IsEngineInstalled() ? TEXT(" -installed") : TEXT(""),
		*ProjectPath,
		*FUnrealEdMisc::Get().GetExecutableForCommandlets(),
		*OptionalParams
	);
	IUATHelperModule::Get().CreateUatTask(CommandLine, PlatformInfo->DisplayName, LOCTEXT("CookingContentTaskName", "Cooking content"), LOCTEXT("CookingTaskName", "Cooking"), FEditorStyle::GetBrush(TEXT("MainFrame.CookContent")));
}

bool FPackAction::GeneratePakName(FString &outPakName, FString inPakName)
{
	if (!inPakName.Contains(FolderConfigure->PakRootDir.Path))
	{
		return false;
	}
	inPakName.Split(FolderConfigure->PakRootDir.Path,nullptr,&outPakName);
	if (outPakName.Len()==0)
	{
		return false;
	}
	if (outPakName[0]=='/' ||outPakName[0]=='\\')
	{
		outPakName.RemoveAt(0);
	}
	outPakName.ReplaceInline(TEXT("/"), TEXT("___"));
	outPakName.ReplaceInline(TEXT("\\"), TEXT("___"));
	return true;
}

bool FPackAction::GenerateCookTargetFile()
{
	bool ret = false;

	if (FolderConfigure == nullptr)
	{
		return false;
	}

	struct _Helper {

		FString pakName;
		TArray<FString> fileNames;
	};

	TArray<_Helper> tmpHelpers;
	for (FPakHelper &helper : FolderConfigure->PakList)
	{
		_Helper tmp;
		if (GeneratePakName(tmp.pakName, helper.SourceFolder.Path))
		{
			GetFiles(helper.SourceFolder.Path, tmp.fileNames, true);
			tmpHelpers.Add(tmp);
		}
		else
		{
			UE_LOG(LogPakTool, Error, TEXT("CANNOT PARSE Pak File Name!! %s"), *helper.SourceFolder.Path);
		}
	}
	
	FString tmpFileList;
	for (_Helper &elm : tmpHelpers)
	{
		tmpFileList.Reset();
		for (FString &fileName : elm.fileNames)
		{
			tmpFileList.Append(fileName).Append("\n");
		}
		if (elm.fileNames.Num())
		{
			FString txtFile = FPaths::Combine(FolderConfigure->PakSaveTo.Path, elm.pakName).Append(".txt");
			FFileHelper::SaveStringToFile(tmpFileList, *txtFile);
			PakTargetInfo.Add(elm.pakName, txtFile);
			UE_LOG(LogPakTool, Log, TEXT("generate pak ...\n file number :%d, target file :%s"), elm.fileNames.Num(), *txtFile);
			ret = true;
		}
		else
		{
			UE_LOG(LogPakTool, Warning, TEXT("generate pak ...\n pak file :%s, no file!"), *elm.pakName);
		}
	}

	return ret;
}



bool FPackAction::GeneratePakFiles()
{
	TArray<FString> TaskList;
	bool ret = false;
	for (auto &iter : PakTargetInfo)
	{
		TaskList.Add(FString::Printf(TEXT(" %s/%s.pak -Create=%s -compress"), *FolderConfigure->PakSaveTo.Path, *iter.Key, *iter.Value));
	}
	FString pakExePath = FString::Printf(TEXT("%sBinaries/Win64/UnrealPak.exe"), *FPaths::ConvertRelativePathToFull(FPaths::EngineDir()));
	if (TaskList.Num() > 0)
	{
		ret = true;
		for (FString &elem : TaskList)
		{
			FProcHandle handle = FPlatformProcess::CreateProc(*pakExePath, *elem, false, false, true, nullptr, 0, nullptr, nullptr);
			if (handle.IsValid())
			{
				UE_LOG(LogPakTool, Log, TEXT("execute script : %s"), *elem);
				FPlatformProcess::WaitForProc(handle);
			}
			else
			{
				UE_LOG(LogPakTool, Error, TEXT("Create Progress failed : %s"), *elem);
			}
		}
	}

	return ret;
}
