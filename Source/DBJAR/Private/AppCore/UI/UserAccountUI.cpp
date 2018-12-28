#include "UserAccountUI.h"
#include "UIManager.h"
#include "UserInfo.h"
#include "EditerARGameModule.h"
#include "RuntimeCDataManager.h"
#include "UserAccountItem.h"
#include "AppInstance.h"

void UUserAccountUI::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("BackButton"))
    {
		m_BackButton = widget;
		
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("SettingButton"))
	{
		m_SettingButton = widget;
		
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("ToUserInfoButton"))
	{
		m_ToUserInfoButton = widget;
		
	}
	if (UImage * widget = (UImage*)GetWidgetFromName("UserImage"))
	{
		m_UserImage = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("CompanyName"))
	{
		m_CompanyName = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("UserName"))
	{
		m_UserName = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("AccountTypeText"))
	{
		m_AccountTypeText = widget;
	}
	if (UScrollBox * widget = (UScrollBox*)GetWidgetFromName("OrderListScroll"))
	{
		m_OrderListScroll = widget;
	}
	if (UCanvasPanel * canvasPanel = (UCanvasPanel*)GetWidgetFromName("ContentEmpty"))
	{
		m_ContentEmptyPanel = canvasPanel;
		m_ContentEmptyPanel->SetVisibility(ESlateVisibility::Hidden);
	}
	m_LastId = 0;
	m_IsRequest = false;
}
void UUserAccountUI::On_Start()
{
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(this, 0), this);

    UIManager::GetInstance()->RegisterButton(1, m_BackButton, this, &UUserAccountUI::OnButtonClick);
    UIManager::GetInstance()->RegisterButton(2, m_SettingButton, this, &UUserAccountUI::OnButtonClick);
    UIManager::GetInstance()->RegisterButton(3, m_ToUserInfoButton, this, &UUserAccountUI::OnButtonClick);
    
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2010, this, &UUserAccountUI::OnGetAccountOrder);

	FString companyName = UserInfo::Get()->GetLocalData().companyName;
	FString userName = UserInfo::Get()->GetLocalData().name;
	FString userPhone = UserInfo::Get()->GetLocalData().phone;
	FString accountTypeS = UserInfo::Get()->GetLocalData().limit ? TEXT("限制账号") : TEXT("正式账号");

	m_CompanyName->SetText(FText::FromString(companyName));
	m_UserName->SetText(FText::FromString(FString::Printf(TEXT("%s    %s"),*userName,*userPhone)));
	m_AccountTypeText->SetText(FText::FromString(accountTypeS));

	UTexture2D * texture = UAppInstance::GetInstance()->LoadImageFromDisk(this, UserInfo::Get()->GetLocalData().IconPath);
	if (texture && texture->IsValidLowLevel())
	{
//        m_UserImage->SetBrushFromTexture(texture);
        m_UserImage->GetDynamicMaterial()->SetTextureParameterValue("headTexture", texture);
	}

	m_IsRequest = true;
	EditerARGameModule::GetInstance()->GetAccountOrder(m_LastId);
}
void UUserAccountUI::On_Tick(float delta)
{
	if (m_OrderListScroll && !m_IsRequest)
	{
		float xx = m_OrderListScroll->GetScrollOffset();
		float yy = m_OrderListScroll->GetDesiredSize().Y;
		UCanvasPanelSlot * scrollSlot = (UCanvasPanelSlot*)m_OrderListScroll->Slot;
		if (xx + scrollSlot->GetSize().Y >= yy)
		{
			ReloadData();
		}
	}
}
void UUserAccountUI::On_Delete()
{
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(this, 0), m_ParentUI);

    UIManager::GetInstance()->UnRegisterButton(m_BackButton);
    UIManager::GetInstance()->UnRegisterButton(m_SettingButton);
    UIManager::GetInstance()->UnRegisterButton(m_ToUserInfoButton);
    
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2010, this);
}
void UUserAccountUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));
	switch (_index)
	{
	case 1:
	{// remove
		RemoveFromParent();
	}break;
	case 2:
	{// setting
		//EditerARGameModule::GetInstance()->GetAccountOrder();
		UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("SettingUI"));
		baseUI->AddToViewport();
		RemoveFromParent();
	}break;
	case 3:
	{// to edit user info
		UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("EditUserInfoUI"));
		baseUI->AddToViewport();
		RemoveFromParent();
	}break;
	}
}
void UUserAccountUI::OnGetAccountOrder(msg_ptr _msg)
{
	TSharedPtr<FJsonObject> jsonObject = _msg->GetJsonObject();
	if (jsonObject->GetIntegerField(TEXT("code")) != 200)
	{
		m_IsRequest = false;
		return;
	}
	if (m_OrderListScroll == nullptr)
	{
		return;
	}
	const TSharedPtr<FJsonObject> jsonData = jsonObject->GetObjectField("data");
	m_LastId = jsonData->GetIntegerField(TEXT("lastId"));


	/*m_OrderListScroll->ClearChildren();
	m_OrderListScroll->ScrollToStart();*/
	TArray<R_Order*> OrderList = RuntimeCDataManager::GetInstance()->GetAccountOrderList();
	
	if (OrderList.Num() > 0)
	{
		m_ContentEmptyPanel->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		m_ContentEmptyPanel->SetVisibility(ESlateVisibility::Visible);
	}
	for (int i = 0; i < OrderList.Num(); i++)
	{
		UUserAccountItem * item = (UUserAccountItem*)UIManager::GetInstance()->OpenUI(TEXT("UserAccountItem"),this);
		
		UScrollBoxSlot * slot = (UScrollBoxSlot*)m_OrderListScroll->AddChild(item);
		slot->SetPadding(FMargin(0.f,24.f,0.f,0.f));
		item->SetOrder(OrderList[i]);

	}
	m_IsRequest = false;
}
void UUserAccountUI::ReloadData()
{
	if (!m_IsRequest && m_LastId != 0)
	{
		m_IsRequest = true;
		UE_LOG(LogTemp, Log, TEXT("zhx : GoodsList reload Data"));
		EditerARGameModule::GetInstance()->GetAccountOrder(m_LastId);

	}
}
