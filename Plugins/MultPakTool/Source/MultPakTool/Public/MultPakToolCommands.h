// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MultPakToolStyle.h"

class FMultPakToolCommands : public TCommands<FMultPakToolCommands>
{
public:

	FMultPakToolCommands()
		: TCommands<FMultPakToolCommands>(TEXT("MultPakTool"), NSLOCTEXT("Contexts", "MultPakTool", "MultPakTool Plugin"), NAME_None, FMultPakToolStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};