//
//  UserController.h
//  GameFrame_Index
//
//  Created by fafa on 2018/8/14.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once


#include "GPawnController.h"
#include "UserPawnController.generated.h"
//
UCLASS()
class DBJ_AR_API AUserPawnController : public AGPawnController
{
    GENERATED_BODY()
public:

    virtual void On_Init() override;
};
