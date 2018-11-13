#include "EditerARUI.h"
#include "UIManager.h"
#include "EditerARGameModule.h"
#include "AppInstance.h"
#include "GoodsList.h"


void UEditerARUI::On_Init()
{
    if (UButton *widget = Cast<UButton>(GetWidgetFromName("ProductListButton")))
    {
        m_ProductListButton = widget;
        UI_M->RegisterButton(1, m_ProductListButton, this, &UEditerARUI::On_Button_Click);
    }
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("ChangeButton")))
	{
		m_ChangeButton = widget;
		UI_M->RegisterButton(2, m_ChangeButton, this, &UEditerARUI::On_Button_Click);
	}
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("DeleteButton")))
	{
		m_DeleteButton = widget;
		UI_M->RegisterButton(3, m_DeleteButton, this, &UEditerARUI::On_Button_Click);
	}
    
}
void UEditerARUI::On_Start()
{
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2004, this, &UEditerARUI::OnGetCategoryList);
    MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2008, this, &UEditerARUI::OnGetProductList);

}
void UEditerARUI::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2004, this);
    MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2008, this);
    
    if (m_ProductListButton)
    {
        UI_M->UnRegisterButton(m_ProductListButton);
    }
}
void UEditerARUI::On_Button_Click(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UEditerARUI::On_Button_Click : %d"), _index);
    switch (_index)
    {
        case 1:
        {
			
			EditerARGameModule::GetInstance()->GetCategoryList();
            break;
        }
        case 2:
        {
            
            break;
        }
		case 3:
		{

			break;
		}
        default:
            break;
    }
    
}
void UEditerARUI::OnGetCategoryList(msg_ptr _msg)
{
	//TSharedPtr<FJsonObject> data = _msg->GetJsonObject();
	//if (data->GetIntegerField(TEXT("code")) == 200)
	{
		EditerARGameModule::GetInstance()->GetProductList();
	}
	
}
void UEditerARUI::OnGetProductList(msg_ptr _msg)
{
	UGoodsList * goodsList = (UGoodsList *)UIManager::GetInstance()->OpenUI(TEXT("GoodsList"));
	goodsList->AddToViewport();

}