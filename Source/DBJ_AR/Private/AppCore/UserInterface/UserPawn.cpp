//
//  UserPawn.c
//  GameFrame_Index
//
//  Created by fafa on 2018/8/14.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//


#include "UserPawn.h"
#include "UserController.h"
#include "Engine/World.h"
#include "BehaviorTreeGameMode.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"

AUserPawn::AUserPawn(const FObjectInitializer& ObjectInitializer)
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    
    m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
    m_Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    
    ////控制默认玩家
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}
void AUserPawn::On_Init()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : user pawn create func2"));
    
}
void AUserPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
#if PLATFORM_IOS
    PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AUserPawn::OnFingerTouch);
#else
    PlayerInputComponent->BindAction("OneFingerTouch", EInputEvent::IE_Pressed, this, &AUserPawn::OneFingerPress);

#endif
    
}
void AUserPawn::OnFingerTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    UE_LOG(LogTemp, Log, TEXT("zhx :: AUserPawn::OnFingerTouch"));
    
//    FHitResult HitResult;
//    ((AUserController*)Controller)->GetHitResultUnderFinger(FingerIndex, ECC_Visibility, true, HitResult);
    
//    ABehaviorTreeGameMode * GameMode = GetWorld()->GetAuthGameMode<ABehaviorTreeGameMode>();
//    GameMode->SetTargetLocation(HitResult.Location);
    
    UE_LOG(LogTemp,Log,TEXT("zhx : hit location %f,%f"),Location.X,Location.Y);
//    UE_LOG(LogTemp,Log,TEXT("zhx : hit location %f,%f"),HitResult.Location.X,HitResult.Location.Y);
    
}
void AUserPawn::OneFingerPress()
{
    UE_LOG(LogTemp, Log, TEXT("zhx :: AUserPawn::OneFingerPress"));

    FHitResult HitResult;
    ((AUserController*)Controller)->
    GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
    
}
