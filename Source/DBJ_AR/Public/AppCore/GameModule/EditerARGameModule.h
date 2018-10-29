#pragma once
#include "GameModule.h"


class EditerARGameModule : public GameModule
{
private:

public:
	static EditerARGameModule * GetInstance();

	virtual void On_Init();
	virtual void On_Start();
	virtual void On_Delete();


};