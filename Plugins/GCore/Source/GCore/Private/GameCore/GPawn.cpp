//
//  GPawn.c
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#include "GCore.h"
#include "GPawn.h"

void AGPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	On_Init();
}
void AGPawn::BeginPlay()
{
	Super::BeginPlay();

	On_Start();
}
void AGPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	On_Tick(DeltaSeconds);
}
void AGPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	On_End();
}
