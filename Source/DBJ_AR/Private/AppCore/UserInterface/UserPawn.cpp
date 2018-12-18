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
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "RuntimeRDataManager.h"


AUserPawn * AUserPawn::m_self = nullptr;

AUserPawn * AUserPawn::GetInstance()
{
	return m_self;
}
AUserPawn::AUserPawn(const FObjectInitializer& ObjectInitializer)
{
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 3002, this, &AUserPawn::ApplicationWillEnterBackground);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 3003, this, &AUserPawn::ApplicationWillEnterBackground);
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    
    m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
    m_Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    
    m_ARIsSetUP = false;
    m_IsPressed  = false;
    m_FingerNum = 0;
    m_SelectActor = nullptr;
    ////控制默认玩家
    AutoPossessPlayer = EAutoReceiveInput::Player0;
	m_self = this;

	m_RotateSpeed = 1.f;
}
void AUserPawn::On_Init()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : user pawn init"));
    
}
void AUserPawn::On_Start()
{
    //StartARSession();
    m_Controller = Cast<AUserController>(Controller);
	UE_LOG(LogTemp, Log, TEXT("zhx : user pawn start."));
}
void AUserPawn::On_Tick(float delta)
{
//    if(m_ARIsSetUP)
//    {
//        DrawPlnes();
//    }
#if PLATFORM_WINDOWS
	if (IsCMove)
	{
		MoveSelecteARActor();
	}else if (IsCRotate)
	{
		RotateSelectARActor();
	}

#endif

}
void AUserPawn::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 3002, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 3003, this);
}
void AUserPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
#if PLATFORM_IOS
    PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AUserPawn::OnFingerTouchPressed);
    PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AUserPawn::OnFingerTouchMoved);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AUserPawn::OnFingerTouchReleased);
#else
    PlayerInputComponent->BindAction("SelectGoods", EInputEvent::IE_Pressed, this, &AUserPawn::SelectGoods);
	PlayerInputComponent->BindAction("MoveGoods", EInputEvent::IE_Pressed, this, &AUserPawn::MoveGoods);
    PlayerInputComponent->BindAction("RotateGoods", EInputEvent::IE_Pressed, this, &AUserPawn::RotateGoods);
	PlayerInputComponent->BindAction("ChangeGoods", EInputEvent::IE_Pressed, this, &AUserPawn::ChangeGoods);
	
#endif
    
}
void AUserPawn::StopARSession()
{
    UARBlueprintLibrary::StopARSession();
	m_ARIsSetUP = false;
}
void AUserPawn::OnFingerTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    UE_LOG(LogTemp, Log, TEXT("zhx :: AUserPawn::OnFingerTouch pressed"));
	int num;
	FVector2D screenPosition;
	GetPressedFingers(num, screenPosition);
	if (num == 1)
	{
		IsHaveActorInScreenPosition(screenPosition);
	}
