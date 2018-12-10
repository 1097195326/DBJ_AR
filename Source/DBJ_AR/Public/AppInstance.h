#pragma once

#include "GAppInstance.h"
#include "AppCore/Managers/DataManager.h"

#include "MsgCenter.h"
#include "AppInstance.generated.h"

UCLASS()
class DBJ_AR_API UAppInstance : public UGAppInstance
{
	GENERATED_BODY()
	
public:
	UAppInstance();

    
	virtual void On_Init() override;
	virtual void On_Delete() override;

	virtual void OpenLevel(const FString & _levelName) override;

    virtual    void ApplicationWillEnterBackground() override;
    virtual    void ApplicationHasEnteredForeground() override;

	void OnGloablMsg(msg_ptr _msg);
	void GloablMsgSure();
	void GloablMsgCancel();


	UFUNCTION(Exec)
		void PakMount();
};
