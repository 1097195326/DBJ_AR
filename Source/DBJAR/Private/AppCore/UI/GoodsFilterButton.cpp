#include "GoodsFilterButton.h"


void UGoodsFilterButton::SelectButton(bool _isSelect)
{
	if (_isSelect)
	{
		m_ButtonText->SetColorAndOpacity(FLinearColor(FColor::FromHex(TEXT("29CF81"))));
		m_SelectBorder->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_ButtonText->SetColorAndOpacity(FLinearColor(FColor::FromHex(TEXT("666666"))));
		m_SelectBorder->SetVisibility(ESlateVisibility::Hidden);
	}
}