#include "GoodsList.h"
#include "RuntimeTDataManager.h"
#include "GoodsList_Icon.h"
#include "UIManager.h"
#include "EditerARGameModule.h"


void UGoodsList::On_Init()
{
    UE_LOG(LogTemp,Log,TEXT("zhx : goodslist ui init"));
	

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
	

}
void UGoodsList::On_Start()
{
    UE_LOG(LogTemp,Log,TEXT("zhx : goodslist ui start"));
    MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2008, this, &UGoodsList::OnGetProductList);
    
    InitView();
}
void UGoodsList::On_Delete()
{
    m_IconScrolBox = nullptr;
    m_IconList = nullptr;
    
    UE_LOG(LogTemp,Log,TEXT("zhx : goodslist ui delete"));
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
    UE_LOG(LogTemp,Log,TEXT("zhx : get msg: %d"),1);
    if(m_IconScrolBox == nullptr || m_IconList == nullptr)
    {
        return;
    }
    m_IconScrolBox->ScrollToStart();
	m_IconList->ClearChildren();
     UE_LOG(LogTemp,Log,TEXT("zhx : get msg: %d"),2);
	TArray<GoodsData*> goods = RuntimeTDataManager::GetInstance()->GetCurrentGoodsList();
    
    UE_LOG(LogTemp,Log,TEXT("zhx : good num : %d"),goods.Num());
    
	for (int i = 0; i < goods.Num(); i++)
	{
		UGoodsList_Icon * icon = (UGoodsList_Icon*)UIManager::GetInstance()->OpenUI(TEXT("GoodsListIcon"));

		if (icon->IsValidLowLevel())
		{
            UE_LOG(LogTemp,Log,TEXT("zhx goods list add icon %d"),i);
            
			UGridSlot * mGridSlot = m_IconList->AddChildToGrid(icon);
			int mIndex = i;//CurrentNum + j;
			mGridSlot->SetRow(mIndex / 2);
			mGridSlot->SetColumn(mIndex % 2);

			GoodsData * data = goods[i];
			icon->SetData(data);
			icon->SetParentUI(this);
            if (mIndex % 2 > 0)
            {
				if (mIndex == 1)
				{
					mGridSlot->SetPadding(FMargin(12.f, 42.0f, 42.f, 0.f));
				}
				else
				{
					mGridSlot->SetPadding(FMargin(12.f, 24.0f, 42.f, 0.f));
				}
            }
            else
            {
				if (mIndex == 0)
				{
					mGridSlot->SetPadding(FMargin(42.f, 42.0f, 12.f, 0.f));
				}
				else
				{
					mGridSlot->SetPadding(FMargin(42.f, 24.0f, 12.f, 0.f));
				}
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
    UE_LOG(LogTemp, Log, TEXT("zhx : UGoodsList::OnButtonClick : "));
	RemoveFromViewport();

}
