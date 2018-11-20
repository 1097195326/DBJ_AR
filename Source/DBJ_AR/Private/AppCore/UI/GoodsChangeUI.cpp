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
	
}
void UGoodsChangeUI::On_Start()
{
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2013, this, &UGoodsChangeUI::OnGetChangeList);

	m_ProductId = AUserPawn::GetInstance()->GetChangeProductId();
	EditerARGameModule::GetInstance()->GetChangeList(m_ProductId);
	//test
	OnGetChangeList(nullptr);
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
		if (m_CurrentGoodsData && !m_CurrentGoodsData->GamePath.IsEmpty())
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
		RemoveFromParent();
	}break;
	default:
		break;
	}
}
void UGoodsChangeUI::OnGetChangeList(msg_ptr _msg)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : OnGetChangeList get msg: %d"), 1);
	if (m_ScrollBox == nullptr || m_GridPanel == nullptr)
	{
		return;
	}
	m_ScrollBox->ScrollToStart();
	m_GridPanel->ClearChildren();
	//TArray<GoodsData*> goods = RuntimeTDataManager::GetInstance()->GetChangeGoodsList();
	TArray<GoodsData*> goods = RuntimeTDataManager::GetInstance()->GetCurrentGoodsList();

	for (int i = 0; i < goods.Num(); i++)
	{
		UGoodsList_Icon * icon = (UGoodsList_Icon*)UIManager::GetInstance()->OpenUI(TEXT("GoodsChangeIcon"));

		if (icon->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Log, TEXT("zhx goods list add icon %d"), i);

			UGridSlot * mGridSlot = m_GridPanel->AddChildToGrid(icon);
			int mIndex = i;//CurrentNum + j;
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
			AUserPawn::GetInstance()->ChangeSelectModel(m_CurrentGoodsData->GamePath);
		}
		else
		{
			icon->ShowSelectIcon(false);
		}

	}
}
//void UGoodsChangeUI::SetData(int _id, FString _path)
//{
//	m_ProductId = _id;
//	m_ModelGamePath = _path;
//}