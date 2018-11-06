#pragma once

#include "GObject.h"
#include "CoreMinimal.h"
#include "GoodsData.h"


class DBJ_AR_API RuntimeTDataManager : public GObject
{
private:
	TArray<GoodsData*>		m_CurrentGoodsList;

public:
    static RuntimeTDataManager * GetInstance();

	//gooods list
	void	DecodeGoodsList(const TSharedPtr<FJsonObject> _data);
	void	ClearGoodList();
	TArray<GoodsData*>	GetCurrentGoodsList();

};
