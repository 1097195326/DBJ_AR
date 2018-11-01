//
//  UserPawn.c
//  GameFrame_Index
//
//  Created by fafa on 2018/8/14.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//


#include "UserPawn.h"

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
    UE_LOG(LogTemp, Log, TEXT("zhx : user pawn init"));
    
}
void AUserPawn::On_Start()
{
	m_Controller = Cast<AUserController>(Controller);
	UE_LOG(LogTemp, Log, TEXT("zhx : user pawn start."));
}
void AUserPawn::On_Tick(float delta)
{
	
	if (m_ARIsSetUP && m_IsPressed)
	{
		if (m_SelectActor)
		{
			if (m_FingerNum == 1)
			{
				AActor * actor = nullptr;
				m_ScreenPosition = GetFingerPosition(1);
				if (IsHaveActorInScreenPosition(actor, m_ScreenPosition) && m_SelectActor == actor)
				{
					MoveSelecteARActor();
				}
				else
				{
					m_SelectActor = actor;
				}
			}else if (m_FingerNum == 2)
			{
				RotateSelectARActor();
			}
		}
		else
		{
			if (m_FingerNum == 1)
			{
				m_ScreenPosition = GetFingerPosition(1);
				if (!IsHaveActorInScreenPosition(m_SelectActor,m_ScreenPosition))
				{
					m_SelectActor = TryCreateARActor(m_ScreenPosition);
				}
			}
		}

	}

}
void AUserPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
#if PLATFORM_IOS
    PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AUserPawn::OnFingerTouchPressed);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AUserPawn::OnFingerTouchReleased);
#else
    PlayerInputComponent->BindAction("OneFingerTouch", EInputEvent::IE_Pressed, this, &AUserPawn::OneFingerPress);
	PlayerInputComponent->BindAction("OneFingerTouch", EInputEvent::IE_Released, this, &AUserPawn::OneFingerPress);

#endif
    
}

void AUserPawn::OnFingerTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    UE_LOG(LogTemp, Log, TEXT("zhx :: AUserPawn::OnFingerTouch"));

	switch (FingerIndex)
	{
		case ETouchIndex::Touch1:
		{
			m_IsPressed = true;
			m_FingerNum++;
			
		}break;
		case ETouchIndex::Touch2:
		{
			m_IsPressed = true;
			m_FingerNum++;
		}break;
		default:
			break;
	}
	
//    FHitResult HitResult;
//    ((AUserController*)Controller)->GetHitResultUnderFinger(FingerIndex, ECC_Visibility, true, HitResult);
    
//    ABehaviorTreeGameMode * GameMode = GetWorld()->GetAuthGameMode<ABehaviorTreeGameMode>();
//    GameMode->SetTargetLocation(HitResult.Location);

//    UE_LOG(LogTemp,Log,TEXT("zhx : hit location %f,%f"),HitResult.Location.X,HitResult.Location.Y);
    
}
void AUserPawn::OnFingerTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	m_FingerNum--;
	if (m_FingerNum <= 0)
	{
		m_IsPressed = false;
	}
}
void AUserPawn::OneFingerPress()
{
    UE_LOG(LogTemp, Log, TEXT("zhx :: AUserPawn::OneFingerPress"));
	m_IsPressed = true;

    FHitResult HitResult;
	if (m_Controller->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult))
	{

	}
    
}
void AUserPawn::oneFingerReleased()
{
	m_IsPressed = false;

}

FVector2D AUserPawn::GetFingerPosition(int _fingerNum)
{
	FVector2D SPostion;
	switch (_fingerNum)
	{
	case 1:
	{
		FVector2D oneFgLocation;
		bool pressed;
		m_Controller->GetInputTouchState(ETouchIndex::Touch1, oneFgLocation.X, oneFgLocation.Y, pressed);
		SPostion = oneFgLocation;
		
	}break;
	case 2:
	{
		FVector2D oneFgLocation, twoFgLocation;
		bool pressed;
		m_Controller->GetInputTouchState(ETouchIndex::Touch1, oneFgLocation.X, oneFgLocation.Y, pressed);
		m_Controller->GetInputTouchState(ETouchIndex::Touch2, twoFgLocation.X, twoFgLocation.Y, pressed);
		SPostion = (oneFgLocation + twoFgLocation) * 0.5;
	}break;
	default:
		break;
	}
	return SPostion;
}

bool AUserPawn::IsHaveActorInScreenPosition(AActor * _outActor, FVector2D _position)
{
	bool isHave = false;
	FHitResult hitResult;

	if (m_Controller->GetHitResultAtScreenPosition(_position, ECC_WorldStatic, false, hitResult))
	{
		isHave = true;
		_outActor = hitResult.GetActor();
	}
	//_outActor->GetName();

	return isHave;
}

AActor * AUserPawn::TryCreateARActor(FVector2D _screenPosition)
{
	AActor * actor = nullptr;


	return actor;
}

void AUserPawn::MoveSelecteARActor()
{
	
	if (m_SelectActor && m_SelectActor->IsValidLowLevel())
	{
		
	}

}

void AUserPawn::RotateSelectARActor()
{

}
//bool AUserPawn::GetPressedFinger()
//{
//	for (int i = 0; i < 10; i++)
//	{
//		ETouchIndex::Type index = ETouchIndex::Touch1 + i;
//		float _x, _y;
//		bool pressed = false;
//		m_Controller->GetInputTouchState(index, _x, _y, pressed);
//		if ()
//		{
//
//		}
//	}
//}