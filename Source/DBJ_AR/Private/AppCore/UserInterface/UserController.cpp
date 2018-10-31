//
//  UserController.c
//  GameFrame_Index
//
//  Created by fafa on 2018/8/14.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#include "UserController.h"

void AUserController::On_Init()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : AUserController::On_Init"));
    
}
void AUserController::On_Start()
{
    UE_LOG(LogTemp,Log,TEXT("zhx : user controller start"));
    StartARSession();
    
}
void AUserController::On_Tick(float DeltaSeconds)
{
    
}
void AUserController::On_Delete()
{
    
}
bool AUserController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : user controller input touch : "));
    
    switch(Type)
    {
        case ETouchType::Began:
            break;
        case ETouchType::Moved:
            break;
        case ETouchType::Stationary:
            break;
        case ETouchType::Ended:
            break;
    }
    
    return Super::InputTouch(Handle,Type,TouchLocation,Force,DeviceTimestamp,TouchpadIndex);
    
}
