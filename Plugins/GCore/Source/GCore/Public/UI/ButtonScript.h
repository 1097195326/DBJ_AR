#pragma once

#include "GObject.h"
#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"  
#include <functional>
#include "ButtonScript.generated.h"

enum ButtonAction
{
	b_Click,
	b_Pressed,
	b_Released,
	b_PressAndRelease,
};

UCLASS()
class GCORE_API UButtonScript : public UObject, public GObject
{
	GENERATED_BODY()
	
private:
	typedef std::function<void(int)> BUTTON_CLICK_CALL;
	typedef std::function<void(int, ButtonAction)> BUTTON_CALL_WITH_ACTION;

	UButton * m_Button;
	int		m_Index;
	bool	m_IsWithAction;
	BUTTON_CLICK_CALL	m_Call;
	BUTTON_CALL_WITH_ACTION m_CallWithAction;


public:
	static UButtonScript * Create();
	
	UFUNCTION()
		void OnButtonClick();
	UFUNCTION()
		void OnButtonPressed();
	UFUNCTION()
		void OnButtonReleased();
	virtual void On_Delete() override;

	template<typename T>
	void BindFunctionCall(int _index,UButton * _btn, T* _obj, void(T::*_func)(int))
	{
		m_Index = _index;
		m_Button = _btn;
		m_Button->OnClicked.AddDynamic(this, &UButtonScript::OnButtonClick);
		m_Call = BUTTON_CLICK_CALL(std::bind(_func,_obj,std::placeholders::_1));
	}
	template<typename T>
	void BindFunctionCall(int _index, UButton * _btn, T* _obj, void(T::*_func)(int, ButtonAction _action), ButtonAction _action)
	{
		m_Index = _index;
		m_Button = _btn;
		m_IsWithAction = true;
		switch (_action)
		{
		case b_Click:
		{
			m_Button->OnClicked.AddDynamic(this, &UButtonScript::OnButtonClick);
		}break;
		case b_Pressed:
		{
			m_Button->OnPressed.AddDynamic(this, &UButtonScript::OnButtonPressed);
		}break;
		case b_Released:
		{
			m_Button->OnReleased.AddDynamic(this, &UButtonScript::OnButtonReleased);
		}break;
		case b_PressAndRelease:
		{
			m_Button->OnPressed.AddDynamic(this, &UButtonScript::OnButtonPressed);
			m_Button->OnReleased.AddDynamic(this, &UButtonScript::OnButtonReleased);
		}break;
		default:
			break;
		}
		m_CallWithAction = BUTTON_CALL_WITH_ACTION(std::bind(_func, _obj, std::placeholders::_1,std::placeholders::_2));
	}
};
