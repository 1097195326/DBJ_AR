// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MultPakToolCommands.h"

#define LOCTEXT_NAMESPACE "FMultPakToolModule"

void FMultPakToolCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "MultPakTool", "Bring up MultPakTool window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
