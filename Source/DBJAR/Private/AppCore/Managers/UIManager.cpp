#include "UIManager.h"
#include "DataManager.h"
#include "AppInstance.h"
#include "TopHintTextUI.h"

UIManager * UIManager::GetInstance()
{
    static UIManager m;

    return &m;
}
UBaseUI* UIManager::OpenUI(const FString & _uiName, UBaseUI * _ParentUI)
{
    // Í¨¹ýuiNameÕÒ³öUIPath.
	
    UIData uiData = Data_M->GetProtoType<UIPrototype>(ControllerPrototype::ScreenResolutionId)->GetDataByKey(_uiName);
    FString mUIPath = uiData.m_Value;

    if (!mUIPath.IsEmpty())
    {
        UClass* loadClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, *mUIPath);

        if (loadClass == nullptr)
            return nullptr;
		if (UAppInstance::GetInstance() && UAppInstance::GetInstance()->IsValidLowLevel())
		{
			UWorld * mWorld = UAppInstance::GetInstance()->GetWorld();
			UBaseUI* _sceneObj = (UBaseUI*)CreateWidget<UUserWidget>(mWorld, loadClass);
			_sceneObj->SetParentUI(_ParentUI);
			return _sceneObj;
		}
		return nullptr;
    }
    return nullptr;
}
void UIManager::UnRegisterButton(UButton * _btn)
{
	if (m_ButtonMap.Contains(_btn))
	{
		UButtonScript * bs = *(m_ButtonMap.Find(_btn));
		m_ButtonMap.Remove(_btn);
		bs->RemoveFromRoot();
	}
	

}
void UIManager::TopHintText(const FString & hintText, float showSecond)
{
	UTopHintTextUI * baseUI = (UTopHintTextUI*)OpenUI(TEXT("TopHintTextUI"));
	baseUI->AddToViewport(999);
	baseUI->InitText(hintText, showSecond);
}