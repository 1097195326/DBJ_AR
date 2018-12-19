#include "ToolScrollButton.h"


void UToolScrollButton::SetData(const IdData & _data, SelectButtonDelegate * _delegate)
{
	m_Data = _data;
	m_Delegate = _delegate;

	FString Content = m_Data.Name;
	int index = Content.Len() / 5;
	for (int i = index; i > 0; i--)
	{
		Content.InsertAt(5 * i, TEXT("\n"));
	}
	m_ButtonText->SetText(FText::FromString(Content));
}