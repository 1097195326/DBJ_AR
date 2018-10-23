//
//  GObject.cpp
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//
#include "GCore.h"
#include "GObject.h"

static int _GObjectCount = 0;

GObject::GObject()
{
    m_ObjectIndex = _GObjectCount++;
	
}
GObject::~GObject()
{
    m_ObjectIndex = -1;
	On_Delete();
}
void GObject::On_Init()
{
	UE_LOG(LogTemp, Log, TEXT("zhx : object create"));

}
void GObject::On_Start()
{

}
void GObject::On_Tick(float delta)
{

}
void GObject::On_End()
{

}
void GObject::On_Delete()
{

}
int GObject::GetGObjectIndex()
{
    return m_ObjectIndex;
}
