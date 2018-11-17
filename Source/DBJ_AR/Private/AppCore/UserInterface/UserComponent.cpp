#include "UserComponent.h"

void UUserComponent::SetGoodsData(GoodsData * _data)
{
	m_Data = _data;
}
int UUserComponent::GetProductId()
{
	return m_Data->id;
}