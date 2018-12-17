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

	UPROPERTY()
		UButton * m_BackButton;
	UPROPERTY()
		UButton * m_SongHuoButton;
	UPROPERTY()
	UButton * m_ZiquButton;

	UPROPERTY()
		UTextBlock * m_Text1;
	UPROPERTY()
		UTextBlock * m_Text2;
	UPROPERTY()
		UCheckBox * m_Box1;
	UPROPERTY()
		UCheckBox * m_Box2;

    
    void OnButtonClick(int _index);
};
