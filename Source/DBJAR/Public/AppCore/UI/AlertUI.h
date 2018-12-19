#pragma once

#include "BaseUI.h"
#include <functional>
#include "AlertUI.generated.h"


UCLASS()
class DBJAR_API  UAlertUI : public UBaseUI
{
    GENERATED_BODY()

public:
	typedef std::function<void()>  AlertFunctionDelegate;

    virtual void On_Init() override;
	virtual void On_Delete() override;

	UPROPERTY()
	UTextBlock * m_ContentText;

	UPROPERTY()
		UButton * m_SureButton;
	UPROPERTY()
		UButton * m_CancelButton;
	UPROPERTY()
	UButton * m_OnlySureButton;

	UPROPERTY()
		UCanvasPanel * m_ShowPanel;
	UPROPERTY()
	UCanvasPanel * m_OnlyPanel;

	void	OnlyButtonShow(bool _show);
	void	SetContentText(const FString & _content);
	template<typename T>
	void BindCancelFunctionCall(T* _obj, void(T::*_func)())
	{
		CancelFunctionDelegate = AlertFunctionDelegate(std::bind(_func, _obj));
	}
	template<typename T>
	void BindSureFunctionCall(T* _obj, void(T::*_func)())
	{
		SureFunctionDelegate = AlertFunctionDelegate(std::bind(_func, _obj));
	}
	template<typename T>
	void BindOnlySureFunctionCall(T* _obj, void(T::*_func)())
	{
		OnlySureFunctionDelegate = AlertFunctionDelegate(std::bind(_func, _obj));
	}
private:
	AlertFunctionDelegate CancelFunctionDelegate;
	AlertFunctionDelegate SureFunctionDelegate;
	AlertFunctionDelegate OnlySureFunctionDelegate;


    void OnButtonClick(int _index);
};
