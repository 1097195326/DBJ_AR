//
//  UserController.c
//  GameFrame_Index
//
//  Created by fafa on 2018/8/14.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#include "UserController.h"
#include "SharingFunctions.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "UserPlaneActor.h"

AUserController * AUserController::GetInstance()
{
	return Cast<AUserController>(UGameplayStatics::GetPlayerController(GWorld, 0));
}
void AUserController::On_Init()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : AUserController::On_Init"));
	

}
void AUserController::On_Start()
{
    UE_LOG(LogTemp,Log,TEXT("zhx : user controller start"));
    
}
void AUserController::On_Tick(float DeltaSeconds)
{
    
}
void AUserController::On_Delete()
{
    
}
//bool AUserController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
//{
//    //UE_LOG(LogTemp, Log, TEXT("zhx : user controller input touch : "));
//    
//    switch(Type)
//    {
//        case ETouchType::Began:
//            break;
//        case ETouchType::Moved:
//            break;
//        case ETouchType::Stationary:
//            break;
//        case ETouchType::Ended:
//            break;
//    }
//    
//    return Super::InputTouch(Handle,Type,TouchLocation,Force,DeviceTimestamp,TouchpadIndex);
//    
//}

void AUserController::ScreenShot_Callback(FScreenshotImage Image)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : user controller make screen shot call back"));
	TArray<AActor *> allPlaneActor;
	UGameplayStatics::GetAllActorsOfClass(this, AUserPlaneActor::StaticClass(), allPlaneActor);
	for (int i = 0; i < allPlaneActor.Num(); i++)
	{
		AUserPlaneActor * actor = (AUserPlaneActor *)allPlaneActor[i];
		actor->StartDraw();
	}
	USharingFunctions::Share("", "AR", "www.dabanjia.com", Image);
	
}
void AUserController::MakeScreenShot()
{
	TArray<AActor *> allPlaneActor;
	UGameplayStatics::GetAllActorsOfClass(this, AUserPlaneActor::StaticClass(), allPlaneActor);
	for (int i = 0; i < allPlaneActor.Num(); i++)
	{
		AUserPlaneActor * actor = (AUserPlaneActor *)allPlaneActor[i];
		actor->StopDraw();
	}
	GEngine->GameViewport->ConsoleCommand(TEXT("Shot"));
}
