//
//  GObject.hpp
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "IObject.h"
#include "CoreMinimal.h"
#include "ClassReflect.h"

class GCORE_API GObject : public I_Object
{
private:
    int     m_ObjectIndex;
public:
    GObject();
    virtual ~GObject();

	virtual void On_Init();
	virtual void On_Start();
	virtual void On_Tick(float delta);
	virtual void On_End();
	virtual void On_Delete();
public:

    int GetGObjectIndex();
    
};

