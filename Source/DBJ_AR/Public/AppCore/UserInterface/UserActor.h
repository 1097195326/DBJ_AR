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
	virtual void BeginPlay() override;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UUserComponent * m_Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * m_PlaneRotateComponent;
    
    TArray<UUserComponent *> m_HuaList;
    
	UPROPERTY(VisibleAnywhere)
		int m_SoketIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		 TEnumAsByte<UserActorType> m_Type;

	TArray<GoodsData *> m_GoodsDatas;

	void	RemoveGoodsData(GoodsData * _data);
	void	AddGoodsData(GoodsData * _data);

    void    AddUserComponent(UUserComponent * _userComponent);
    bool    MergeOtherActor(AUserActor * _otherActor);
    
    void    ResetHuaComponent();
	void	ShowPlaneComponent(bool visiable);
};

