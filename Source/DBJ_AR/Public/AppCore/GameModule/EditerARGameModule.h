#pragma once
#include "GameModule.h"
//#include "FileDownloadManager.h"


class DBJ_AR_API EditerARGameModule : public GameModule
{
private:
	int		m_GetArea_Level;

public:
	static EditerARGameModule * GetInstance();
	EditerARGameModule();

	virtual void On_Init();
	virtual void On_Start();
	virtual void On_Delete();

	/*FDelegateHandle m_DelegateHandle;
	void OnGetPakFinish(int _finish, FFileInfo _info);*/

	void	GetCategoryList();
	void	OnGetCategoryList(msg_ptr _msg);
    void    GetProductList(int categoryId = 0, int lastId = 0, int typeId = 0, int materialId = 0, int innerDiameterId = 0, int size =10);
    void    OnGetProductList(msg_ptr _msg);
	// change list
	void	GetChangeList(int productId, int lastId = 0, int exceptProductId = 0, int size = 10);
	void	OnGetChangeList(msg_ptr _msg);
	//get address
	void	GetAreaList(int parentId,int level);
	void	OnGetAreaList(msg_ptr _msg);
	//save and commit current order
	void	CommitCurrentOrder();
	void	OnCommitCurrentOrder(msg_ptr _msg);
	// get user account order
	void	GetAccountOrder(int lastid = 0, int size = 10);
	void	OnGetAccountOrder(msg_ptr _msg);
	// user logout
	void	UserLogout();
	void	OnUserLogout(msg_ptr _msg);
	// editer user info
	void	UpdateUserName(const FString & _userName);
	void	OnUpdateSelf(msg_ptr _msg);
	// get inner diameter
	void	GetInnerDiameters();
	void	OnGetInnerDiameters(msg_ptr _msg);
	// get material
	void	GetMaterials();
	void	OnGetMaterials(msg_ptr _msg);
	// get types
	void	GetGoodsType();
	void	OnGetGoodsType(msg_ptr _msg);
};
