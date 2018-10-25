#include "UIManager.h"
#include "DataManager.h"
#include "AppInstance.h"

UIManager * UIManager::GetInstance()
{
    static UIManager m;

    return &m;
}
UBaseUI* UIManager::OpenUI(const FString & _uiName)
{
    // ͨ��uiName�ҳ�UIPath.
    UIData uiData = ((UIPrototype*)Data_M->GetProtoType(E_UI_IOS_ID))->GetDataByKey(_uiName);
    FString mUIPath = uiData.m_Value;

    if (!mUIPath.IsEmpty())
    {
        UClass* loadClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, *mUIPath);

        if (loadClass == nullptr)
            return nullptr;

        UWorld * mWorld = UAppInstance::GetInstance()->GetWorld();
        UBaseUI* _sceneObj = (UBaseUI*)CreateWidget<UUserWidget>(mWorld, loadClass);
        return _sceneObj;
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
