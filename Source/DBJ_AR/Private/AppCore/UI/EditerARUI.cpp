#include "EditerARUI.h"
#include "UIManager.h"
#include "EditerARGameModule.h"
#include "AppInstance.h"
#include "GoodsList.h"
#include "GoodsChangeUI.h"
#include "UserPawn.h"
#include "UserAccountUI.h"
#include "RuntimeRDataManager.h"

void UEditerARUI::On_Init()
{
    if (UButton *widget = Cast<UButton>(GetWidgetFromName("ProductListButton")))
    {
        m_ProductListButton = widget;
        
    }
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("ChangeButton")))
	{
		m_ChangeButton = widget;
		m_ChangeButton->SetVisibility(ESlateVisibility::Hidden);
		
	}
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("DeleteButton")))
	{
		m_DeleteButton = widget;
		m_DeleteButton->SetVisibility(ESlateVisibility::Hidden);
		
	}
    //top button list
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("ShowListButton")))
	{
		m_ShowlistButton = widget;
		
	}
	if (UScrollBox *widget = Cast<UScrollBox>(GetWidgetFromName("ShowListPanel")))
	{
		m_ShowlistPanel = widget;
		m_ShowlistPanel->SetVisibility(ESlateVisibility::Hidden);
	}
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("CloseListButton")))
	{
		m_CloseListButton = widget;
		
	}if (UButton *widget = Cast<UButton>(GetWidgetFromName("AcountButton")))
	{
		m_AcountButton = widget;
		
	}if (UButton *widget = Cast<UButton>(GetWidgetFromName("AdressButton")))
	{
		m_AddressButton = widget;
		
	}if (UButton *widget = Cast<UButton>(GetWidgetFromName("OrderListButton")))
	{
		m_OrderlistButton = widget;
		
	}if (UButton *widget = Cast<UButton>(GetWidgetFromName("ShareButton")))
	{
		m_ShareButton = widget;
		
	}
}
void UEditerARUI::On_Start()
{
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2004, this, &UEditerARUI::OnGetCategoryList);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 3001, this, &UEditerARUI::OnSelectActor);


    UI_M->RegisterButton(1, m_ProductListButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(2, m_ChangeButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(3, m_DeleteButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(10, m_ShowlistButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(11, m_CloseListButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(12, m_AcountButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(13, m_AddressButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(14, m_OrderlistButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(15, m_ShareButton, this, &UEditerARUI::On_Button_Click);
}
void UEditerARUI::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2004, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 3001, this);
    
    UI_M->UnRegisterButton(m_ProductListButton);
    UI_M->UnRegisterButton(m_ChangeButton);
    UI_M->UnRegisterButton(m_DeleteButton);
    
    UI_M->UnRegisterButton(m_ShowlistButton);
    UI_M->UnRegisterButton(m_CloseListButton);
    UI_M->UnRegisterButton(m_AcountButton);
    UI_M->UnRegisterButton(m_AddressButton);
    UI_M->UnRegisterButton(m_OrderlistButton);
    UI_M->UnRegisterButton(m_ShareButton);
	
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
		case 10:
		{// show button list
			m_ShowlistButton->SetVisibility(ESlateVisibility::Hidden);
			m_ShowlistPanel->SetVisibility(ESlateVisibility::Visible);
		}break;
		case 11:
		{// close buuton list
			m_ShowlistButton->SetVisibility(ESlateVisibility::Visible);
			m_ShowlistPanel->SetVisibility(ESlateVisibility::Hidden);
		}break;
		case 12:
		{// user account 
			UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("UserAccountUI"));
			baseUI->AddToViewport();
		}break;
		case 13:
		{// reset AR session
			//AUserPawn::GetInstance()->StopARSession();
			AUserPawn::GetInstance()->DeleteAllARActor();
			//AUserPawn::GetInstance()->StartARSession();
		}break;
		case 14:
		{//to order list 
			//RemoveFromParent();
			RuntimeRDataManager::GetInstance()->MakeOrder();
			UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("MakeOrderUI"));
			baseUI->AddToViewport();
			//baseUI->addto
		}break;
		case 15:
		{// share 
			AUserController::GetInstance()->MakeScreenShot();
		}break;
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
