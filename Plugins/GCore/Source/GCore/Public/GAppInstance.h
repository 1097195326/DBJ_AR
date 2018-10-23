//
//  GAppInstance.hpp
//  GameFrame
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once


#include "CoreMinimal.h"
#include "GObject.h"
#include "Engine/GameInstance.h"
#include "GAppInstance.generated.h"

UCLASS()
class GCORE_API UGAppInstance : public UGameInstance, public GObject
{
    GENERATED_BODY()
private:
    static UGAppInstance *  m_Instance;
public:
    static UGAppInstance * GetInstance();
    
    virtual void Init() override;
    
    UFUNCTION(Exec)
    void ShowLog();
    
};

