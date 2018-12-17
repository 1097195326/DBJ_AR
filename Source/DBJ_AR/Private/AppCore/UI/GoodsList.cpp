#include "GoodsList.h"
#include "RuntimeTDataManager.h"
#include "MsgCenter.h"
#include "UIManager.h"
#include "EditerARGameModule.h"


void UGoodsList::On_Init()
{
    UE_LOG(LogTemp,Log,TEXT("zhx : goodslist ui init"));
	

    if (UButton * button = (UButton*)GetWidgetFromName("BackButton"))
    {
		m_BackButton = button;
		UIManager::GetInstance()->RegisterButton(1, m_BackButton, this, &UGoodsList::OnButtonClick);
    }
	if (UButton * button = (UButton*)GetWidgetFromName("FilterButton"))
	{
		m_FilterButton = button;
		UIManager::GetInstance()->RegisterButton(2, m_FilterButton, this, &UGoodsList::OnButtonClick);
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
	
	m_IsRequest = false;

	m_CurrentSelectId = 0;
	m_TypeIndex = 0;
	m_MaterialIndex = 0;
	m_InnerIndex = 0;
}
void UGoodsList::On_Start()
{
    UE_LOG(LogTemp,Log,TEXT("zhx : goodslist ui start"));
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2008, this, &UGoodsList::OnGetProductList);
    
    UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(this, 0), this);
    
    InitView();
}
void UGoodsList::On_Tick(float delta)
{
	if (m_IconScrolBox && !m_IsRequest && UGoodsList_Icon::CanDownPak)
	{
		float xx = m_IconScrolBox->GetScrollOffset();
		float yy = m_IconScrolBox->GetDesiredSize().Y;
		UCanvasPanelSlot * scrollSlot = (UCanvasPanelSlot*)m_IconScrolBox->Slot;
		if (xx + scrollSlot->GetSize().Y >= yy)
		{
			ReloadData();
		}
	}
}
void UGoodsList::On_Delete()
{
    m_IconScrolBox = nullptr;
    m_IconList = nullptr;
    
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(this, 0), m_ParentUI);

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
	TSharedPtr<FJsonObject> jsonObject = _msg->GetJsonObject();
	if (jsonObject->GetIntegerField(TEXT("code")) != 200)
	{
		m_IsRequest = false;
		return;
	}
    if(m_IconScrolBox == nullptr || m_IconList == nullptr)
    {
        return;
    }
	const TSharedPtr<FJsonObject> jsonData = jsonObject->GetObjectField("data");
	
	m_LastId = jsonData->GetIntegerField(TEXT("lastId"));

    /*m_IconScrolBox->ScrollToStart();
	m_IconList->ClearChildren();*/
     UE_LOG(LogTemp,Log,TEXT("zhx : get msg: %d"),2);
	TArray<GoodsData*> goods = RuntimeTDataManager::GetInstance()->GetCurrentGoodsList();
    
    UE_LOG(LogTemp,Log,TEXT("zhx : good num : %d"),goods.Num());
	int CurrentNum = m_IconArray.Num();
	for (int i = 0; i < goods.Num(); i++)
	{
		UGoodsList_Icon * icon = (UGoodsList_Icon*)UIManager::GetInstance()->OpenUI(TEXT("GoodsListIcon"),this);

		if (icon->IsValidLowLevel())
		{
            UE_LOG(LogTemp,Log,TEXT("zhx goods list add icon %d"),i);
			m_IconArray.Add(icon);

			UGridSlot * mGridSlot = m_IconList->AddChildToGrid(icon);
			int mIndex = CurrentNum + i;//CurrentNum + j;
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

	m_IsRequest = false;
}
void UGoodsList::SelectCategoryButton(int _id)
{
	if (!UGoodsList_Icon::CanDownPak)
	{
		UIManager::GetInstance()->TopHintText(TEXT("正在下载资源中..."));
		return;
	}
	m_IconScrolBox->ScrollToStart();
	m_IconList->ClearChildren();
	m_IconArray.Empty();

	for (int i = 0; i< m_ListButtons.Num(); i++)
	{
		UGoodsListButton * button = m_ListButtons[i];
		if (button->m_Id == _id)
		{
			button->SetButtonSelect(true);
			m_CurrentSelectId = _id;
			m_LastId = 0;
			m_IsRequest = true;
			EditerARGameModule::GetInstance()->GetProductList(m_CurrentSelectId,m_LastId,m_TypeIndex,m_MaterialIndex,m_InnerIndex);
		}
		else
		{
			button->SetButtonSelect(false);
		}
	}
}
void UGoodsList::ReloadData(bool _clear)
{
	if (_clear)
	{
		m_IconScrolBox->ScrollToStart();
		m_IconList->ClearChildren();
		m_IconArray.Empty();
		m_IsRequest = true;
		m_LastId = 0;
		UE_LOG(LogTemp, Log, TEXT("zhx : GoodsList reload Data"));
		EditerARGameModule::GetInstance()->GetProductList(m_CurrentSelectId, m_LastId, m_TypeIndex, m_MaterialIndex, m_InnerIndex);

	}else if (!m_IsRequest && UGoodsList_Icon::CanDownPak && m_LastId != 0)
	{
		m_IsRequest = true;
		UE_LOG(LogTemp, Log, TEXT("zhx : GoodsList reload Data"));
		EditerARGameModule::GetInstance()->GetProductList(m_CurrentSelectId, m_LastId, m_TypeIndex, m_MaterialIndex, m_InnerIndex);

	}
}
void UGoodsList::OnButtonClick(int _index)
{
	if (!UGoodsList_Icon::CanDownPak)
	{
		UIManager::GetInstance()->TopHintText(TEXT("正在下载资源中..."));
		return;
	}

    UE_LOG(LogTemp, Log, TEXT("zhx : UGoodsList::OnButtonClick : "));
	switch (_index)
	{
	case 1:
	{
		RemoveFromViewport();
	}break;
	case 2:
	{
		UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("GoodsFilterUI"),this);
		baseUI->AddToViewport();
	}break;
	}

}