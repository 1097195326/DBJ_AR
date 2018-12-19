// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUI.h"
#include "PhotoPage.generated.h"

/**
 * 
 */
UCLASS()
class DBJAR_API UPhotoPage : public UBaseUI
{
	GENERATED_BODY()
public:
	//	复写BaseUI.
	virtual void On_Start() override;
	virtual void On_Init() override;
	virtual void On_Delete() override;


	void PhotoPicture(int32 _pid);

	//打开系统相册.
	void GetUploadPattern();

	//选择图片后的回调.
	void CBOnOpenPattern(bool isSuccess, FString inIconFilePath, FString inFilePath, FVector2D inDPI, FVector2D inRes);

	//打开系统相册.
	void GetUploadPicture();

	//选择图片后的回调.
	void CBOnOpenPicture(bool isSuccess, FString inIconFilePath, FString inFilePath, FVector2D inDPI, FVector2D inRes);

protected:
	UButton* m_BtnPhoto;	//	拍照按钮.
	UButton* m_BtnPicture;	//	从相册中选择按钮.
	UButton* m_BtnCancel;	//	取消按钮.

	UTextBlock* m_TextPhoto;	//	拍照字段.
	UTextBlock* m_TextPicture;	//	从相册中选择字段.
	UTextBlock* m_TextCancel;	//	取消字段.

};
