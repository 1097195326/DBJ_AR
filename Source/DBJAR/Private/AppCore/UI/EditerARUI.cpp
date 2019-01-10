#include "EditerARUI.h"
#include "UIManager.h"
#include "EditerARGameModule.h"
#include "AppInstance.h"
#include "GoodsList.h"
#include "GoodsChangeUI.h"
#include "UserPawn.h"
#include "UserAccountUI.h"
#include "RuntimeRDataManager.h"
#include "AlertUI.h"
#include "UserInfo.h"
#include "Kismet/GameplayStatics.h"
#include "UserPlaneActor.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "ARBlueprintLibrary.h"

void UEditerARUI::On_Init()
{
    if (UButton *widget = Cast<UButton>(GetWidgetFromName("ProductListButton")))
    {
        m_ProductListButton = widget;
    }
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("ChangeButton")))
	{
		m_ChangeButton = widget;
		m_ChangeButton->SetVisibility(ESlateVisibility::Hidden);
	}
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("DeleteButton")))
	{
		m_DeleteButton = widget;
		m_DeleteButton->SetVisibility(ESlateVisibility::Hidden);
	}
	if (UCanvasPanel *widget = Cast<UCanvasPanel>(GetWidgetFromName("MainPanel")))
	{
		m_MainPanel = widget;
	}
	if (UCanvasPanel *widget = Cast<UCanvasPanel>(GetWidgetFromName("ScreenPanel")))
	{
		m_ScreenPanel = widget;
		m_ScreenPanel->SetVisibility(ESlateVisibility::Hidden);
		m_ShowEye = false;
	}
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("ScreenButton")))
	{
		m_ScreenButton = widget;
	}
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("ColseEyeButton")))
	{
		m_CloseEyeButton = widget;
		m_CloseEyeButton->SetVisibility(ESlateVisibility::Hidden);
	}
    //top button list
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("ShowListButton")))
	{
		m_ShowlistButton = widget;
	}
	if (UScrollBox *widget = Cast<UScrollBox>(GetWidgetFromName("ShowListPanel")))
	{
		m_ShowlistPanel = widget;
		m_ShowlistPanel->SetVisibility(ESlateVisibility::Hidden);
	}
	if (UButton *widget = Cast<UButton>(GetWidgetFromName("CloseListButton")))
	{
		m_CloseListButton = widget;
	}if (UButton *widget = Cast<UButton>(GetWidgetFromName("AcountButton")))
	{
		m_AcountButton = widget;
	}if (UButton *widget = Cast<UButton>(GetWidgetFromName("AdressButton")))
	{
		m_AddressButton = widget;
	}if (UButton *widget = Cast<UButton>(GetWidgetFromName("OrderListButton")))
	{
		m_OrderlistButton = widget;
	}if (UButton *widget = Cast<UButton>(GetWidgetFromName("ShareButton")))
	{
		m_ShareButton = widget;
	}if (UButton *widget = Cast<UButton>(GetWidgetFromName("OpenEyeButton")))
	{
		m_OpenEyeButton = widget;
	}
	if (UCanvasPanel *widget = Cast<UCanvasPanel>(GetWidgetFromName("LoadingPanel")))
	{
		m_LoadingPanel = widget;
		m_LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
	}
}
void UEditerARUI::On_Start()
{
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2004, this, &UEditerARUI::OnGetCategoryList);
	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 3001, this, &UEditerARUI::OnSelectActor);


    UI_M->RegisterButton(1, m_ProductListButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(2, m_ChangeButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(3, m_DeleteButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(10, m_ShowlistButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(11, m_CloseListButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(12, m_AcountButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(13, m_AddressButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(14, m_OrderlistButton, this, &UEditerARUI::On_Button_Click);
    UI_M->RegisterButton(15, m_ShareButton, this, &UEditerARUI::On_Button_Click);

	UI_M->RegisterButton(16, m_OpenEyeButton, this, &UEditerARUI::On_Button_Click);
	UI_M->RegisterButton(17, m_CloseEyeButton, this, &UEditerARUI::On_Button_Click);
	UI_M->RegisterButton(18, m_ScreenButton, this, &UEditerARUI::On_Button_Click);

#if PLATFORM_IOS
	ResetLoading();
#endif
}
void UEditerARUI::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2004, this);
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 3001, this);
    
    UI_M->UnRegisterButton(m_ProductListButton);
    UI_M->UnRegisterButton(m_ChangeButton);
    UI_M->UnRegisterButton(m_DeleteButton);
    
    UI_M->UnRegisterButton(m_ShowlistButton);
    UI_M->UnRegisterButton(m_CloseListButton);
    UI_M->UnRegisterButton(m_AcountButton);
    UI_M->UnRegisterButton(m_AddressButton);
    UI_M->UnRegisterButton(m_OrderlistButton);
    UI_M->UnRegisterButton(m_ShareButton);

	UI_M->UnRegisterButton(m_OpenEyeButton);
	UI_M->UnRegisterButton(m_CloseEyeButton);
	UI_M->UnRegisterButton(m_ScreenButton);
}
void UEditerARUI::On_Button_Click(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UEditerARUI::On_Button_Click : %d"), _index);
    switch (_index)
    {
        case 1:
        {
			EditerARGameModule::GetInstance()->GetCategoryList();
            break;
        }
        case 2:
        {
			
			UGoodsChangeUI * changeUI = (UGoodsChangeUI *)UIManager::GetInstance()->OpenUI(TEXT("GoodsChangeUI"),this);

			changeUI->AddToViewport();
            break;
        }
		case 3:
		{
			AUserPawn::GetInstance()->DeleteSelectARActor();
			break;
		}
		case 10:
		{// show button list
			m_ShowlistButton->SetVisibility(ESlateVisibility::Hidden);
			m_ShowlistPanel->SetVisibility(ESlateVisibility::Visible);
		}break;
		case 11:
		{// close buuton list
			m_ShowlistButton->SetVisibility(ESlateVisibility::Visible);
			m_ShowlistPanel->SetVisibility(ESlateVisibility::Hidden);
		}break;
		case 12:
		{// user account 
			UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("UserAccountUI"),this);
			baseUI->AddToViewport();
		}break;
		case 13:
		{// reset AR session
			//AUserPawn::GetInstance()->StopARSession();
			UAlertUI * alertUI = (UAlertUI*)UIManager::GetInstance()->OpenUI(TEXT("AlertUI"));
			alertUI->SetContentText(TEXT("删除所有绿植"));
			alertUI->BindSureFunctionCall(this, &UEditerARUI::DeleteAllUserActor);
			alertUI->AddToViewport(99);
			//AUserPawn::GetInstance()->StartARSession();
		}break;
		case 14:
		{//to order list 
			//RemoveFromParent();
			RuntimeRDataManager::GetInstance()->MakeOrder();
			UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("MakeOrderUI"), this);
			baseUI->AddToViewport();
			//baseUI->addto
		}break;
		case 15:
		{// share 
			AUserPawn::GetInstance()->CancelSelectActor();
			AUserController::GetInstance()->MakeScreenShot();
		}break;
		case 16:
		{// open eye
			m_MainPanel->SetVisibility(ESlateVisibility::Hidden);
			m_ScreenPanel->SetVisibility(ESlateVisibility::Visible);
            m_CloseEyeButton->SetVisibility(ESlateVisibility::Hidden);
            
			TArray<AActor *> allPlaneActor;
			UGameplayStatics::GetAllActorsOfClass(this, AUserPlaneActor::StaticClass(), allPlaneActor);
			for (int i = 0; i < allPlaneActor.Num(); i++)
			{
				AUserPlaneActor * actor = (AUserPlaneActor *)allPlaneActor[i];
				actor->StopDraw();
			}
			AUserPawn::GetInstance()->CancelSelectActor();
		}break;
		case 17:
		{// close eye
			m_MainPanel->SetVisibility(ESlateVisibility::Visible);
			m_ScreenPanel->SetVisibility(ESlateVisibility::Hidden);
			TArray<AActor *> allPlaneActor;
			UGameplayStatics::GetAllActorsOfClass(this, AUserPlaneActor::StaticClass(), allPlaneActor);
			for (int i = 0; i < allPlaneActor.Num(); i++)
			{
				AUserPlaneActor * actor = (AUserPlaneActor *)allPlaneActor[i];
				actor->StartDraw();
			}
		}break;
		case 18:
		{// screen button
			m_ShowEye = !m_ShowEye;
			m_ShowEye ? m_CloseEyeButton->SetVisibility(ESlateVisibility::Visible) : m_CloseEyeButton->SetVisibility(ESlateVisibility::Hidden);

		}break;
        default:
            break;
    }
    
}
void UEditerARUI::DeleteAllUserActor()
{
	AUserPawn::GetInstance()->DeleteAllARActor();
}
void UEditerARUI::OnGetCategoryList(msg_ptr _msg)
{
	//TSharedPtr<FJsonObject> data = _msg->GetJsonObject();
	//if (data->GetIntegerField(TEXT("code")) == 200)
	{
		
	}
	UGoodsList * goodsList = (UGoodsList *)UIManager::GetInstance()->OpenUI(TEXT("GoodsList"),this);
    UE_LOG(LogTemp,Log,TEXT("zhx : new goodslist : %lld"),goodsList);
    
	goodsList->AddToViewport();
}
void UEditerARUI::OnSelectActor(msg_ptr _msg)
{
	bool select = _msg->GetMsgContent<bool>();
	if (select)
	{
		m_ChangeButton->SetVisibility(ESlateVisibility::Visible);
		m_DeleteButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_ChangeButton->SetVisibility(ESlateVisibility::Hidden);
		m_DeleteButton->SetVisibility(ESlateVisibility::Hidden);
	}
}
// set loadding ui

void  UEditerARUI::UpdateLoading()
{
#if PLATFORM_WINDOWS
	return;
#endif
	TArray<UARPlaneGeometry*> planeGeometryArray = UARBlueprintLibrary::GetAllTrackedPlanes();
	if (planeGeometryArray.Num() > 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_timerHandle);
		m_LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
	}
}
void UEditerARUI::ResetLoading()
{
	m_LoadingPanel->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(m_timerHandle, this, &UEditerARUI::UpdateLoading, 0.1f, true, 0.f);
}
