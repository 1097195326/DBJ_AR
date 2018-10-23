//
//  UserPawn.c
//  GameFrame_Index
//
//  Created by fafa on 2018/8/14.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//


#include "UserPawn.h"
#include "UserPawnController.h"
#include "Engine/World.h"
#include "BehaviorTreeGameMode.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"

AUserPawn::AUserPawn(const FObjectInitializer& ObjectInitializer)
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    
    m_Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
    m_Movement->SetUpdatedComponent(RootComponent);
    


    m_CameraArmSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
    m_CameraArmSpring->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    m_CameraArmSpring->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-30.0f, 0.0f, 0.0f));
    m_CameraArmSpring->TargetArmLength = 30.f;
    m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
    m_Camera->AttachToComponent(m_CameraArmSpring, FAttachmentTransformRules::KeepRelativeTransform,USpringArmComponent::SocketName);

    ////控制默认玩家
    //AutoPossessPlayer = EAutoReceiveInput::Player0;
}
void AUserPawn::On_Init()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : user pawn create func2"));
}
UPawnMovementComponent* AUserPawn::GetMovementComponent() const
{
    return m_Movement;
}
void AUserPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
#if PLATFORM_IOS
    PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AUserPawn::OnFingerTouch);
#else
    PlayerInputComponent->BindAction("OneFingerTouch", EInputEvent::IE_Pressed, this, &AUserPawn::OneFingerPress);
    PlayerInputComponent->BindAxis("LeftAndRight", this, &AUserPawn::LeftAndRight);
    PlayerInputComponent->BindAxis("UpAndDown", this, &AUserPawn::UpAndDown);

#endif
    
}
void AUserPawn::OnFingerTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    UE_LOG(LogTemp, Log, TEXT("zhx :: AUserPawn::OnFingerTouch"));
    
    FHitResult HitResult;
    ((AUserPawnController*)Controller)->GetHitResultUnderFinger(FingerIndex, ECC_Visibility, true, HitResult);
    
//    ABehaviorTreeGameMode * GameMode = GetWorld()->GetAuthGameMode<ABehaviorTreeGameMode>();
//    GameMode->SetTargetLocation(HitResult.Location);
    
    UE_LOG(LogTemp,Log,TEXT("zhx : hit location %f,%f"),Location.X,Location.Y);
//    UE_LOG(LogTemp,Log,TEXT("zhx : hit location %f,%f"),HitResult.Location.X,HitResult.Location.Y);
    
}
void AUserPawn::OneFingerPress()
{
    UE_LOG(LogTemp, Log, TEXT("zhx :: AUserPawn::OneFingerPress"));

    FHitResult HitResult;
    ((AUserPawnController*)Controller)->
    GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
    
}
void AUserPawn::LeftAndRight(float scale)
{
    if (m_Movement && m_Movement->UpdatedComponent == RootComponent)
    {
        m_Movement->AddInputVector(GetActorRightVector() * scale);
        //UE_LOG(LogTemp, Log, TEXT("zhx : acale %f"), scale);
    }
    
}
void AUserPawn::UpAndDown(float scale)
{
    if (m_Movement && m_Movement->UpdatedComponent == RootComponent)
    {
        m_Movement->AddInputVector(GetActorForwardVector() * scale);
    }
}
