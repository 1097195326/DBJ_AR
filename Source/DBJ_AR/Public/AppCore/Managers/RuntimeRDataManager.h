#pragma once

#include "GObject.h"
#include "CoreMinimal.h"
#include "GoodsData.h"


class DBJ_AR_API RuntimeRDataManager : public GObject
{
private:
	TArray<GoodsData*>		m_RuntimeGoodsList;

public:
	static RuntimeRDataManager * GetInstance();

	GoodsData * AddGoodsToList(GoodsData* _data);
	void RemoveGoodsFromList(TArray<GoodsData*> _datas);
	TArray<GoodsData*>	GetRuntimeGoodsList();

};
