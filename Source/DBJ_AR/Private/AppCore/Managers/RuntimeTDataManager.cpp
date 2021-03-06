#include "RuntimeTDataManager.h"
//#include "AppInstance.h"

RuntimeTDataManager * RuntimeTDataManager::GetInstance()
{
    static RuntimeTDataManager m;

    return &m;
}
void RuntimeTDataManager::DecodeCategoryList(const TSharedPtr<FJsonObject> _data)
{
    ClearCategoryList();
    
	const TArray<TSharedPtr<FJsonValue>> dList = _data->GetArrayField("data");

	for (TSharedPtr<FJsonValue> obj : dList)
	{
		TSharedPtr<FJsonObject> objD = obj->AsObject();

		GoodsListCategoryData data;
		objD->TryGetNumberField(TEXT("id"),data.id);
		objD->TryGetStringField(TEXT("name"),data.name);
		m_CategoryList.Add(data);
	}
	
}
TArray<GoodsListCategoryData>	RuntimeTDataManager::GetCategoryList()
{
	return m_CategoryList;
}

void RuntimeTDataManager::ClearCategoryList()
{
	m_CategoryList.Empty();

}
void RuntimeTDataManager::DecodeGoodsList(const TSharedPtr<FJsonObject> _data)
{
	ClearGoodList();

	const TSharedPtr<FJsonObject> data = _data->GetObjectField("data");
    const TArray<TSharedPtr<FJsonValue>> dList = data->GetArrayField("list");

	for(TSharedPtr<FJsonValue> obj : dList)
	{
		GoodsData  * goods = new GoodsData();
		goods->InitWithJson(obj->AsObject());
		m_CurrentGoodsList.Add(goods);
	}
}
void RuntimeTDataManager::ClearGoodList()
{
	/*for(GoodsData * goods : m_CurrentGoodsList)
	{
		delete goods;
	}*/
	m_CurrentGoodsList.Empty();

}
TArray<GoodsData*> RuntimeTDataManager::GetCurrentGoodsList()
{
	return m_CurrentGoodsList;
}

void RuntimeTDataManager::DecodeChangeList(const TSharedPtr<FJsonObject> _data)
{
	ClearChangeGoodList();

	const TSharedPtr<FJsonObject> data = _data->GetObjectField("data");
	const TArray<TSharedPtr<FJsonValue>> dList = data->GetArrayField("list");

	for (TSharedPtr<FJsonValue> obj : dList)
	{
		GoodsData  * goods = new GoodsData();
		goods->InitWithJson(obj->AsObject());
		m_ChangeGoodsList.Add(goods);
	}
}
void RuntimeTDataManager::ClearChangeGoodList()
{
	/*for (GoodsData * goods : m_ChangeGoodsList)
	{
		delete goods;
	}*/
	m_ChangeGoodsList.Empty();
}
TArray<GoodsData*>	RuntimeTDataManager::GetChangeGoodsList()
{
	return m_ChangeGoodsList;
}
