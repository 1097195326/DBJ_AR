// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class ImageMagick : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }
    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }
    public ImageMagick(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        // Startard Module Dependencies
        PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "InputCore", "ImageMagick"});
        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "Slate", "SlateCore", "ImageWrapper", "RenderCore" });
     
        string imagemagickPath = Path.Combine(ThirdPartyPath, "imagemagick");
        string LibPath = "";
        bool isdebug = Target.Configuration == UnrealTargetConfiguration.Debug && Target.bDebugBuildsActuallyUseDebugCRT;
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicIncludePaths.AddRange(new string[] { Path.Combine(imagemagickPath, "Include","Win64") });
            
            LibPath = Path.Combine(imagemagickPath, "Libraries", "Win64");
            PublicLibraryPaths.Add(LibPath);

            PublicAdditionalLibraries.Add("CORE_RL_Magick++_.lib");
            PublicAdditionalLibraries.Add("CORE_RL_MagickCore_.lib");
            PublicAdditionalLibraries.Add("CORE_RL_MagickWand_.lib");
            PublicAdditionalLibraries.Add("OpenFileDlgLib.lib");
        }
        else if (Target.Platform == UnrealTargetPlatform.Win32)
        {
            PublicIncludePaths.AddRange(new string[] { Path.Combine(imagemagickPath, "Include","Win64") });
            LibPath = Path.Combine(imagemagickPath, "Libraries", "Win32");
            PublicLibraryPaths.Add(LibPath);

            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "CORE_RL_Magick++_.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "CORE_RL_MagickCore_.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "CORE_RL_MagickWand_.lib"));
            
        }
        else if(Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicIncludePaths.AddRange(new string[] { Path.Combine(imagemagickPath, "Include","Mac") });
            LibPath = Path.Combine(imagemagickPath, "Libraries", "Mac");
            PublicLibraryPaths.Add(LibPath);

            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libMagick++-7.Q16HDRI.a"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libMagickWand-7.Q16HDRI.a"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libMagickCore-7.Q16HDRI.a"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libjpeg.a"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libOpenFileDialogLib.a"));
        }
        else if(Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicLibraryPaths.Add("/usr/lib");
            
            PublicAdditionalLibraries.Add("/usr/lib/libxml2.2.dylib");
            PublicAdditionalLibraries.Add("/usr/lib/libz.dylib");
            
            PublicIncludePaths.AddRange(new string[] { Path.Combine(imagemagickPath, "Include","iOS"),Path.Combine(imagemagickPath, "Include","iOS","MagickCore"),Path.Combine(imagemagickPath, "Include","iOS","jpeg"),Path.Combine(imagemagickPath, "Include","iOS","MagickWand") ,Path.Combine(imagemagickPath, "Include","iOS","MagickWand") });
            
            
            LibPath = Path.Combine(imagemagickPath, "Libraries", "iOS");
            PublicLibraryPaths.Add(LibPath);
            
            //PublicAdditionalLibraries.Add(Path.Combine(LibPath, "HMImagePickerManager.a"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libjpeg.a"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libMagick++.a"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libMagickCore.a"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libMagickWand.a"));
            //PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libpng.a"));
            
            PublicFrameworks.AddRange(
            new string[]
            {
                "UIKIT",
                "Foundation"
            }
            );
        }

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.Add("Launch");
        }

    }
}
