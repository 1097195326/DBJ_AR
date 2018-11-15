#include "GoodsList.h"
#include "RuntimeTDataManager.h"
#include "GoodsList_Icon.h"
#include "UIManager.h"
#include "EditerARGameModule.h"


void UGoodsList::On_Init()
{
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2008, this, &UGoodsList::OnGetProductList);

    if (UButton * button = (UButton*)GetWidgetFromName("BackButton"))
    {
		m_BackButton = button;
		m_BackButton->OnClicked.AddDynamic(this, &UGoodsList::OnButtonClick);
    }
	if (UScrollBox * scrollBox = (UScrollBox*)GetWidgetFromName("IconScrolBox"))
	{
		m_IconScrolBox = scrollBox;
	}
	if (UGridPanel * gridPanel = (UGridPanel*)GetWidgetFromName("IconList"))
	{
		m_IconList = gridPanel;
	}
	if (UVerticalBox * verticalBox = (UVerticalBox*)GetWidgetFromName("CategoryButton"))
	{
		m_CategoryView = verticalBox;
	}
	InitView();

}
void UGoodsList::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2008, this);
}
void UGoodsList::InitView()
{
    m_CategoryView->ClearChildren();
    
	int firstButton = 0;
	TArray<GoodsListCategoryData> CategoryListData = RuntimeTDataManager::GetInstance()->GetCategoryList();
	
	for (int i = 0; i < CategoryListData.Num(); i++)
	{
		UGoodsListButton * button = (UGoodsListButton*)UIManager::GetInstance()->OpenUI(TEXT("GoodsListButton"));
		if (button->IsValidLowLevel())
		{
			UVerticalBoxSlot * slot = (UVerticalBoxSlot *)m_CategoryView->AddChild(button);
			GoodsListCategoryData data = CategoryListData[i];
			button->SetData(data.id, data.name,this);
			m_ListButtons.Add(button);
			if (i == 0)
			{
				firstButton = data.id;
			}
		}
	}
	SelectCategoryButton(firstButton);
}
void UGoodsList::OnGetProductList(msg_ptr _msg)
{
	m_IconList->ClearChildren();

	TArray<GoodsData*> goods = RuntimeTDataManager::GetInstance()->GetCurrentGoodsList();
	for (int i = 0; i < goods.Num(); i++)
	{
		UGoodsList_Icon * icon = (UGoodsList_Icon*)UIManager::GetInstance()->OpenUI(TEXT("GoodsListIcon"));

		if (icon->IsValidLowLevel())
		{
			UGridSlot * mGridSlot = m_IconList->AddChildToGrid(icon);
			int mIndex = i;//CurrentNum + j;
			mGridSlot->SetRow(mIndex / 2);
			mGridSlot->SetColumn(mIndex % 2);

			GoodsData * data = goods[i];
			icon->SetData(data);
			icon->SetParentUI(this);
			if (mIndex % 2 > 0)
			{
				mGridSlot->SetPadding(FMargin(10.f, 20.0f, 0.f, 0.f));
			}
			else
			{
				mGridSlot->SetPadding(FMargin(0.f, 20.0f, 10.f, 0.f));
			}
		}
	}
}
void UGoodsList::SelectCategoryButton(int _id)
{
	for (int i = 0; i< m_ListButtons.Num(); i++)
	{
		UGoodsListButton * button = m_ListButtons[i];
		if (button->m_Id == _id)
		{
			button->SetButtonSelect(true);

			EditerARGameModule::GetInstance()->GetProductList(_id);
		}
		else
		{
			button->SetButtonSelect(false);
		}
	}
}
void UGoodsList::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));
	RemoveFromParent();

}
