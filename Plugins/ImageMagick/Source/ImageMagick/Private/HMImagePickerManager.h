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
#import "HMError.h"

@interface HMImagePickerManager : NSObject

+ (instancetype)defaultManager;

- (void)imagePickerWithController:(id)vc scaledToSizeWithWidth:(CGFloat)width height:(CGFloat)height imagePickerBlock:(void(^)(UIImage *image,UIImage *icon, NSString *imagePath, NSString *iconPath))callBack Error:(void(^)(HMError *error))errorCallBack;

@end
#endif
