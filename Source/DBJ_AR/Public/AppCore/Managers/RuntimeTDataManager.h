#pragma once

#include "GObject.h"
#include "CoreMinimal.h"
#include "GoodsData.h"


struct GoodsListCategoryData
{
	int id;
	FString name;
};

class DBJ_AR_API RuntimeTDataManager : public GObject
{
private:
	TArray<GoodsData*>		m_ChangeGoodsList;

	TArray<GoodsData*>		m_CurrentGoodsList;

	TArray<GoodsListCategoryData> m_CategoryList;

public:
    static RuntimeTDataManager * GetInstance();

	void DecodeCategoryList(const TSharedPtr<FJsonObject> _data);
	TArray<GoodsListCategoryData>	GetCategoryList();
	void	ClearCategoryList();
	//gooods list
	void	DecodeGoodsList(const TSharedPtr<FJsonObject> _data);
	void	ClearGoodList();
	TArray<GoodsData*>	GetCurrentGoodsList();
	// change list
	void  DecodeChangeList(const TSharedPtr<FJsonObject> _data);
	void	ClearChangeGoodList();
	TArray<GoodsData*>	GetChangeGoodsList();
};
