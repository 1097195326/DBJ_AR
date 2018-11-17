#pragma once


#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GoodsData.h"
#include "UserComponent.generated.h"


UCLASS()
class UUserComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	GoodsData *		m_Data;
    FString         m_SocketName;
    
	void SetGoodsData(GoodsData * _data,FString  _socketName = TEXT(""));
	int	GetProductId();
};
