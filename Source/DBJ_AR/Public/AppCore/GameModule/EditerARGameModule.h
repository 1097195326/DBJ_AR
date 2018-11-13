#pragma once
#include "GameModule.h"


class DBJ_AR_API EditerARGameModule : public GameModule
{
private:

public:
	static EditerARGameModule * GetInstance();

	virtual void On_Init();
	virtual void On_Start();
	virtual void On_Delete();

	void	GetCategoryList();
	void	OnGetCategoryList(msg_ptr _msg);
    void    GetProductList();
    void    OnGetProductList(msg_ptr _msg);
};
