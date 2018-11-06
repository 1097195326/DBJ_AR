#include "RuntimeTDataManager.h"
//#include "AppInstance.h"

RuntimeTDataManager * RuntimeTDataManager::GetInstance()
{
    static RuntimeTDataManager m;

    return &m;
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
	for(GoodsData * goods : m_CurrentGoodsList)
	{
		delete goods;
	}
	m_CurrentGoodsList.Empty();

}
TArray<GoodsData*> RuntimeTDataManager::GetCurrentGoodsList()
{
	return m_CurrentGoodsList;
}