//
//  UserPawn.h
//  GameFrame_Index
//
//  Created by fafa on 2018/8/14.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "GPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "UserPawn.generated.h"


UCLASS()
class DBJ_AR_API AUserPawn : public AGPawn
{
    GENERATED_BODY()
public:
    AUserPawn(const FObjectInitializer& ObjectInitializer);

    virtual void On_Init() override;
private:
    USpringArmComponent * m_CameraArmSpring;
    UCameraComponent * m_Camera;

    UPROPERTY(VisibleAnywhere)
    UFloatingPawnMovement * m_Movement;
public:
    
    virtual UPawnMovementComponent* GetMovementComponent() const override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    //PC
    void OneFingerPress();
    void LeftAndRight(float scale);
    void UpAndDown(float scale);
    // mobile
    void OnFingerTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
};
