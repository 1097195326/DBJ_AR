#include "EditerARUI.h"
#include "UIManager.h"
#include "EditerARGameModule.h"
#include "AppInstance.h"
#include "GoodsList.h"
#include "GoodsChangeUI.h"
#include "UserPawn.h"

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
		m_ChangeButton->SetVisibility(ESlateVisibility::Hidden);
		UI_M->RegisterButton(2, m_ChangeButton, this, &UEditerARUI::On_Button_Click);
	}
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("DeleteButton")))
	{
		m_DeleteButton = widget;
		m_DeleteButton->SetVisibility(ESlateVisibility::Hidden);
		UI_M->RegisterButton(3, m_DeleteButton, this, &UEditerARUI::On_Button_Click);
	}
    
}
void UEditerARUI::On_Start()
{
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2004, this, &UEditerARUI::OnGetCategoryList);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 3001, this, &UEditerARUI::OnSelectActor);


}
void UEditerARUI::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2004, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 3001, this);

    if (m_ProductListButton)
    {
        UI_M->UnRegisterButton(m_ProductListButton);
		m_ProductListButton = nullptr;
    }
	if (m_ChangeButton)
	{
		UI_M->UnRegisterButton(m_ChangeButton);
		m_ChangeButton = nullptr;
	}
	if (m_DeleteButton)
	{
		UI_M->UnRegisterButton(m_DeleteButton);
		m_DeleteButton = nullptr;
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
			UGoodsChangeUI * changeUI = (UGoodsChangeUI *)UIManager::GetInstance()->OpenUI(TEXT("GoodsChangeUI"));

			changeUI->AddToViewport();
            break;
        }
		case 3:
		{
			AUserPawn::GetInstance()->DeleteSelectARActor();
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
		
	}
	UGoodsList * goodsList = (UGoodsList *)UIManager::GetInstance()->OpenUI(TEXT("GoodsList"));
    UE_LOG(LogTemp,Log,TEXT("zhx : new goodslist : %lld"),goodsList);
    
	goodsList->AddToViewport();
}
void UEditerARUI::OnSelectActor(msg_ptr _msg)
{
	bool select = _msg->GetMsgContent<bool>();
	if (select)
	{
		m_ChangeButton->SetVisibility(ESlateVisibility::Visible);
		m_DeleteButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_ChangeButton->SetVisibility(ESlateVisibility::Hidden);
		m_DeleteButton->SetVisibility(ESlateVisibility::Hidden);
	}
}