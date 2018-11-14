#include "RuntimeRDataManager.h"


RuntimeRDataManager * RuntimeRDataManager::GetInstance()
{
	static RuntimeRDataManager m;

	return &m;
}

GoodsData * RuntimeRDataManager::AddGoodsToList(GoodsData* _data)
{
	GoodsData * newData = new GoodsData();
	_data->CloneData(newData);
	m_RuntimeGoodsList.Add(newData);
	return newData;
}
void RuntimeRDataManager::RemoveGoodsFromList(TArray<GoodsData*> _datas)
{
	for (int i = 0; i < _datas.Num(); i++)
	{
		GoodsData * data = _datas[i];
		if (data != nullptr && m_RuntimeGoodsList.Find(data))
		{
			m_RuntimeGoodsList.Remove(data);
		}
	}
	
}
TArray<GoodsData*> RuntimeRDataManager::GetRuntimeGoodsList()
{
	return m_RuntimeGoodsList;
}