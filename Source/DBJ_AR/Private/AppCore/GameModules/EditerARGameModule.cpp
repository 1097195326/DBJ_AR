#include "EditerARGameModule.h"
#include "EditerARUIController.h"
#include "DataManager.h"



EditerARGameModule * EditerARGameModule::GetInstance()
{
    static EditerARGameModule m;
    return &m;
}
void EditerARGameModule::On_Init()
{
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
    TSharedPtr<FJsonObject> t_jsonObject = MakeShareable(new FJsonObject);
    
    t_jsonObject->SetNumberField(TEXT("categoryId"), 0);
    t_jsonObject->SetNumberField(TEXT("lastId"), 0);
    t_jsonObject->SetNumberField(TEXT("size"), 10);
    t_jsonObject->SetNumberField(TEXT("typeId"), 0);
    t_jsonObject->SetNumberField(TEXT("materialId"), 0);
    t_jsonObject->SetNumberField(TEXT("innerDiameterId"), 0);

	//bafa3b91c83546c2a1cc2b21d880893e
	FString token = TEXT("bafa3b91c83546c2a1cc2b21d880893e");
    
    HttpMsg * msg = new HttpMsg(Msg_HttpRequest, 1008, t_jsonObject,true,token);
    msg->m_httpUrl = Data_M->GetURL(msg->m_MsgId);
    msg_ptr mMsg(msg);
    
    MsgCenter::GetInstance()->SendMsg(mMsg);
}
void EditerARGameModule::OnGetProductList(msg_ptr _msg)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : EditerARGameModule::OnGetProductList : "));
    TSharedPtr<FJsonObject> jsonData = _msg->GetJsonObject();
    
    
}
