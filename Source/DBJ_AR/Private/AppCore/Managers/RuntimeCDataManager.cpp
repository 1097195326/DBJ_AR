#include "RuntimeCDataManager.h"
#include "UserInfo.h"

RuntimeCDataManager * RuntimeCDataManager::GetInstance()
{
	static RuntimeCDataManager m;

	return &m;
}

void RuntimeCDataManager::DecodeAccountOrderList(const TSharedPtr<FJsonObject> _data)
{
	ClearAccountOrderList();
	TSharedPtr<FJsonObject> JsonData = _data->GetObjectField(TEXT("data"));
	m_lastId = JsonData->GetNumberField(TEXT("lastId"));
	const TArray<TSharedPtr<FJsonValue>> dList = JsonData->GetArrayField("list");

	for (TSharedPtr<FJsonValue> obj : dList)
	{
		TSharedPtr<FJsonObject> objD = obj->AsObject();

		R_Order * data = new R_Order();
		objD->TryGetNumberField(TEXT("orderId"), data->Id);
		objD->TryGetStringField(TEXT("receiverCompanyName"), data->ReceiverCompanyName);
		objD->TryGetStringField(TEXT("receiverName"), data->ReceiverName);
		objD->TryGetStringField(TEXT("receiverPhone"), data->ReceiverPhone);
		objD->TryGetStringField(TEXT("address"), data->Address);
		objD->TryGetStringField(TEXT("detailAddress"), data->DetailAddress);
		objD->TryGetBoolField(TEXT("morning"), data->Morning);

		objD->TryGetNumberField(TEXT("status"), data->Status);
		objD->TryGetNumberField(TEXT("totalQuantity"), data->totalQuantity);
		objD->TryGetNumberField(TEXT("totalPrice"), data->totalPrice);
		objD->TryGetStringField(TEXT("remark"), data->Remark);

		const TArray<TSharedPtr<FJsonValue>> productList = objD->GetArrayField("productList");

		for (TSharedPtr<FJsonValue> goodsData : productList)
		{
			GoodsData * gData = new GoodsData();
			gData->InitWithJson(goodsData->AsObject());
			data->ProductList.Add(gData);
		}
		m_OrderList.Add(data);
	}

}
TArray<R_Order*> RuntimeCDataManager::GetAccountOrderList()
{
	return m_OrderList;
}

void RuntimeCDataManager::ClearAccountOrderList()
{
	for (int j = 0; j< m_OrderList.Num(); j++)
	{
		R_Order * order = m_OrderList[j];
		for (int i = 0 ; i< order->ProductList.Num() ; i++)
		{
			GoodsData * data = order->ProductList[i];
			delete data;
		}
		delete order;
	}
	m_OrderList.Empty();

}