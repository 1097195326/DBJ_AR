// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class DBJAR : ModuleRules
{
	public DBJAR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "InputCore",
            "JsonUtilities",
            "Json",
            "HTTP",
            "Networking",
            "Slate",
            "SlateCore",
            "UMG",
            "ImageDownload",
            "PakFile",
            "ProceduralMeshComponent",
            "AugmentedReality"
        });

            PublicDependencyModuleNames.AddRange(new string[] {"GCore",  "GXmlPlugins", "MsgCore", "DownloadTool","ImageMagick"});
	}
}
