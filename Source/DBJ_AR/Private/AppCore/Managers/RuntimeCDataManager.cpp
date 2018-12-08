#include "RuntimeCDataManager.h"
#include "UserInfo.h"
#include "DateTime.h"

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
		objD->TryGetStringField(TEXT("deliveryArea"), data->Address);
		objD->TryGetStringField(TEXT("address"), data->DetailAddress);
		objD->TryGetNumberField(TEXT("expectReceiveTime"), data->ExpectReceiveTime);
		objD->TryGetStringField(TEXT("expectReceiveTimeStr"), data->ReceiveTime);
		objD->TryGetBoolField(TEXT("morning"), data->Morning);
		
		/*FString IsMorning;
		if (data->Morning)
		{
			IsMorning = TEXT("上午");
		}
		else
		{
			IsMorning = TEXT("下午");
		}
		FDateTime time(data->ExpectReceiveTime);
		data->ReceiveTime = FString::Printf(TEXT("%d年%d月%d日%s"), time.GetYear(),time.GetMonth(),time.GetDay(),*IsMorning);*/

		objD->TryGetNumberField(TEXT("provinceId"), data->ProvinceId);
		objD->TryGetNumberField(TEXT("cityId"), data->CityId);
		objD->TryGetNumberField(TEXT("districtId"), data->DistrictId);

		objD->TryGetNumberField(TEXT("deliverType"), data->DeliverType);
		objD->TryGetNumberField(TEXT("status"), data->Status);
		objD->TryGetNumberField(TEXT("totalQuantity"), data->totalQuantity);
		objD->TryGetNumberField(TEXT("totalPrice"), data->totalPrice);
		objD->TryGetStringField(TEXT("remark"), data->Remark);
		objD->TryGetStringField(TEXT("gmtCreate"),data->CommitTime);
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
	for (int j = 0; j< m_OrderList.Num(); )
	{
		R_Order * order = m_OrderList[j++];
		for (int i = 0 ; i< order->ProductList.Num() ; )
		{
			GoodsData * data = order->ProductList[i++];
			delete data;
		}
		order->ProductList.Empty();
		delete order;
	}
	m_OrderList.Empty();

}