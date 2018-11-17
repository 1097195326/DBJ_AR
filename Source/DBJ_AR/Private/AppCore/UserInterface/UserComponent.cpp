#include "UserComponent.h"

void UUserComponent::SetGoodsData(GoodsData * _data,FString  _socketName)
{
	m_Data = _data;
    m_SocketName = _socketName;
}
int UUserComponent::GetProductId()
{
	return m_Data->id;
}
