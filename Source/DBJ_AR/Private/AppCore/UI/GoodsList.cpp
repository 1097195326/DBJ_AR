#include "GoodsList.h"
#include "RuntimeTDataManager.h"
#include "GoodsList_Icon.h"
#include "UIManager.h"

void UGoodsList::On_Init()
{
    if (UButton * button = (UButton*)GetWidgetFromName("ViewButton"))
    {
        m_ViewButton = button;
        m_ViewButton->OnClicked.AddDynamic(this, &UGoodsList::OnButtonClick);
    }
	if (UScrollBox * scrollBox = (UScrollBox*)GetWidgetFromName("IconScrolBox"))
	{
		m_IconScrolBox = scrollBox;
	}
	if (UGridPanel * gridPanel = (UGridPanel*)GetWidgetFromName("IconList"))
	{
		m_IconList = gridPanel;
	}
	InitView();
    
}
void UGoodsList::InitView()
{
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
				mGridSlot->SetPadding(FMargin(20.f, 0.0f, 0.f, 30.f));
			}
			else
			{
				mGridSlot->SetPadding(FMargin(20.f, 0.0f, 0.f, 30.f));
			}
			
		}

	}
}
void UGoodsList::OnButtonClick()
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UTestUIB::OnButtonClick : "));

}
