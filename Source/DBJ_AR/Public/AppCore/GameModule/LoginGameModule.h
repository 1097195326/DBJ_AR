#pragma once
#include "GameModule.h"


class LoginGameModule : public GameModule
{
private:

public:
	static LoginGameModule * GetInstance();

	virtual void On_Init();
	virtual void On_Start();
	virtual void On_Delete();

	void GetSmsCodeToLogin(FString _phoneNum);

};