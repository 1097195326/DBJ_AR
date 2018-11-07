// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class XRResource : ModuleRules
{
	public XRResource(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        DynamicallyLoadedModuleNames.AddRange(
           new string[] {

               //"DesktopPlatform",
           }
       );

        PublicDependencyModuleNames.AddRange(
            new string[]
			{
                "PakFile",
                "XmlParser",
            }
        );

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
                "InputCore",
				"RHI",
				"ShaderCore",
                "HTTP",
                "Json",
                "Slate",
                "SlateCore"
			}
        );

		PrivateIncludePathModuleNames.AddRange(
			new string[] {
			}
		);
  
        PrivateIncludePaths.AddRange(
			new string[] {
                "XRResource/Private",
            }
		);

    }
}