//    switch (FingerIndex)
//    {
//        case ETouchIndex::Touch1:
//        {
//            m_IsPressed = true;
//            m_FingerNum++;
//
//        }break;
//        case ETouchIndex::Touch2:
//        {
//            m_IsPressed = true;
//            m_FingerNum++;
//        }break;
//        default:
//            break;
//    }
//    if (m_FingerNum == 1)
//    {
//        m_ScreenPosition = GetFingerPosition(1);
//        
//        if (IsHaveActorInScreenPosition(m_ScreenPosition))
//        {
//            
//        }else
//        {
////            m_SelectActor = TryCreateARActor(m_ScreenPosition);
//        }
//    }
}
void AUserPawn::OnFingerTouchMoved(const ETouchIndex::Type FingerIndex, const FVector Location)
{
//    UE_LOG(LogTemp, Log, TEXT("zhx :: AUserPawn::OnFingerTouch moved"));
    if (m_SelectActor)
    {
		int num;
		FVector2D screenPosition;
		GetPressedFingers(num, screenPosition);

        if (num == 1)
        {
			if (m_WantToRotate)
			{
				RotateSelectARActor();
			}
			else
			{
				MoveSelecteARActor();
			}
           
        }else if (num == 2)
        {
			RotateSelectARActor();
        }
    }
}
void AUserPawn::OnFingerTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    UE_LOG(LogTemp, Log, TEXT("zhx :: AUserPawn::OnFingerTouch releaseed"));
    
	/*m_FingerNum--;
	if (m_FingerNum <= 0)
	{
		m_IsPressed = false;
	}*/
}
void AUserPawn::GetPressedFingers(int & num, FVector2D & location)
{
	bool oneP, twoP;
	FVector2D oneFgLocation, twoFgLocation;
	m_Controller->GetInputTouchState(ETouchIndex::Touch1, oneFgLocation.X, oneFgLocation.Y, oneP);
	m_Controller->GetInputTouchState(ETouchIndex::Touch2, twoFgLocation.X, twoFgLocation.Y, twoP);

	if (oneP && twoP)
	{
		num = 2;
		location = (oneFgLocation + twoFgLocation) * 0.5;
	}else if (oneP)
	{
		num = 1;
		location = oneFgLocation;
	}else if (twoP)
	{
		num = 1;
		location = twoFgLocation;
	}
}
FVector2D AUserPawn::GetFingerPosition(int _fingerNum)
{
    FVector2D SPostion;
#if PLATFORM_IOS
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
#else
	m_Controller->GetMousePosition(SPostion.X, SPostion.Y);
#endif
    return SPostion;
}
bool  AUserPawn::IsHaveActorInScreenPosition(FVector2D _position)
{
	if (m_Controller->PlayerInput)
	{}
	else
	{
		return false;
	}
	bool IsSelect = false;
    
    if (m_SelectComponent)
    {
        m_SelectComponent->SetRenderCustomDepth(false);
    }
    if (m_SelectActor)
    {
        m_SelectActor->ShowPlaneComponent(false);
        m_WantToRotate = false;
    }
    m_SelectComponent = nullptr;
    m_SelectActor = nullptr;
    
    FHitResult hitResult;
    if (m_Controller->GetHitResultAtScreenPosition(_position, ECC_WorldStatic, false, hitResult))
    {
		m_SelectActor = Cast<AUserActor>(hitResult.GetActor());
		if (m_SelectActor)
		{
			m_SelectActor->ShowPlaneComponent(true);

			UPrimitiveComponent * selelctComponent = hitResult.GetComponent();
			if (selelctComponent->GetName().Equals(TEXT("PlaneRotateComponent")))
			{
				UE_LOG(LogTemp, Log, TEXT("zhx : select plane rotate compoent"));
				m_WantToRotate = true;
			}
			else
			{
				m_WantToRotate = false;
				if (m_SelectComponent)
				{
					m_SelectComponent->SetRenderCustomDepth(false);
					m_SelectComponent = nullptr;
				}
				m_SelectComponent = Cast<UUserComponent>(hitResult.GetComponent());
				m_SelectComponent->SetRenderCustomDepth(true);
				// send msg to ui
				IsSelect = true;
				msg_ptr _msg(new LocalMsg(Msg_Local, 3001, &IsSelect));
				MsgCenter::GetInstance()->SendMsg(_msg);
				UE_LOG(LogTemp, Log, TEXT("zhx : select actor name :%s,component name : %s"), *m_SelectActor->GetName(), *m_SelectComponent->GetName());

			}
			return true;
		}
	}
	
	msg_ptr _msg(new LocalMsg(Msg_Local, 3001, &IsSelect));
	MsgCenter::GetInstance()->SendMsg(_msg);

	UE_LOG(LogTemp, Log, TEXT("zhx : select good fail"));
    return false;
}
void AUserPawn::TryCreateMergeActor(GoodsData * _goodsData)
{
	AUserActor * one = TryCreateARActor(_goodsData);
	AUserActor * two = TryCreateARActor(_goodsData->matchedProduct);
	if (one && two)
	{
		UE_LOG(LogTemp, Log, TEXT("zhx : one actor data num : %d"), one->m_GoodsDatas.Num());
		UE_LOG(LogTemp, Log, TEXT("zhx : two actor data num : %d"), two->m_GoodsDatas.Num());

		one->SetMatchId(_goodsData->id, _goodsData->matchedProduct->id);
		two->SetMatchId(_goodsData->id, _goodsData->matchedProduct->id);

		MergeTwoUserActor(one, two);

		UE_LOG(LogTemp, Log, TEXT("zhx : GetRuntimeGoodsList data num : %d"), RuntimeRDataManager::GetInstance()->GetRuntimeGoodsList().Num());

	}

}
AUserActor * AUserPawn::TryCreateARActor(GoodsData * _goodsData)
{
	if (_goodsData == nullptr)
	{
		return nullptr;
	}
	AUserActor * uactor = nullptr;
	UStaticMesh * mesh = _goodsData->LoadMesh();
	if (mesh == nullptr)
	{
		return nullptr;
	}
    APlayerCameraManager * cameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
    FVector location = cameraManager->GetCameraLocation();
    FVector forward = cameraManager->GetCameraRotation().Vector();
    location = location + forward.GetSafeNormal() * 100;

    UClass * uclass = LoadClass<AUserActor>(NULL,TEXT("/Game/Blueprints/BP_UserActor.BP_UserActor_C"),NULL,LOAD_None,NULL);
	FActorSpawnParameters parameter;
	parameter.Owner = this;
	parameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	parameter.bNoFail = true;
	uactor = GetWorld()->SpawnActor<AUserActor>(uclass,parameter);
	uactor->SetActorLocation(location);
    //AUserActor * uactor = (AUserActor*)actor;
    switch(_goodsData->typeId)
    {
        case 0:
        {
            uactor->m_Type = User_None;
        }break;
        case 1:
        {
            uactor->m_Type = User_Hua;
        }break;
        case 2:
        {
            uactor->m_Type = User_Pen;
        }break;
    }

	m_CurrentGoodsData = RuntimeRDataManager::GetInstance()->AddGoodsToList(_goodsData);
    //UStaticMesh * mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/DLC/Goods/AR_HuaPen_181026013/AR_HuaPen_181026013"));
	//UStaticMesh * mesh = LoadObject<UStaticMesh>(nullptr, *m_CurrentGoodsData->GamePath);
    uactor->m_Mesh->SetStaticMesh(mesh);
    uactor->m_Mesh->RegisterComponent();
	uactor->m_Mesh->SetGoodsData(m_CurrentGoodsData);
	uactor->m_GoodsDatas.Add(m_CurrentGoodsData);
//    m_SelectActor = actor;
    
	return uactor;
}
void AUserPawn::TryDeleteARActor(AUserActor * actor)
{
	TArray<AActor *> allUserActor;
	UGameplayStatics::GetAllActorsOfClass(this, AUserActor::StaticClass(), allUserActor);

	if (allUserActor.Contains(actor))
	{
		RuntimeRDataManager::GetInstance()->RemoveGoodsFromList(actor->m_GoodsDatas);

		actor->Destroy();
	}
	GEngine->ForceGarbageCollection(true);

}
void AUserPawn::DeleteSelectARActor()
{
	TryDeleteARActor(m_SelectActor);
	bool IsSelect = false;
	msg_ptr _msg(new LocalMsg(Msg_Local, 3001, &IsSelect));
	MsgCenter::GetInstance()->SendMsg(_msg);
}
void AUserPawn::DeleteAllARActor()
{

    TArray<AActor *> allUserActor;
    UGameplayStatics::GetAllActorsOfClass(this, AUserActor::StaticClass(), allUserActor);
    for (int i = 0; i < allUserActor.Num(); i++)
    {
        AUserActor * actor = (AUserActor *)allUserActor[i];
		TryDeleteARActor(actor);
		actor = nullptr;
    }
    RuntimeRDataManager::GetInstance()->RemoveAllGoodsData();
	bool IsSelect = false;
	msg_ptr _msg(new LocalMsg(Msg_Local, 3001, &IsSelect));
	MsgCenter::GetInstance()->SendMsg(_msg);

	GEngine->ForceGarbageCollection(true);

}
void AUserPawn::QuitEditScene()
{
    DeleteAllARActor();
    StopARSession();
    
}
AActor * AUserPawn::TryCreateARActor(FVector2D _screenPosition)
{
    AActor * actor = nullptr;

    if (!m_CurrentGoodsData->GamePath.IsEmpty())
    {
        FTransform t;
        if (GetTrackedGeometryTransform(_screenPosition, t))
        {
            UClass * uclass = LoadClass<AActor>(NULL,TEXT("/Game/Blueprints/BP_UserActor.BP_UserActor_C"),NULL,LOAD_None,NULL);
            
            actor = GetWorld()->SpawnActor<AActor>(uclass,t);
            
            AUserActor * uactor = (AUserActor*)actor;

            UStaticMesh * mesh = LoadObject<UStaticMesh>(nullptr, *m_CurrentGoodsData->GamePath);

            uactor->m_Mesh->SetStaticMesh(mesh);
            uactor->m_Mesh->RegisterComponent();
			uactor->AddGoodsData(m_CurrentGoodsData);
        }
    }
   
    return actor;
}
void AUserPawn::MoveSelecteARActor()
{
    if (m_SelectActor && m_SelectActor->IsValidLowLevel())
    {
       
        //FVector2D _screenPosition = GetFingerPosition(1);

		int num;
		FVector2D _screenPosition;
		GetPressedFingers(num, _screenPosition);

#if PLATFORM_IOS
		FTransform t;
		if (GetTrackedGeometryTransform(_screenPosition, t))
		{
			UE_LOG(LogTemp, Log, TEXT("set location"));
			m_SelectActor->SetActorLocation(t.GetLocation());
		}
#else
		FHitResult HitResult;
		m_Controller->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, HitResult);
		FVector HitLoction = HitResult.Location;
		FVector OldLoction = m_SelectActor->GetActorLocation();
		FVector NewLoction(HitLoction.X, HitLoction.Y, OldLoction.Z);
		m_SelectActor->SetActorLocation(HitLoction);
#endif
        TArray<AActor *> allUserActor;
        UGameplayStatics::GetAllActorsOfClass(this, AUserActor::StaticClass(), allUserActor);
		for (int i = 0; i < allUserActor.Num(); i++)
		{
			AUserActor * actor = (AUserActor *)allUserActor[i];
			if (m_SelectActor != actor)
			{
				if (FVector::Distance(m_SelectActor->GetActorLocation(), actor->GetActorLocation()) <= 80)
				{
					UE_LOG(LogTemp, Log, TEXT("zhx : two user actor distance <= 80"));
					MergeTwoUserActor(m_SelectActor, actor);
				}
			}
		}
    }
}
void AUserPawn::RotateSelectARActor()
{
	if (m_SelectActor && m_SelectActor->IsValidLowLevel())
	{
		FVector2D _screenPosition;
		bool IsVerse;
		if (m_WantToRotate)
		{
			_screenPosition = GetFingerPosition(1);
		}
		else
		{
			_screenPosition = GetFingerPosition(2);
		}

		float spd = _screenPosition.X - m_ScreenPosition.X;
		
		IsVerse = spd > 0.f ? true : false;

		FRotator currentRotator = m_SelectActor->m_Mesh->GetComponentRotation();
		currentRotator.Yaw -= (spd * m_RotateSpeed);
		
		float yawProcess = (currentRotator.Yaw + 180.f) / 360.f;
		UE_LOG(LogTemp, Log, TEXT("zhx : current Yaw : %f"), yawProcess);

//        if(currentRotator.Yaw > 0)
//        {
//            m_SelectActor->m_PlaneRotateComponent->SetScalarParameterValueOnMaterials(TEXT("Percent"), yawProcess);
//        }else
//        {
//            m_SelectActor->m_PlaneRotateComponent->SetScalarParameterValueOnMaterials(TEXT("Percent"), yawProcess);
//        }
		m_SelectActor->m_PlaneRotateComponent->SetScalarParameterValueOnMaterials(TEXT("Percent"), 1.f - yawProcess);
			
		m_SelectActor->m_Mesh->SetRelativeRotation(currentRotator);//->SetActorRotation(currentRotator);
		
		m_ScreenPosition = _screenPosition;
	}
}
void AUserPawn::MergeTwoUserActor(AUserActor * one, AUserActor * two)
{
		if (one->m_Type == User_Hua && two->m_Type == User_Pen)
		{
            if(two->MergeOtherActor(one))
            {
                //m_SelectActor = two;
				one = nullptr;
            }
//            FString socketName = FString::Printf(TEXT("Socket%d"), two->m_SoketIndex + 1);
//
//            if (two->m_Mesh->GetSocketByName(*socketName))
//            {
//                UUserComponent * component = NewObject<UUserComponent>(two,TEXT("HuaComponent"));
//                component->AttachToComponent(two->m_Mesh, FAttachmentTransformRules::KeepRelativeTransform, *socketName);
//                UStaticMesh * hua = one->m_Mesh->GetStaticMesh();
//                component->SetStaticMesh(hua);
//                component->RegisterComponent();//WithWorld(GetWorld());
//                component->SetGoodsData(one->m_Mesh->m_Data);
//                two->AddUserComponent(component);
//                for (int i = 0; i < one->m_GoodsDatas.Num(); i++)
//                {
//                    two->m_GoodsDatas.Add(one->m_GoodsDatas[i]);
//                }
//                two->m_SoketIndex += 1;
//                m_SelectActor = two;
//                one->Destroy();
//                GEngine->ForceGarbageCollection(true);
//            }
		}
		else if (one->m_Type == User_Pen && two->m_Type == User_Hua)
		{
            if(one->MergeOtherActor(two))
            {
                //m_SelectActor = one;
				two = nullptr;
            }
            
//            FString socketName = FString::Printf(TEXT("Socket%d"), one->m_SoketIndex + 1);
//            if (one->m_Mesh->GetSocketByName(*socketName))
//            {
//                UUserComponent * component = NewObject<UUserComponent>(one,TEXT("HuaComponent"));
//                component->AttachToComponent(one->m_Mesh, FAttachmentTransformRules::KeepRelativeTransform, *socketName);
//                UStaticMesh * hua = two->m_Mesh->GetStaticMesh();
//                component->SetStaticMesh(hua);
//                component->RegisterComponent();//WithWorld(GetWorld());
//                component->SetGoodsData(two->m_Mesh->m_Data);
//                one->AddUserComponent(component);
//                for (int i = 0; i < two->m_GoodsDatas.Num(); i++)
//                {
//                    one->m_GoodsDatas.Add(two->m_GoodsDatas[i]);
//                }
//                one->m_SoketIndex += 1;
//                m_SelectActor = one;
//                two->Destroy();
//                GEngine->ForceGarbageCollection(true);
//            }
		}
}
int	 AUserPawn::GetChangeProductId()
{
	if (m_SelectActor && m_SelectComponent)
	{
		if (m_SelectActor->m_MatchMap.Contains(m_SelectComponent->m_Data->id))
		{
			return m_SelectActor->m_MatchMap[m_SelectComponent->m_Data->id];
		}
	}
	return 0;
}
void AUserPawn::ChangeSelectModel(UStaticMesh * mesh)
{
	if (m_SelectComponent)
	{
		if (mesh)
		{
			m_SelectComponent->SetStaticMesh(mesh);
            m_SelectActor->ResetHuaComponent();
		}
	}
}
void AUserPawn::CancelChangeSelectModel()
{
	if (m_SelectComponent)
	{
		ChangeSelectModel(m_SelectComponent->m_Data->LoadMesh());
	}
}
void AUserPawn::SureChangeSelectModel(GoodsData * _data)
{
	if (m_SelectComponent)
	{
		GoodsData * preData = m_SelectComponent->m_Data;
		int preId = preData->id;
		m_SelectActor->RemoveGoodsData(preData);
		m_CurrentGoodsData = RuntimeRDataManager::GetInstance()->ChangeListGoods(preData, _data);
		m_SelectActor->AddGoodsData(m_CurrentGoodsData);
		m_SelectComponent->SetGoodsData(m_CurrentGoodsData);
		int preValue = m_SelectActor->m_MatchMap[preId];
		m_SelectActor->m_MatchMap.Remove(preId);
		m_SelectActor->m_MatchMap[preValue] = m_CurrentGoodsData->id;
		m_SelectActor->m_MatchMap.Add(m_CurrentGoodsData->id, preValue);
	}
}
// PC TEST
void AUserPawn::SelectGoods()
{
    ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(m_Controller->Player);
    
    if (LocalPlayer && LocalPlayer->ViewportClient)
    {
        FVector2D MousePosition;
        if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
        {
            IsHaveActorInScreenPosition(MousePosition);
        }
    }
}
void AUserPawn::MoveGoods()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : PC move goods"));
    IsCMove = !IsCMove;
}
void AUserPawn::RotateGoods()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : PC rotate goods"));
    IsCRotate = !IsCRotate;
    
}
void AUserPawn::ChangeGoods()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : PC change goods"));
    if (m_SelectComponent)
    {
        UStaticMesh * mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/TestMesh/HuaPanB.HuaPanB"));
        m_SelectComponent->SetStaticMesh(mesh);
        m_SelectComponent->RegisterComponent();
    }
}
void AUserPawn::ApplicationWillEnterBackground(msg_ptr _msg)
{
	QuitEditScene();

}
void AUserPawn::ApplicationHasEnteredForeground(msg_ptr _msg)
{
	StopARSession();
}
