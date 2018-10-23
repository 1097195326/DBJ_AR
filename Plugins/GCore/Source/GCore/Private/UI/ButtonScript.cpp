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

	m_Call(m_Index);
}
void UButtonScript::On_Delete()
{
	RemoveFromRoot();
}