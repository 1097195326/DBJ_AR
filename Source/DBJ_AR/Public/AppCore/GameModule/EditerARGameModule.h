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
    void    GetProductList(int categoryId = 0, int lastId = 0, int size =10, int typeId = 0, int materialId = 0, int innerDiameterId = 0);
    void    OnGetProductList(msg_ptr _msg);
	// change list
	void	GetChangeList(int productId, int lastId = 0, int exceptProductId = 0, int size = 10);
	void	OnGetChangeList(msg_ptr _msg);
	
};
