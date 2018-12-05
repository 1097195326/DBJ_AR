#include "EditerARGameModule.h"
#include "EditerARUIController.h"
#include "DataManager.h"
#include "UserInfo.h"
#include "RuntimeTDataManager.h"
#include "RuntimeRDataManager.h"
#include "RuntimeCDataManager.h"


EditerARGameModule * EditerARGameModule::GetInstance()
{
    static EditerARGameModule m;
    return &m;
}
EditerARGameModule::EditerARGameModule()
{
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1003, this, &EditerARGameModule::OnUserLogout);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1004, this, &EditerARGameModule::OnGetCategoryList);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1008, this, &EditerARGameModule::OnGetProductList);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1009, this, &EditerARGameModule::OnCommitCurrentOrder);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1010, this, &EditerARGameModule::OnGetAccountOrder);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1013, this, &EditerARGameModule::OnGetChangeList);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1014, this, &EditerARGameModule::OnGetAreaList);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1015, this, &EditerARGameModule::OnUpdateSelf);
}
void EditerARGameModule::On_Init()
{
	UserInfo::Get()->ReadLocalData();

    m_CurrentUIController = new EditerARUIController();
    m_CurrentUIController->On_Init();
    
	

}
void EditerARGameModule::On_Start()
{
    m_CurrentUIController->On_Start();
    
}
void EditerARGameModule::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1003, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1004, this);
    MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1008, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1009, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1010, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1013, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1014, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1015, this);


    if (m_CurrentUIController != nullptr)
    {
        delete m_CurrentUIController;
    }
}
void EditerARGameModule::GetCategoryList()
{
	FString cookie = UserInfo::Get()->GetCookie();
	FString token = UserInfo::Get()->GetToken();

	FString httpUrl = Data_M->GetURL(1004);
	msg_ptr mMsg(new HttpMsg(Msg_HttpRequest, 1004,httpUrl,TEXT(""),Http_Get,cookie,token));

	MsgCenter::GetInstance()->SendMsg(mMsg);
}
void EditerARGameModule::OnGetCategoryList(msg_ptr _msg)
{
	int result = 0;
	TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
	if (jsonData->GetIntegerField(TEXT("code")) == 200)
	{
		result = 1;
		RuntimeTDataManager::GetInstance()->DecodeCategoryList(jsonData);
	}
	msg_ptr msg(new LocalMsg(Msg_Local, 2004, &result));
	MsgCenter::GetInstance()->SendMsg(msg);
}
void EditerARGameModule::GetProductList(int categoryId, int lastId, int size, int typeId, int materialId, int innerDiameterId)
{
	FString appendUrl = FString::Printf(TEXT("categoryId=%i&lastId=%i&size=%i&typeId=%i&materialId=%i&innerDiameterId=%i"), categoryId, lastId, size, typeId, materialId, innerDiameterId);

	FString cookie = UserInfo::Get()->GetCookie();
	FString token = UserInfo::Get()->GetToken();

	FString httpUrl = Data_M->GetURL(1008);
	msg_ptr mMsg(new HttpMsg(Msg_HttpRequest, 1008, httpUrl, appendUrl,Http_Get,cookie,token));

    MsgCenter::GetInstance()->SendMsg(mMsg);
}
void EditerARGameModule::OnGetProductList(msg_ptr _msg)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : EditerARGameModule::OnGetProductList : "));
	int result = 0;
	TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
	if (jsonData->GetIntegerField(TEXT("code")) == 200)
	{
		result = 1;
		RuntimeTDataManager::GetInstance()->DecodeGoodsList(jsonData);
	}
	msg_ptr msg(new LocalMsg(Msg_Local,2008, jsonData));
	MsgCenter::GetInstance()->SendMsg(msg);
}
void EditerARGameModule::GetChangeList(int productId, int lastId, int exceptProductId, int size)
{
	FString appendUrl = FString::Printf(TEXT("productId=%d&exceptProductId=%d&lastId=%d&size=%d"), productId, exceptProductId, lastId, size);

	FString cookie = UserInfo::Get()->GetCookie();
	FString token = UserInfo::Get()->GetToken();

	FString httpUrl = Data_M->GetURL(1013);
	msg_ptr mMsg(new HttpMsg(Msg_HttpRequest, 1013, httpUrl, appendUrl, Http_Get, cookie, token));

	MsgCenter::GetInstance()->SendMsg(mMsg);
}
void EditerARGameModule::OnGetChangeList(msg_ptr _msg)
{
	int result = 0;
	TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
	if (jsonData->GetIntegerField(TEXT("code")) == 200)
	{
		result = 1;
		RuntimeTDataManager::GetInstance()->DecodeChangeList(jsonData);
	}
	msg_ptr msg(new LocalMsg(Msg_Local, 2013, jsonData));
	MsgCenter::GetInstance()->SendMsg(msg);
}
void EditerARGameModule::GetAreaList(int parentId,int level)
{
	m_GetArea_Level = level;

	FString appendUrl = FString::Printf(TEXT("parentId=%d"), parentId);

	FString cookie = UserInfo::Get()->GetCookie();
	FString token = UserInfo::Get()->GetToken();

	FString httpUrl = Data_M->GetURL(1014);
	msg_ptr mMsg(new HttpMsg(Msg_HttpRequest, 1014, httpUrl, appendUrl, Http_Get, cookie, token));

	MsgCenter::GetInstance()->SendMsg(mMsg);
}
void EditerARGameModule::OnGetAreaList(msg_ptr _msg)
{
	TSharedPtr<FJsonObject> jsonObject = _msg->GetJsonObject();
	msg_ptr msg(new LocalMsg(Msg_Local, 2014, &m_GetArea_Level));
	msg->m_JsonObject = jsonObject;
	MsgCenter::GetInstance()->SendMsg(msg);
	
}
void EditerARGameModule::CommitCurrentOrder()
{
	R_Order * order = RuntimeRDataManager::GetInstance()->GetCurrentOrder();
	TSharedPtr<FJsonObject> t_jsonObject = MakeShareable(new FJsonObject);

	t_jsonObject->SetNumberField(TEXT("id"), order->Id);
	t_jsonObject->SetNumberField(TEXT("status"), order->Status);
	t_jsonObject->SetStringField(TEXT("receiverCompanyName"), order->ReceiverCompanyName);
	t_jsonObject->SetStringField(TEXT("receiverName"), order->ReceiverName);
	t_jsonObject->SetStringField(TEXT("receiverPhone"), order->ReceiverPhone);
	t_jsonObject->SetNumberField(TEXT("expectReceiveTime"), order->ExpectReceiveTime);
	t_jsonObject->SetBoolField(TEXT("morning"), order->Morning);
	t_jsonObject->SetNumberField(TEXT("deliverType"), order->DeliverType);
	t_jsonObject->SetNumberField(TEXT("provinceId"), order->ProvinceId);
	t_jsonObject->SetNumberField(TEXT("cityId"), order->CityId);
	t_jsonObject->SetNumberField(TEXT("districtId"), order->DistrictId);
	t_jsonObject->SetStringField(TEXT("address"), order->Address);
	t_jsonObject->SetStringField(TEXT("remark"), order->Remark);

	TArray<TSharedPtr<FJsonValue>> array;
	for (int i  = 0; i<order->ProductList.Num(); i++)
	{
		TSharedRef<FJsonObject> value = MakeShareable(new FJsonObject);
		value->SetNumberField(TEXT("id"), order->ProductList[i]->id);
		value->SetNumberField(TEXT("quantity"), order->ProductList[i]->quantity);
		array.Add(MakeShareable(new FJsonValueObject(value)));
	}

	t_jsonObject->SetArrayField(TEXT("productList"), array);

	FString cookie = UserInfo::Get()->GetCookie();
	FString token = UserInfo::Get()->GetToken();

	FString httpUrl = Data_M->GetURL(1009);
	msg_ptr msg(new HttpMsg(Msg_HttpRequest, 1009, t_jsonObject,httpUrl,Http_Post,cookie,token));
	MsgCenter::GetInstance()->SendMsg(msg);
}
void EditerARGameModule::OnCommitCurrentOrder(msg_ptr _msg)
{
	UE_LOG(LogTemp,Log,TEXT("zhx : EditerARGameModule::OnCommitCurrentOrder"));
	int result = 0;
	TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
	if (jsonData->GetIntegerField(TEXT("code")) == 200)
	{
		result = 1;
	}
	msg_ptr msg(new LocalMsg(Msg_Local, 2009, &result));
	MsgCenter::GetInstance()->SendMsg(msg);

}
void EditerARGameModule::GetAccountOrder(int lastid, int size)
{
	FString appendUrl = FString::Printf(TEXT("lastId=%d&size=%d"), lastid,size);

	FString cookie = UserInfo::Get()->GetCookie();
	FString token = UserInfo::Get()->GetToken();

	FString httpUrl = Data_M->GetURL(1010);
	msg_ptr mMsg(new HttpMsg(Msg_HttpRequest, 1010, httpUrl, appendUrl, Http_Get, cookie, token));

	MsgCenter::GetInstance()->SendMsg(mMsg);
}
void EditerARGameModule::OnGetAccountOrder(msg_ptr _msg)
{
	int result = 0;
	TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
	if (jsonData->GetIntegerField(TEXT("code")) == 200)
	{
		RuntimeCDataManager::GetInstance()->DecodeAccountOrderList(jsonData);
		result = 1;
	}
	msg_ptr msg(new LocalMsg(Msg_Local, 2010, jsonData));
	MsgCenter::GetInstance()->SendMsg(msg);
}
void EditerARGameModule::UserLogout()
{
	FString cookie = UserInfo::Get()->GetCookie();
	FString token = UserInfo::Get()->GetToken();

	FString httpUrl = Data_M->GetURL(1003);
	msg_ptr msg(new HttpMsg(Msg_HttpRequest, 1003,httpUrl,TEXT(""), Http_Post, cookie, token));
	MsgCenter::GetInstance()->SendMsg(msg);
}
void EditerARGameModule::OnUserLogout(msg_ptr _msg)
{
	int result = 0;
	TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
	if (jsonData->GetIntegerField(TEXT("code")) == 200)
	{
		TSharedPtr<FJsonObject> jsonObj = jsonData->GetObjectField(TEXT("data"));
		jsonObj->SetStringField(TEXT("token"), UserInfo::Get()->GetToken());
		UserInfo::Get()->SaveToLocal(jsonObj);
		result = 1;
	}
	msg_ptr msg(new LocalMsg(Msg_Local, 2003, &result));
	MsgCenter::GetInstance()->SendMsg(msg);
}
void EditerARGameModule::UpdateUserName(const FString & _userName)
{
	TSharedPtr<FJsonObject> t_jsonObject = MakeShareable(new FJsonObject);

	t_jsonObject->SetStringField(TEXT("name"), _userName);
	t_jsonObject->SetStringField(TEXT("phone"), UserInfo::Get()->GetLocalData().phone);
	t_jsonObject->SetStringField(TEXT("avatarUrl"), TEXT(""));

	FString cookie = UserInfo::Get()->GetCookie();
	FString token = UserInfo::Get()->GetToken();

	FString httpUrl = Data_M->GetURL(1015);
	msg_ptr msg(new HttpMsg(Msg_HttpRequest, 1015, t_jsonObject, httpUrl, Http_Put, cookie, token));
	MsgCenter::GetInstance()->SendMsg(msg);
}
void EditerARGameModule::OnUpdateSelf(msg_ptr _msg)
{
	int result = 0;
	TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
	if (jsonData->GetIntegerField(TEXT("code")) == 200)
	{
		result = 1;
	}
	msg_ptr msg(new LocalMsg(Msg_Local, 2015, &result));
	MsgCenter::GetInstance()->SendMsg(msg);
}