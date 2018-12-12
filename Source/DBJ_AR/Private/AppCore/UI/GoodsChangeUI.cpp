#include "GoodsChangeUI.h"
#include "UIManager.h"
#include "RuntimeTDataManager.h"
#include "EditerARGameModule.h"
#include "UserPawn.h"

void UGoodsChangeUI::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("SureButton"))
    {
        m_SureButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_SureButton, this, &UGoodsChangeUI::OnButtonClick);
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("CancelButton"))
	{
		m_CancelButton = widget;
		UIManager::GetInstance()->RegisterButton(2, m_CancelButton, this, &UGoodsChangeUI::OnButtonClick);
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("BackButton"))
	{
		m_BackButton = widget;
		UIManager::GetInstance()->RegisterButton(3, m_BackButton, this, &UGoodsChangeUI::OnButtonClick);
	}
	if (UScrollBox * widget = (UScrollBox*)GetWidgetFromName("ChangeScroll"))
	{
		m_ScrollBox = widget;
	}
	if (UGridPanel * widget = (UGridPanel*)GetWidgetFromName("ChangeList"))
	{
		m_GridPanel = widget;
	}

	m_CurrentGoodsData = nullptr;
	m_LastId = 0;
}
void UGoodsChangeUI::On_Start()
{
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2013, this, &UGoodsChangeUI::OnGetChangeList);

	m_ProductId = AUserPawn::GetInstance()->GetChangeProductId();
	//m_ProductId = 10;
	EditerARGameModule::GetInstance()->GetChangeList(m_ProductId,m_LastId);
}
void UGoodsChangeUI::On_Tick(float delta)
{
	if (m_ScrollBox && !m_IsRequest)
	{
		float xx = m_ScrollBox->GetScrollOffset();
		float yy = m_ScrollBox->GetDesiredSize().X;
		UCanvasPanelSlot * scrollSlot = (UCanvasPanelSlot*)m_ScrollBox->Slot;
		if (xx + scrollSlot->GetSize().X >= yy)
		{
			ReloadData();
		}
	}
}
void UGoodsChangeUI::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2013, this);

}
void UGoodsChangeUI::OnButtonClick(int id)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));
	switch (id)
	{
	case 1:
	{
		if (m_CurrentGoodsData && m_CurrentGoodsData->m_FilePathList.Num()>0)
		{
			AUserPawn::GetInstance()->SureChangeSelectModel(m_CurrentGoodsData);
		}
		RemoveFromParent();
	}break;
	case 2:
	{
		AUserPawn::GetInstance()->CancelChangeSelectModel();
		RemoveFromParent();
	}break;
	case 3:
	{
		AUserPawn::GetInstance()->CancelChangeSelectModel();
		RemoveFromParent();
	}break;
	default:
		break;
	}
}
void UGoodsChangeUI::OnGetChangeList(msg_ptr _msg)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : OnGetChangeList get msg: %d"), 1);
	TSharedPtr<FJsonObject> jsonObject = _msg->GetJsonObject();
	if (jsonObject->GetIntegerField(TEXT("code")) != 200)
	{
		m_IsRequest = false;
		return;
	}
	if (m_ScrollBox == nullptr || m_GridPanel == nullptr)
	{
		return;
	}
	const TSharedPtr<FJsonObject> jsonData = jsonObject->GetObjectField("data");
	m_LastId = jsonData->GetIntegerField(TEXT("lastId"));

	int CurrentNum  = m_GoodsListIcons.Num();
	/*m_ScrollBox->ScrollToStart();
	m_GridPanel->ClearChildren();*/
    TArray<GoodsData*> goods = RuntimeTDataManager::GetInstance()->GetChangeGoodsList();

	for (int i = 0; i < goods.Num(); i++)
	{
		UGoodsList_Icon * icon = (UGoodsList_Icon*)UIManager::GetInstance()->OpenUI(TEXT("GoodsChangeIcon"));

		if (icon->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Log, TEXT("zhx goods list add icon %d"), i);

			UGridSlot * mGridSlot = m_GridPanel->AddChildToGrid(icon);
			int mIndex = CurrentNum + i;//CurrentNum + j;
			mGridSlot->SetRow(mIndex % 2);
			mGridSlot->SetColumn(mIndex / 2);

			GoodsData * data = goods[i];
			icon->SetData(data ,true);
			icon->SetParentUI(this);
			if (mIndex % 2 > 0)
			{
				mGridSlot->SetPadding(FMargin(10.f, 10.f, 10.f, 10.f));
			}
			else
			{
				mGridSlot->SetPadding(FMargin(10.f, 10.f, 10.f, 10.f));
			}
			m_GoodsListIcons.Add(icon);
		}
	}
	m_IsRequest = false;

}
void UGoodsChangeUI::SelectChangeIcon(UGoodsList_Icon * _icon)
{
	for (int i = 0;i < m_GoodsListIcons.Num();i++)
	{
		UGoodsList_Icon * icon = m_GoodsListIcons[i];
		if (icon == _icon)
		{
			icon->ShowSelectIcon(true);
			m_CurrentGoodsData = icon->GetData();
			AUserPawn::GetInstance()->ChangeSelectModel(m_CurrentGoodsData->LoadMesh());
		}
		else
		{
			icon->ShowSelectIcon(false);
		}

	}
}
void UGoodsChangeUI::ReloadData()
{
	if (!m_IsRequest && UGoodsList_Icon::CanDownPak && m_LastId != 0)
	{
		m_IsRequest = true;
		UE_LOG(LogTemp, Log, TEXT("zhx : UGoodsChangeUI reload Data"));
		EditerARGameModule::GetInstance()->GetChangeList(m_ProductId, m_LastId);


	}
}
//void UGoodsChangeUI::SetData(int _id, FString _path)
//{
//	m_ProductId = _id;
//	m_ModelGamePath = _path;
//}
