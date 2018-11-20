#pragma once

#include "BaseUI.h"
#include "MsgCenter.h"
#include "EditerARUI.generated.h"

UCLASS()
class UEditerARUI : public UBaseUI
{
    GENERATED_BODY()
    
public:
    UButton * m_ProductListButton;
	UButton * m_ChangeButton;
	UButton * m_DeleteButton;
	// top button list
	UButton * m_ShowlistButton;
	UCanvasPanel *  m_ShowlistPanel;
	UButton * m_CloseListButton;
	UButton * m_AcountButton;
	UButton * m_AddressButton;
	UButton * m_OrderlistButton;
	UButton * m_ShareButton;

public:
    virtual void On_Init() override;
    virtual void On_Start() override;
    virtual void On_Delete() override;
    
    void On_Button_Click(int _index);
    
	void OnGetCategoryList(msg_ptr _msg);
	void OnSelectActor(msg_ptr _msg);
};
