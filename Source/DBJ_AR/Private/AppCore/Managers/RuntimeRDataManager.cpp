#include "RuntimeRDataManager.h"
#include "UserInfo.h"

RuntimeRDataManager * RuntimeRDataManager::GetInstance()
{
	static RuntimeRDataManager m;
	
	return &m;
}
RuntimeRDataManager::RuntimeRDataManager()
{
	m_CurrentOrder = nullptr;
	m_EditOrder = nullptr;
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
TMap<int, GoodsData*> RuntimeRDataManager::GetOrderDatas()
{
	TMap<int, GoodsData*> orderInfoData;
	if (m_EditOrder)
	{
		for (int i = 0; i < m_EditOrder->ProductList.Num(); i++)
		{
			GoodsData * data = m_EditOrder->ProductList[i];
			orderInfoData.Add(data->id, data);
		}
		return orderInfoData;
	}
	for (int i = 0;i < m_RuntimeGoodsList.Num(); i++)
	{
		GoodsData * data = m_RuntimeGoodsList[i];
		if (orderInfoData.Contains(data->id))
		{
			orderInfoData[data->id]->quantity++;
		}
		else
		{
			data->quantity = 1;
			orderInfoData.Add(data->id, data);
		}
	}
	return orderInfoData;
}
R_Order * RuntimeRDataManager::MakeOrder()
{
	FSaveUserData userData = UserInfo::Get()->GetLocalData();

	m_CurrentOrder = new R_Order();
	m_CurrentOrder->DeliverType = 1;
	m_CurrentOrder->ReceiverCompanyName = userData.companyName;
	m_CurrentOrder->ReceiverName = userData.name;
	m_CurrentOrder->ReceiverPhone = userData.phone;
	m_CurrentOrder->Address = userData.detailAddress;

	return m_CurrentOrder;
}
void RuntimeRDataManager::EditOrder(R_Order * order)
{
	m_EditOrder = order;
}
bool RuntimeRDataManager::IsEditOrder()
{
	if (m_EditOrder)
	{
		return true;
	}
	return false;
}
R_Order * RuntimeRDataManager::GetCurrentOrder()
{
	if (m_CurrentOrder != nullptr)
	{
		return m_CurrentOrder;
	}
	return m_EditOrder;
}
void RuntimeRDataManager::ClearOrder()
{
	if (m_CurrentOrder)
	{
		delete m_CurrentOrder;
		m_CurrentOrder = nullptr;
	}
	if (m_EditOrder)
	{
		m_EditOrder = nullptr;
	}
}