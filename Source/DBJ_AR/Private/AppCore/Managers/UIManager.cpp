#include "UIManager.h"
#include "ManagerHeader.h"
#include "GAppInstance.h"

UIManager * UIManager::GetInstance()
{
    static UIManager m;

    return &m;
}
UBaseUI* UIManager::OpenUI(const FString & _uiName)
{
    // Í¨¹ýuiNameÕÒ³öUIPath.
    UIData uiData = ((UIPrototype*)Data_M->GetProtoType(E_UI_IOS_ID))->GetDataByKey(_uiName);
    FString mUIPath = uiData.m_Value;

    if (!mUIPath.IsEmpty())
    {
        UClass* loadClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, *mUIPath);

        if (loadClass == nullptr)
            return nullptr;

        UWorld * mWorld = UGAppInstance::GetInstance()->GetWorld();
        UBaseUI* _sceneObj = (UBaseUI*)CreateWidget<UUserWidget>(mWorld, loadClass);
        return _sceneObj;
    }
    return nullptr;
}
void UIManager::UnRegisterButton(UButtonScript * _btn)
{
    m_ButtonList.remove(_btn);
    _btn->On_Delete();

}
