#pragma once



#include "CoreMinimal.h"
#include "UserComponent.h"
#include "GoodsData.h"
#include "UserActor.generated.h"

UENUM()
enum UserActorType
{
	User_None,
	User_Hua,
	User_Pen,
};

UCLASS()
class AUserActor : public AActor
{
    GENERATED_BODY()
    
public:
    AUserActor();
	~AUserActor();
	virtual void BeginDestroy() override;
    
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UUserComponent * m_Mesh;
	UPROPERTY(VisibleAnywhere)
		int m_SoketIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		 TEnumAsByte<UserActorType> m_Type;

	TArray<GoodsData *> m_GoodsDatas;

	void	RemoveGoodsData(GoodsData * _data);
	void	AddGoodsData(GoodsData * _data);

};

