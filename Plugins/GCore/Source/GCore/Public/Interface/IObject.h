#pragma once


class GCORE_API I_Object
{
	virtual void On_Init() = 0;
	virtual void On_Start() = 0;
	virtual void On_Tick(float delta) = 0;
	virtual void On_End() = 0;
	virtual void On_Delete() = 0;
};