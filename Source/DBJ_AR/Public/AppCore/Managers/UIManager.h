#pragma once

#include "GObject.h"
#include "ButtonScript.h"
#include "CoreMinimal.h"
#include "BaseUI.h"
#include <list>

class DBJ_AR_API UIManager : public GObject
{
private:
    // single instance
    std::list<UButtonScript*>        m_ButtonList;

public:
    static UIManager * GetInstance();

    UBaseUI* OpenUI(const FString & _uiName);

    template<typename T>
    void RegisterButton(int _bid, UButton * _btn, T * _obj, void(T::*_func)(int))
    {
        UButtonScript * bs = UButtonScript::Create();
        bs->BindFunctionCall(_bid, _btn, _obj, _func);
        m_ButtonList.push_back(bs);
    }
    void UnRegisterButton(UButtonScript * _btn);
};
