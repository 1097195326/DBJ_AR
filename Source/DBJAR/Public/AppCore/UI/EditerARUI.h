#pragma once

#include "BaseUI.h"
#include "MsgCenter.h"
#include "EditerARUI.generated.h"

UCLASS()
class UEditerARUI : public UBaseUI
{
    GENERATED_BODY()
    
public:
	UPROPERTY()
		UButton * m_ProductListButton;
	UPROPERTY()
		UButton * m_ChangeButton;
	UPROPERTY()
	UButton * m_DeleteButton;
	// top button list
	UPROPERTY()
		UButton * m_ShowlistButton;
	UPROPERTY()
		UScrollBox *  m_ShowlistPanel;
	UPROPERTY()
		UButton * m_CloseListButton;
	UPROPERTY()
		UButton * m_AcountButton;
	UPROPERTY()
		UButton * m_AddressButton;
	UPROPERTY()
		UButton * m_OrderlistButton;
	UPROPERTY()
	UButton * m_ShareButton;

public:
    virtual void On_Init() override;
    virtual void On_Start() override;
    virtual void On_Delete() override;

    void On_Button_Click(int _index);
	void DeleteAllUserActor();

	void OnGetCategoryList(msg_ptr _msg);
	void OnSelectActor(msg_ptr _msg);
};
