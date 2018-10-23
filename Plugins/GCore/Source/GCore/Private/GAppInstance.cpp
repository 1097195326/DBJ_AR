//
//  GAppInstance.cpp
//  GameFrame
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#include "GCore.h"
#include "GAppInstance.h"

UGAppInstance *  UGAppInstance::m_Instance = nullptr;

UGAppInstance * UGAppInstance::GetInstance()
{
    return m_Instance;
}
void UGAppInstance::Init()
{
    Super::Init();
    
	On_Init();
}
void UGAppInstance::ShowLog()
{
    UE_LOG(LogTemp,Log,TEXT("zhx :: UGAppInstance::ShowLog"));
    
}
