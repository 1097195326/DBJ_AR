#include "RuntimeRDataManager.h"
#include "UserInfo.h"

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
GoodsData * RuntimeRDataManager::ChangeListGoods(GoodsData* _preData, GoodsData * _changeData)
{
	if (m_RuntimeGoodsList.Contains(_preData))
	{
		m_RuntimeGoodsList.Remove(_preData);
		delete _preData;
		GoodsData * newData = new GoodsData();
		_changeData->CloneData(newData);
		m_RuntimeGoodsList.Add(newData);
		return newData;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("zhx : change list goods fail ,can not find preData"));
	}
	return nullptr;
}
void RuntimeRDataManager::RemoveGoodsFromList(TArray<GoodsData*> _datas)
{
	for (int i = 0; i < _datas.Num(); i++)
	{
		GoodsData * data = _datas[i];
		if (data != nullptr && m_RuntimeGoodsList.Find(data))
		{
			m_RuntimeGoodsList.Remove(data);
			delete data;
		}
	}
	
}
TArray<GoodsData*> RuntimeRDataManager::GetRuntimeGoodsList()
{
	return m_RuntimeGoodsList;
}
TMap<int, OrderInfoData> RuntimeRDataManager::GetOrderDatas()
{
	TMap<int, OrderInfoData> orderInfoData;

	for (int i = 0;i < m_RuntimeGoodsList.Num(); i++)
	{
		GoodsData * data = m_RuntimeGoodsList[i];
		if (orderInfoData.Contains(data->id))
		{
			orderInfoData[data->id].Num++;
		}
		else
		{
			OrderInfoData infoData;
			infoData.Num = 1;
			infoData.goodsData = data;
			orderInfoData.Add(data->id, infoData);
		}
	}
	return orderInfoData;
}
R_Order * RuntimeRDataManager::MakeOrder()
{
	FSaveUserData userData = UserInfo::Get()->GetLocalData();

	m_CurrentOrder = new R_Order();
	m_CurrentOrder->ReceiverCompanyName = userData.companyName;
	m_CurrentOrder->ReceiverName = userData.renterName;
	m_CurrentOrder->ReceiverPhone = userData.phone;
	m_CurrentOrder->Address = userData.detailAddress;

	return m_CurrentOrder;
}
R_Order * RuntimeRDataManager::GetCurrentOrder()
{
	return m_CurrentOrder;
}
void RuntimeRDataManager::ClearOrder()
{
	if (m_CurrentOrder)
	{
		delete m_CurrentOrder;
		m_CurrentOrder = nullptr;
	}
}