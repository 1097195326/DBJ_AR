#pragma once
#include "BaseUI.h"
#include "GetStyleUI.generated.h"


UCLASS()
class DBJ_AR_API  UGetStyleUI : public UBaseUI
{
    GENERATED_BODY()

public:
    virtual void On_Init() override;
	virtual void On_Start() override;
	FString m_String;

    UButton * m_BackButton;
	UButton * m_SongHuoButton;
	UButton * m_ZiquButton;

	UTextBlock * m_Text1;
	UTextBlock * m_Text2;
	UCheckBox * m_Box1;
	UCheckBox * m_Box2;

    
    void OnButtonClick(int _index);
};
