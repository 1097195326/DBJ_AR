//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "SharingComponent.h"
//��¼
void USharingComponent::OnRegister()
{
	Super::OnRegister();
	
	USharingComponent::SharingFinishedDelegate.AddUObject(this, &USharingComponent::SharingFinished_Handler);
}
//ע��
void USharingComponent::OnUnregister()
{
	Super::OnUnregister();
	
	USharingComponent::SharingFinishedDelegate.RemoveAll(this);
}
//����SharingFinishedDelegateί��
USharingComponent::FSharingFinishedDelegate USharingComponent::SharingFinishedDelegate;
