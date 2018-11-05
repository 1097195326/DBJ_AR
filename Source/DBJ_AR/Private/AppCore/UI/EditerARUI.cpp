#include "EditerARUI.h"
#include "UIManager.h"
#include "EditerARGameModule.h"
#include "AppInstance.h"


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
    
//    MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1002, this, &ULoginUI::OnGetSmsCode);
//    MsgCenter::GetInstance()->RegisterMsgHeader(Msg_HttpRequest, 1001, this, &ULoginUI::OnUserLogin);
}
void UEditerARUI::On_Delete()
{
//    MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1002, this);
//    MsgCenter::GetInstance()->RemoveMsgHeader(Msg_HttpRequest, 1001, this);
    
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
