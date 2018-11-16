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
#include "GFileManager.h"
#include "UserActor.h"
#include "UserPawn.generated.h"


enum ActionState
{
    A_Nomal,
    A_Creating,
    A_Moveing,
};

UCLASS()
class DBJ_AR_API AUserPawn : public AGPawn
{
    GENERATED_BODY()
public:
    
    AUserPawn(const FObjectInitializer& ObjectInitializer);


	static AUserPawn * GetInstance();

    virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Tick(float delta) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//FVector2D  m_PreScreenPosition;
	//PC
	bool IsCRotate;
	bool IsCMove;

    void SelectGoods();
	void MoveGoods();
    void RotateGoods();
	void ChangeGoods();
	// mobile
	void OnFingerTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
    void OnFingerTouchMoved(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnFingerTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);
    
public:
   
    
    UFUNCTION(BlueprintImplementableEvent)
        void StartARSession();
    UFUNCTION(BlueprintImplementableEvent)
        void DrawPlnes();
    UFUNCTION(BlueprintImplementableEvent)
        bool GetTrackedGeometryTransform(FVector2D _scrrenPosition,FTransform & _transform);

    UFUNCTION(BlueprintCallable)
        FVector2D    GetFingerPosition(int _fingerNum);
    UFUNCTION(BlueprintCallable)
        bool IsHaveActorInScreenPosition(FVector2D _position);
    UFUNCTION(BlueprintCallable)
        AActor * TryCreateARActor(FVector2D _screenPosition);
	
	AActor * TryCreateARActor(GoodsData * _goodsData);
	void	TryDeleteARActor(AUserActor* _actor);
	
	void MergeTwoUserActor(AUserActor * one, AUserActor * two);

	void	DeleteSelectARActor();
	void	DeleteAllARActor();


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
		UStaticMeshComponent * m_SelectComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    TArray<TEnumAsByte<ETouchIndex::Type>>    m_PressedFingers;

private:
    AUserController * m_Controller;
    ActionState m_ActionState;

	static AUserPawn * m_self;
    
    GoodsData* m_CurrentGoodsData;

	float	m_RotateSpeed;

	TArray<AUserActor*>		m_AllUserActor;
};
