#pragma once

#include "GObject.h"
#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"  
#include <functional>
#include "ButtonScript.generated.h"

typedef std::function<void(int)> BUTTON_CLICK_CALL;

UCLASS()
class UButtonScript : public UObject, public GObject
{
	GENERATED_BODY()
private:
	UButton * m_Button;
	int		m_Index;
	BUTTON_CLICK_CALL	m_Call;

	UFUNCTION()
		void OnButtonClick();
public:
	static UButtonScript * Create();

	virtual void On_Delete() override;

	template<typename T>
	void BindFunctionCall(int _index,UButton * _btn, T* _obj, void(T::*_func)(int))
	{
		m_Index = _index;
		m_Button = _btn;
		m_Button->OnClicked.AddDynamic(this, &UButtonScript::OnButtonClick);
		m_Call = BUTTON_CLICK_CALL(std::bind(_func,_obj,std::placeholders::_1));
	}

};