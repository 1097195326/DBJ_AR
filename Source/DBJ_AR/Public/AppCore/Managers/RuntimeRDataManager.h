#pragma once

#include "GObject.h"
#include "CoreMinimal.h"
#include "GoodsData.h"

struct OrderInfoData
{
	int Num;
	GoodsData * goodsData;
};

class DBJ_AR_API RuntimeRDataManager : public GObject
{
private:
	TArray<GoodsData*>		m_RuntimeGoodsList;

public:
	static RuntimeRDataManager * GetInstance();

	GoodsData * AddGoodsToList(GoodsData* _data);
	GoodsData * ChangeListGoods(GoodsData* _preData,GoodsData * _changeData);
	void RemoveGoodsFromList(TArray<GoodsData*> _datas);
	TArray<GoodsData*>	GetRuntimeGoodsList();

	TMap<int, OrderInfoData> GetOrderDatas();
};
