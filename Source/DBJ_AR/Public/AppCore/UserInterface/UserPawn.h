//
//  UserPawn.h
//  GameFrame_Index
//
//  Created by fafa on 2018/8/14.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "GPawn.h"
#include "UserController.h"
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
	virtual void On_Tick(float delta) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//PC
	void OneFingerPress();
	void oneFingerReleased();
	// mobile
	void OnFingerTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnFingerTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);

public:
   
	//
	UFUNCTION(BlueprintImplementableEvent)
		void StartARSession();
	UFUNCTION(BlueprintImplementableEvent)
		bool GetTrackedGeometryTransform(FVector2D _scrrenPosition,FTransform & _transform);

	UFUNCTION(BlueprintCallable)
		FVector2D	GetFingerPosition(int _fingerNum);
	UFUNCTION(BlueprintCallable)
		bool IsHaveActorInScreenPosition(AActor * _outActor, FVector2D _position);
	UFUNCTION(BlueprintCallable)
		AActor * TryCreateARActor(FVector2D _screenPosition);
	UFUNCTION(BlueprintCallable)
		void MoveSelecteARActor();
	UFUNCTION(BlueprintCallable)
		void RotateSelectARActor();
	/*UFUNCTION(BlueprintCallable)
		bool GetPressedFinger();*/

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
		FVector2D m_ScreenPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		AActor * m_SelectActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<ETouchIndex::Type>>	m_PressedFingers;

private:
	AUserController * m_Controller;
};
