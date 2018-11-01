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
	virtual void On_Start() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//PC
	void OneFingerPress();
	// mobile
	void OnFingerTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	
public:
   
	//
	UFUNCTION(BlueprintImplementableEvent)
		void StartARSession();
	UFUNCTION(BlueprintImplementableEvent)
		FTransform GetTrackedGeometryTransform(FVector2D _scrrenPosition);

	UFUNCTION(BlueprintCallable)
		FVector2D	GetFingerPosition(int _fingerNum);
	UFUNCTION(BlueprintCallable)
		bool IsHaveActorInScreenPosition(AActor * _outActor, FVector2D _position);
	UFUNCTION(BlueprintCallable)
		AActor * CreateARActor();
	UFUNCTION(BlueprintCallable)
		void MoveSelecteARActor(FVector _location);
	UFUNCTION(BlueprintCallable)
		void RotateSelectARActor(FRotator _rotation);


public:
	UPROPERTY(VisibleAnywhere)
		UCameraComponent * m_Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool  m_ARIsSetUP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool  m_IsPressed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32  m_FingerNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		AActor * m_SelectActor;

};
