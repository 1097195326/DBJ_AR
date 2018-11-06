#pragma once
#include "GameModule.h"


class DBJ_AR_API LoginGameModule : public GameModule
{
private:

public:
	static LoginGameModule * GetInstance();

	virtual void On_Init();
	virtual void On_Start();
	virtual void On_Delete();

	void GetSmsCodeToLogin(FString _phoneNum);
	void OnGetSmsCode(msg_ptr _msg);
	void UserLogin(FString _phoneNum, FString _smsCodeNum);
	void OnUserLogin(msg_ptr _msg);
};