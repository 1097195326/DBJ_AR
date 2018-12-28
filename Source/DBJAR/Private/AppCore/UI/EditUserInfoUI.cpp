#include "EditUserInfoUI.h"
#include "UIManager.h"
#include "UserInfo.h"
#include "EditerARGameModule.h"
#include "PlatformFilemanager.h"
#include "Engine/Texture2D.h"
#include "Misc/PackageName.h"
#include "AppInstance.h"
#include "ImageMagick.h"
#include "FileDownloadManager.h"

void UEditUserInfoUI::On_Init()
{
    if (UButton * widget = (UButton*)GetWidgetFromName("BackButton"))
    {
		m_BackButton = widget;
    }
	if (UButton * widget = (UButton*)GetWidgetFromName("ChangeUserImage"))
	{
		m_ChangeUserImage = widget;
	}
	if (UButton * widget = (UButton*)GetWidgetFromName("EditUserNameButton"))
	{
		m_EditUerNameButton = widget;
	}
	if (UImage * widget = (UImage*)GetWidgetFromName("UserImage"))
	{
		m_UserImage = widget;
	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("UserName"))
	{
		m_UserName = widget;

	}
	if (UTextBlock * widget = (UTextBlock*)GetWidgetFromName("UserPhone"))
	{
		m_UserPhone = widget;
	}

}
void UEditUserInfoUI::On_Start()
{
	UIManager::GetInstance()->RegisterButton(1, m_BackButton, this, &UEditUserInfoUI::OnButtonClick);
	UIManager::GetInstance()->RegisterButton(2, m_ChangeUserImage, this, &UEditUserInfoUI::OnButtonClick);
	UIManager::GetInstance()->RegisterButton(3, m_EditUerNameButton, this, &UEditUserInfoUI::OnButtonClick);

	MsgCenter::GetInstance()->RegisterMsgHeader(Msg_Local, 2015, this, &UEditUserInfoUI::OnEditString);

	m_UserName->SetText(FText::FromString(UserInfo::Get()->GetLocalData().name));
	m_UserPhone->SetText(FText::FromString(UserInfo::Get()->GetLocalData().phone));

	UTexture2D * texture = UAppInstance::GetInstance()->LoadImageFromDisk(this, UserInfo::Get()->GetLocalData().IconPath);
	if (texture && texture->IsValidLowLevel())
	{
//        m_UserImage->SetBrushFromTexture(texture);
        m_UserImage->GetDynamicMaterial()->SetTextureParameterValue("headTexture", texture);
	}
}
void UEditUserInfoUI::On_Delete()
{
	MsgCenter::GetInstance()->RemoveMsgHeader(Msg_Local, 2015, this);

	UIManager::GetInstance()->UnRegisterButton(m_BackButton);
	UIManager::GetInstance()->UnRegisterButton(m_ChangeUserImage);
	UIManager::GetInstance()->UnRegisterButton(m_EditUerNameButton);

}
void UEditUserInfoUI::OnButtonClick(int _index)
{
    UE_LOG(LogTemp, Log, TEXT("zhx : UEditUserInfoUI::OnButtonClick : "));
	switch (_index)
	{
	case 1:
	{
		UBaseUI * baseUI = UIManager::GetInstance()->OpenUI(TEXT("UserAccountUI"));
		baseUI->AddToViewport();
		RemoveFromParent();
	}break;
	case 2:
	{
        IImageMagickModule::Get().OpenSelectPicture(FOnOpenReresult::CreateUObject(this, &UEditUserInfoUI::OnSelectPicture));
	}break;
	case 3:
	{
		UEditStringUI * baseUI = (UEditStringUI*)UIManager::GetInstance()->OpenUI(TEXT("EditStringUI"));
		baseUI->SetDelegate(this,TEXT("用户名"), UserInfo::Get()->GetLocalData().name);
		baseUI->AddToViewport();
	}break;
	}

}
void UEditUserInfoUI::OnEditString(msg_ptr _msg)
{
	UE_LOG(LogTemp, Log, TEXT("zhx : edit user info text changed"));
	UserInfo::Get()->SetUserName(m_Wto_UserName);
	m_UserName->SetText(FText::FromString(m_Wto_UserName));
}
void UEditUserInfoUI::EditString(const FString & text)
{
	m_Wto_UserName = text;

	EditerARGameModule::GetInstance()->UpdateUserName(text);

}
void UEditUserInfoUI::OnSelectPicture(bool isSuccess, FString inIconFilePath, FString inFilePath, FVector2D inDPI, FVector2D inRes)
{
    UE_LOG(LogTemp,Log,TEXT("zhx : UEditUserInfoUI::OnSelectPicture"));
    FString ueIconPath;
    FString ueImagePath;
#if PLATFORM_ANDROID
    
#elif PLATFORM_IOS
    ueIconPath = UFileDownloadManager::Get()->ExtractIOSDir(*inIconFilePath);
    ueImagePath = UFileDownloadManager::Get()->ExtractIOSDir(*inFilePath);
#endif
    IPlatformFile &  pf = FPlatformFileManager::Get().GetPlatformFile();
    
    if (pf.FileExists(*ueImagePath))
    {
        pf.DeleteFile(*ueImagePath);
        UE_LOG(LogTemp,Log,TEXT("zhx : delete image : %s"),*ueImagePath);
    }
    if (pf.FileExists(*ueIconPath))
    {
        UE_LOG(LogTemp, Log, TEXT("zhx : icon find : %s"),*ueIconPath);
//        UserInfo::Get()->SaveUserData(TEXT("IconPath"), ueIconPath);
//        UTexture2D * texture = UAppInstance::GetInstance()->LoadImageFromDisk(this,UserInfo::Get()->GetLocalData().IconPath);
//        if (texture && texture->IsValidLowLevel())
//        {
//            UE_LOG(LogTemp,Log,TEXT("zhx : get valid texture"));
//            m_UserImage->SetBrushFromTexture(texture);
//        }
        FString iconName = FPackageName::GetShortName(ueIconPath);
        FString iconSavePath = UFileDownloadManager::Get()->GetAppPath(TEXT("Saved/HeadIconImage"));
        if(!pf.DirectoryExists(*iconSavePath))
        {
            pf.CreateDirectoryTree(*iconSavePath);
        }
        FString iconSPath = FPaths::Combine(iconSavePath, iconName);
        UE_LOG(LogTemp,Log,TEXT("zhx :  iconSPath : %s"),*iconSPath);
        if (pf.FileExists(*iconSPath))
        {
            UE_LOG(LogTemp,Log,TEXT("zhx : delete ICON : %s"),*iconSPath);
            pf.DeleteFile(*iconSPath);
        }
        if (pf.MoveFile(*iconSPath, *ueIconPath))
        {
            UE_LOG(LogTemp,Log,TEXT("zhx : MoveFile"));
            UserInfo::Get()->SaveUserData(TEXT("IconPath"), iconSPath);
            UTexture2D * texture = UAppInstance::GetInstance()->LoadImageFromDisk(this,UserInfo::Get()->GetLocalData().IconPath);
            if (texture && texture->IsValidLowLevel())
            {
                UE_LOG(LogTemp,Log,TEXT("zhx : get valid texture"));
//                m_UserImage->SetBrushFromTexture(texture);
                m_UserImage->GetDynamicMaterial()->SetTextureParameterValue("headTexture", texture);
            }
        }
    }
    
}
