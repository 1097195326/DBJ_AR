#include "GoodsFilterUI.h"
#include "UIManager.h"
#include "MsgCenter.h"
#include "EditerARGameModule.h"
#include "GoodsList.h"


void UGoodsFilterUI::On_Init()
{
	if (UVerticalBox * widget = (UVerticalBox*)GetWidgetFromName("ViewVerticalBox"))
	{
		m_ViewVerticalBox = widget;
	}
    if (UButton * widget = (UButton*)GetWidgetFromName("CancelButton"))
    {
        m_CancelButton = widget;
		UIManager::GetInstance()->RegisterButton(1, m_CancelButton, this, &UGoodsFilterUI::OnButtonClick);
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("SureButton"))
	{
		m_SureButton = widget;
		UIManager::GetInstance()->RegisterButton(2, m_SureButton, this, &UGoodsFilterUI::OnButtonClick);
	}
    
	m_TypeIndex = 0;
	m_MaterialIndex = 0;
	m_InnerIndex = 0;

	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2005, this, &UGoodsFilterUI::OnGetGoodsType);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2006, this, &UGoodsFilterUI::OnGetMaterials);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2007, this, &UGoodsFilterUI::OnGetInnerDiameters);
}
void UGoodsFilterUI::On_Start()
{
	m_ReceiveNum = 0;
	EditerARGameModule::GetInstance()->GetGoodsType();
	EditerARGameModule::GetInstance()->GetInnerDiameters();
	EditerARGameModule::GetInstance()->GetMaterials();

}
void UGoodsFilterUI::On_Delete()
{
	UIManager::GetInstance()->UnRegisterButton(m_CancelButton);
	UIManager::GetInstance()->UnRegisterButton(m_SureButton);

	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2005, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2006, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2007, this);
}
void UGoodsFilterUI::InitView()
{
	++m_ReceiveNum;
	if (m_ReceiveNum >= 3)
	{
		UGoodsList * goodsList = (UGoodsList*)m_ParentUI;

		UGoodsFilterItem * typeItem = (UGoodsFilterItem*)UIManager::GetInstance()->OpenUI(TEXT("GoodsFilterItem"),this);
		m_ViewVerticalBox->AddChild(typeItem);
		typeItem->SetData(1,m_TypeData,goodsList->m_TypeIndex);

		UGoodsFilterItem * materialItem = (UGoodsFilterItem*)UIManager::GetInstance()->OpenUI(TEXT("GoodsFilterItem"),this);
		m_ViewVerticalBox->AddChild(materialItem);
		materialItem->SetData(2, m_MaterialData,goodsList->m_MaterialIndex);

		UGoodsFilterItem * innerItem = (UGoodsFilterItem*)UIManager::GetInstance()->OpenUI(TEXT("GoodsFilterItem"),this);
		m_ViewVerticalBox->AddChild(innerItem);
		innerItem->SetData(3, m_InnerData,goodsList->m_InnerIndex);
	}
}
void UGoodsFilterUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UGoodsFilterUI::OnButtonClick : "));
	switch (_index)
	{
	case 1:
	{
		RemoveFromParent();
	}break;
	case 2:
	{
		RemoveFromParent();
		UGoodsList * baseUI = (UGoodsList*)m_ParentUI;
		baseUI->m_TypeIndex = m_TypeIndex;
		baseUI->m_MaterialIndex = m_MaterialIndex;
		baseUI->m_InnerIndex = m_InnerIndex;
		baseUI->ReloadData();
	}break;
	}
}
void UGoodsFilterUI::OnGetInnerDiameters(msg_ptr _msg)
{
	m_InnerData.Empty();

	TSharedPtr<FJsonObject> jsonObject = _msg->GetJsonObject();
	TArray<TSharedPtr<FJsonValue>> dataList = jsonObject->GetArrayField(TEXT("data"));
	for (int i = 0; i < dataList.Num(); i++)
	{
		TSharedPtr<FJsonObject> value = dataList[i]->AsObject();
		IdData data;
		data.Id = value->GetNumberField(TEXT("id"));
		data.Name = value->GetStringField(TEXT("name"));
		m_InnerData.Add(data);
	}
	InitView();
}
void UGoodsFilterUI::OnGetMaterials(msg_ptr _msg)
{
	m_MaterialData.Empty();
	TSharedPtr<FJsonObject> jsonObject = _msg->GetJsonObject();
	TArray<TSharedPtr<FJsonValue>> dataList = jsonObject->GetArrayField(TEXT("data"));
	for (int i = 0; i < dataList.Num(); i++)
	{
		TSharedPtr<FJsonObject> value = dataList[i]->AsObject();
		IdData data;
		data.Id = value->GetNumberField(TEXT("id"));
		data.Name = value->GetStringField(TEXT("name"));
		m_MaterialData.Add(data);
	}
	InitView();

}
void UGoodsFilterUI::OnGetGoodsType(msg_ptr _msg)
{
	m_TypeData.Empty();
	TSharedPtr<FJsonObject> jsonObject = _msg->GetJsonObject();
	TArray<TSharedPtr<FJsonValue>> dataList = jsonObject->GetArrayField(TEXT("data"));
	for (int i = 0; i < dataList.Num(); i++)
	{
		TSharedPtr<FJsonObject> value = dataList[i]->AsObject();
		IdData data;
		data.Id = value->GetNumberField(TEXT("id"));
		data.Name = value->GetStringField(TEXT("name"));
		m_TypeData.Add(data);
	}
	InitView();

}