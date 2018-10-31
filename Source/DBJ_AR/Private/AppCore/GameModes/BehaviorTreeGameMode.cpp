//
//  BehaviorTreeGameMode.c
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#include "BehaviorTreeGameMode.h"
#include "UserController.h"


ABehaviorTreeGameMode::ABehaviorTreeGameMode()
{
//    DefaultPawnClass = AUserPawn::StaticClass();
//    PlayerControllerClass = AUserController::StaticClass();
    
}
void ABehaviorTreeGameMode::SetTargetLocation(FVector targetLocation)
{
    m_TargetLocation = targetLocation;
    
}
