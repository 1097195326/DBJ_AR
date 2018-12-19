#include "GCore.h"
#include "ButtonScript.h"


UButtonScript * UButtonScript::Create()
{
	UButtonScript * bs = NewObject<UButtonScript>();
	bs->AddToRoot();
	return bs;
}
void UButtonScript::OnButtonClick()
{
	if (m_IsWithAction)
	{
		m_CallWithAction(m_Index,b_Click);
	}
	else
	{
		m_Call(m_Index);
	}
	
	
}
void UButtonScript::OnButtonPressed()
{
	m_CallWithAction(m_Index, b_Pressed);
}
void UButtonScript::OnButtonReleased()
{
	m_CallWithAction(m_Index, b_Released);
}
void UButtonScript::On_Delete()
{
	
}