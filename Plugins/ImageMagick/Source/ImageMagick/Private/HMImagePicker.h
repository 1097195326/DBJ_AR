//
//  HMImagePicker.h
//  HMImagePicker
//
//  Created by 门皓 on 2017/11/28.
//  Copyright © 2017年 门皓. All rights reserved.
//
#pragma once
#if PLATFORM_IOS

#import <Foundation/Foundation.h>
#import <UIkit/UIKit.h>

typedef void(^ImageCallBack)(UIImage *image);

typedef void(^ImageCancelCallBack)();

@interface HMImagePicker : NSObject

@property (copy, nonatomic) ImageCallBack callback;

@property (copy, nonatomic) ImageCancelCallBack errorCallback;

- (void)imagepickerWithController:(UIViewController *)vc;

@end

#endif
