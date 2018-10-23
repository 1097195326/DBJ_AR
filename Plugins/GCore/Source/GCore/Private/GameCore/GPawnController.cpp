//
//  GPawnController.c
//  GameFrame
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#include "GCore.h"
#include "GPawnController.h"


void AGPawnController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	On_Init();
}
void AGPawnController::BeginPlay()
{
	Super::BeginPlay();

	On_Start();
}
void AGPawnController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	On_Tick(DeltaSeconds);
}
void AGPawnController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	On_End();
}