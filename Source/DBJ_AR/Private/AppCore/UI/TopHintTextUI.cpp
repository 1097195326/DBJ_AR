#include "TopHintTextUI.h"


void UTopHintTextUI::On_Init()
{
    if (UVerticalBox * widget = (UVerticalBox*)GetWidgetFromName("ShowTextView"))
    {
        m_ShowTextView = widget;
    }
	m_IsUpdate = false;
}
void UTopHintTextUI::InitText(const FString & hintText, float showSecond)
{
	m_ShowTime += showSecond;
	if (!m_IsUpdate)
	{
		m_IsUpdate = true;
		UTextBlock * showText = NewObject<UTextBlock>();
		showText->SetText(FText::FromString(hintText));
		showText->SetColorAndOpacity(FLinearColor(FColor::FromHex(TEXT("FFFFFFFF"))));
		showText->SetFont(FSlateFontInfo(TEXT("PingFang_Regular_Font"), 30));
		showText->SetJustification(ETextJustify::Center);
		m_ShowTextView->AddChild(showText);
		GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &UTopHintTextUI::OnTimerUpdate, 0.1f, true);
	}
	
}
void UTopHintTextUI::OnTimerUpdate()
{
	m_ShowTime -= 0.1f;
	if (m_ShowTime <= 0.f)
	{
		m_ShowTime = 0.f;
		m_IsUpdate = false;
		GetWorld()->GetTimerManager().ClearTimer(m_TimerHandle);
		RemoveFromParent();
		UE_LOG(LogTemp, Log, TEXT("zhx : UTopHintTextUI::OnTimerUpdate Show Time is down"));
	}
}