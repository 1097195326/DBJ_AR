#include "EditerARGameModule.h"
#include "EditerARUIController.h"
#include "DataManager.h"
#include "UserInfo.h"
#include "RuntimeTDataManager.h"



EditerARGameModule * EditerARGameModule::GetInstance()
{
    static EditerARGameModule m;
    return &m;
}
void EditerARGameModule::On_Init()
{
	UserInfo::Get()->ReadLocalData();

    m_CurrentUIController = new EditerARUIController();
    m_CurrentUIController->On_Init();
    
    MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1008, this, &EditerARGameModule::OnGetProductList);
    
}
void EditerARGameModule::On_Start()
{
    m_CurrentUIController->On_Start();
    
}
void EditerARGameModule::On_Delete()
{
    MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1008, this);
    
    if (m_CurrentUIController != nullptr)
    {
        delete m_CurrentUIController;
    }
}
void EditerARGameModule::GetProductList()
{
    /*TSharedPtr<FJsonObject> t_jsonObject = MakeShareable(new FJsonObject);
    
    t_jsonObject->SetNumberField(TEXT("categoryId"), 0);
    t_jsonObject->SetNumberField(TEXT("lastId"), 0);
    t_jsonObject->SetNumberField(TEXT("size"), 10);
    t_jsonObject->SetNumberField(TEXT("typeId"), 0);
    t_jsonObject->SetNumberField(TEXT("materialId"), 0);
    t_jsonObject->SetNumberField(TEXT("innerDiameterId"), 0);*/

	FString appendUrl = FString::Printf(TEXT("categoryId=%i&lastId=%i&size=%i&typeId=%i&materialId=%i&innerDiameterId=%i"),0, 0, 10, 0, 0, 0);


	FString cookie = UserInfo::Get()->GetCookie();
	FString token = UserInfo::Get()->GetToken();

	FString httpUrl = Data_M->GetURL(1008);
    HttpMsg * msg = new HttpMsg(Msg_HttpRequest, 1008, httpUrl, appendUrl,true,cookie,token);

    msg_ptr mMsg(msg);
    
    MsgCenter::GetInstance()->SendMsg(mMsg);
}
void EditerARGameModule::OnGetProductList(msg_ptr _msg)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : EditerARGameModule::OnGetProductList : "));
    TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
    
	RuntimeTDataManager::GetInstance()->DecodeGoodsList(jsonData);

	msg_ptr msg(new LocalMsg(Msg_Local,2008,nullptr));
	MsgCenter::GetInstance()->SendMsg(msg);
}
