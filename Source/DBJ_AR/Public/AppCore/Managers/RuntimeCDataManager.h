#pragma once

#include "GObject.h"
#include "CoreMinimal.h"
#include "GoodsData.h"
#include "RuntimeRDataManager.h"

class DBJ_AR_API RuntimeCDataManager : public GObject
{
private:
	TArray<R_Order*> m_OrderList;
	int			m_lastId;
public:
	static RuntimeCDataManager * GetInstance();
	void	DecodeAccountOrderList(const TSharedPtr<FJsonObject> _data);
	void	ClearAccountOrderList();
	TArray<R_Order*> GetAccountOrderList();


};
