#include "EditerARUI.h"
#include "UIManager.h"
#include "EditerARGameModule.h"
#include "AppInstance.h"
#include "GoodsList.h"


void UEditerARUI::On_Init()
{
    if (UButton *button = Cast<UButton>(GetWidgetFromName("ProductListButton")))
    {
        m_ProductListButton = button;
        UI_M->RegisterButton(1, m_ProductListButton, this, &UEditerARUI::On_Button_Click);
    }
    
}
void UEditerARUI::On_Start()
{
    
    MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2008, this, &UEditerARUI::OnGetProductList);

}
void UEditerARUI::On_Delete()
{
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
			EditerARGameModule::GetInstance()->GetProductList();

            break;
        }
        case 2:
        {
            
            break;
        }
        default:
            break;
    }
    
}
void UEditerARUI::OnGetProductList(msg_ptr _msg)
{
	UGoodsList * goodsList = (UGoodsList *)UIManager::GetInstance()->OpenUI(TEXT("GoodsList"));
	goodsList->AddToViewport();

}