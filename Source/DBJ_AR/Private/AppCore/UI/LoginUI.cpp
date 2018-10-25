#include "LoginUI.h"
#include "UIManager.h"


void ULoginUI::On_Init()
{
	if (UButton *button = Cast<UButton>(GetWidgetFromName("VeriCodeButton")))
	{
		m_VeriCode_Button = button;
		UI_M->RegisterButton(1, m_VeriCode_Button, this, &ULoginUI::On_Button_Click);
	}
	if (UButton *button = Cast<UButton>(GetWidgetFromName("LoginButton")))
	{
		m_Login_Button = button;
		UI_M->RegisterButton(2, m_Login_Button, this, &ULoginUI::On_Button_Click);
	}
	if (UEditableText * text = Cast<UEditableText>(GetWidgetFromName("PhoneBox")))
	{
		m_Phone_Text = text;
	}
	if (UEditableText * text = Cast<UEditableText>(GetWidgetFromName("VeriCodeBox")))
	{
		m_VeriCode_Text = text;
	}
	
}
void ULoginUI::On_Start()
{
	
	
}
void ULoginUI::On_Delete()
{
	if (m_Login_Button)
	{
		UI_M->UnRegisterButton(m_Login_Button);
	}
	if (m_VeriCode_Button)
	{
		UI_M->UnRegisterButton(m_VeriCode_Button);
	}
}
void ULoginUI::On_Button_Click(int _index)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : ULoginUI::On_Button_Click : %d"), _index);


}