//
//  HMImagePicker.m
//  HMImagePicker
//
//  Created by 门皓 on 2017/11/28.
//  Copyright © 2017年 门皓. All rights reserved.
//

#include "HMImagePicker.h"
#if PLATFORM_IOS

@interface HMImagePicker()<UINavigationControllerDelegate,UIImagePickerControllerDelegate>

@property (strong, nonatomic) id vc;

@end

@implementation HMImagePicker

- (void)imagepickerWithController:(UIViewController *)vc
{
    self.vc = vc;
    
    // 创建UIImagePickerController实例
    UIImagePickerController *imagePickerController = [[UIImagePickerController alloc] init];
    // 设置代理
    imagePickerController.delegate = self;
    // 是否允许编辑（默认为NO）
    //    imagePickerController.allowsEditing = YES;
    
    
    // 创建一个警告控制器
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"选取图片" message:nil preferredStyle:UIAlertControllerStyleActionSheet];
    
    UIPopoverPresentationController *popover = alert.popoverPresentationController;

    if (popover)
    {
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
        {
            popover.sourceView = vc.view;
            popover.sourceRect = CGRectMake(0, ([UIScreen mainScreen].bounds.size.height - 5), [UIScreen mainScreen].bounds.size.width, 5);
            popover.permittedArrowDirections = UIPopoverArrowDirectionAny;
        }else
        {
            popover.sourceView = vc.view;
            popover.sourceRect = CGRectMake(([UIScreen mainScreen].bounds.size.width / 4) * 3 / 4, ([UIScreen mainScreen].bounds.size.height * 3 / 4) +([UIScreen mainScreen].bounds.size.height / 16), [UIScreen mainScreen].bounds.size.width / 8, 5);
            popover.permittedArrowDirections = UIPopoverArrowDirectionAny;
        }
    }
    // 设置警告响应事件
    UIAlertAction *cameraAction = [UIAlertAction actionWithTitle:@"拍照" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        // 设置照片来源为相机
        imagePickerController.sourceType = UIImagePickerControllerSourceTypeCamera;
        
        // 设置进入相机时使用前置或后置摄像头
        imagePickerController.cameraDevice = UIImagePickerControllerCameraDeviceRear;
        
        // 展示选取照片控制器
        [vc presentViewController:imagePickerController animated:YES completion:^{}];
    }];
    
    UIAlertAction *photosAction = [UIAlertAction actionWithTitle:@"从相册选择" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        imagePickerController.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
        [vc presentViewController:imagePickerController animated:YES completion:^{}];
    }];
    
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
        if (self.errorCallback)
        {
            self.errorCallback();
        }
    }];
    
    // 判断是否支持相机
    if([UIImagePickerController isCameraDeviceAvailable:UIImagePickerControllerCameraDeviceRear])
    {
        // 添加警告按钮
//        [alert addAction:cameraAction];
    }
    [alert addAction:photosAction];
    [alert addAction:cancelAction];
    // 展示警告控制器
    [vc presentViewController:alert animated:YES completion:nil];
    
    // Do any additional setup after loading the view, typically from a nib.
}


#pragma mark - UIImagePickerControllerDelegate
// 完成图片的选取后调用的方法
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    
    // 选取完图片后跳转回原控制器
    [picker dismissViewControllerAnimated:YES completion:nil];
    
    /* 此处参数 info 是一个字典，下面是字典中的键值 （从相机获取的图片和相册获取的图片时，两者的info值不尽相同）
     * UIImagePickerControllerMediaType; // 媒体类型
     * UIImagePickerControllerOriginalImage;  // 原始图片
     * UIImagePickerControllerEditedImage;    // 裁剪后图片
     * UIImagePickerControllerCropRect;       // 图片裁剪区域（CGRect）
     * UIImagePickerControllerMediaURL;       // 媒体的URL
     * UIImagePickerControllerReferenceURL    // 原件的URL
     * UIImagePickerControllerMediaMetadata    // 当数据来源是相机时，此值才有效
     */
    
    // 从info中将图片取出，并加载到imageView当中
    UIImage *image = [info objectForKey:UIImagePickerControllerOriginalImage];
    
    
    
    //    // 创建保存图像时需要传入的选择器对象（回调方法格式固定）
    //    SEL selectorToCall = @selector(image:didFinishSavingWithError:contextInfo:);
    //    // 将图像保存到相册（第三个参数需要传入上面格式的选择器对象）
    //    UIImageWriteToSavedPhotosAlbum(image, self, selectorToCall, NULL);
    
    if (self.callback)
    {
        self.callback(image);
    }
    
}
// 取消选取调用的方法
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    if (self.errorCallback)
    {
        self.errorCallback();
    }
    
    [self.vc dismissViewControllerAnimated:YES completion:nil];
}

// 保存图片后到相册后，回调的相关方法，查看是否保存成功
- (void)image:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo {
    if (error == nil){
        NSLog(@"Image was saved successfully.");
    } else {
        NSLog(@"An error happened while saving the image.");
        NSLog(@"Error = %@", error);
    }
}

@end
#endif
