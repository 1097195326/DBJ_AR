#pragma once

#include "GAppInstance.h"
#include "AppCore/Managers/DataManager.h"
#include "Misc/CoreDelegates.h"
#include "MsgCenter.h"
#include "AppInstance.generated.h"

UCLASS()
class DBJ_AR_API UAppInstance : public UGAppInstance
{
	GENERATED_BODY()
	
public:
	UAppInstance();

    virtual void PostInitProperties() override;
    virtual void BeginDestroy() override;
    
    
    //    UFUNCTION()
    virtual    void ApplicationWillEnterBackground();
    //    UFUNCTION()
    virtual    void ApplicationHasEnteredForeground();
    
	virtual void On_Init() override;
	virtual void On_Delete() override;

	virtual void OpenLevel(const FString & _levelName) override;

    

	void OnGloablMsg(msg_ptr _msg);

	UFUNCTION(Exec)
		void PakMount();
};
