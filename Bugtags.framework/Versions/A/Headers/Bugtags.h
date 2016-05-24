/*
 File:       Bugtags/Bugtags.h
 
 Contains:   API for using Bugtags's SDK.
 
 Copyright:  (c) 2016 by Bugtags, Ltd., all rights reserved.
 
 Version:    1.2.6
 */

#import "BTGConstants.h"
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface BugtagsOptions : NSObject <NSCopying>

/**
 *  是否跟踪闪退，联机 Debug 状态下默认 NO，其它情况默认 YES
 */
@property(nonatomic, assign) BOOL trackingCrashes;

/**
 *  是否跟踪用户操作步骤，默认 YES
 */
@property(nonatomic, assign) BOOL trackingUserSteps;

/**
 *  是否收集控制台日志，默认 YES
 */
@property(nonatomic, assign) BOOL trackingConsoleLog;

/**
 *  是否收集用户位置信息，默认 YES
 */
@property(nonatomic, assign) BOOL trackingUserLocation;

/**
 *  是否跟踪网络请求，只跟踪 HTTP / HTTPS 请求，默认 NO
 *  强烈建议同时设置 trackingNetworkURLFilter 对需要跟踪的网络请求进行过滤
 */
@property(nonatomic, assign) BOOL trackingNetwork;

/**
 *  设置需要跟踪的网络请求 URL，多个地址用 | 隔开，支持正则表达式，不设置则跟踪所有请求
 *  强烈建议设置为应用服务器接口的域名，如果接口是通过 IP 地址访问，则设置为 IP 地址
 *  如：设置为 bugtags.com，则网络请求跟踪只对 URL 中包含 bugtags.com 的请求有效
 */
@property(nonatomic, copy) NSString *trackingNetworkURLFilter;

/**
 * 网络请求跟踪遇到 HTTPS 请求证书无效的时候，是否允许继续访问，默认 NO
 */
@property(nonatomic, assign) BOOL trackingNetworkContinueWithInvalidCertificate;

/**
 *  是否收集闪退时的界面截图，默认 YES
 */
@property(nonatomic, assign) BOOL crashWithScreenshot;

/**
 *  是否忽略 PIPE Signal (SIGPIPE) 闪退，默认 NO
 */
@property(nonatomic, assign) BOOL ignorePIPESignalCrash;

/**
 * 支持的屏幕方向，默认 UIInterfaceOrientationMaskAllButUpsideDown，请根据您的 App 支持的屏幕方向来设置
 * 1.1.2+ 不需要手动设置，SDK 会自动设置
 */
@property(nonatomic, assign) UIInterfaceOrientationMask supportedInterfaceOrientations __attribute__((deprecated));

/**
 *  设置应用版本号，默认自动获取应用的版本号
 */
@property(nonatomic, copy) NSString *version;

/**
 *  设置应用 build，默认自动获取应用的 build
 */
@property(nonatomic, copy) NSString *build;

@end

@interface Bugtags : NSObject

/**
 * 初始化 Bugtags
 * @param appKey - 通过 bugtags.com 申请的应用appKey
 * @param invocationEvent - 呼出方式
 * @return none
 */
+ (void)startWithAppKey:(NSString *)appKey invocationEvent:(BTGInvocationEvent)invocationEvent;

/**
 * 初始化 Bugtags
 * @param appKey - 通过 bugtags.com 申请的应用appKey
 * @param invocationEvent - 呼出方式
 * @param options - 启动选项
 * @return none
 */
+ (void)startWithAppKey:(NSString *)appKey invocationEvent:(BTGInvocationEvent)invocationEvent options:(BugtagsOptions *)options;

/**
 * 设置 Bugtags 呼出方式
 * @param invocationEvent - 呼出方式
 * @return none
 */
+ (void)setInvocationEvent:(BTGInvocationEvent)invocationEvent;

/**
 * 获取 Bugtags 当前的呼出方式
 *
 * @return 呼出方式
 */
+ (BTGInvocationEvent)currentInvocationEvent;

/**
 * Bugtags 日志工具，添加自定义日志，不会在控制台输出
 * @param format
 * @param ...
 * @return none
 */
void BTGLog(NSString *format, ...);

/**
 * Bugtags 日志工具，添加自定义日志，不会在控制台输出，功能等同于 BTGLog
 * 在 Swift 中请调用此方法添加自定义日志
 * @param content - 日志内容
 * @return none
 */
+ (void)log:(NSString *)content;

/**
 * 设置是否收集 Crash 信息
 * @param trackingCrashes - 默认 YES
 * @return none
 */
+ (void)setTrackingCrashes:(BOOL)trackingCrashes;

/**
 * 设置是否跟踪用户操作步骤
 * @param trackingUserSteps - 默认 YES
 * @return none
 */
+ (void)setTrackingUserSteps:(BOOL)trackingUserSteps;

/**
 * 设置是否收集控制台日志
 * @param trackingConsoleLog - 默认 YES
 * @return none
 */
+ (void)setTrackingConsoleLog:(BOOL)trackingConsoleLog;

/**
* 设置是否收集用户位置信息
* @param trackingUserLocation
* @return none
*/
+ (void)setTrackingUserLocation:(BOOL)trackingUserLocation;

/**
 *  设置是否跟踪网络请求，只跟踪 HTTP / HTTPS 请求
 *  强烈建议同时设置 trackingNetworkURLFilter 对需要跟踪的网络请求进行过滤
 *  @param trackingNetwork - 默认 NO
 *  @return none
 */
+ (void)setTrackingNetwork:(BOOL)trackingNetwork;

/**
 * 设置自定义数据，会与问题一起提交
 * @param data
 * @param key
 * @return none
 */
+ (void)setUserData:(NSString *)data forKey:(NSString *)key;

/**
 * 移除指定 key 的自定义数据
 * @param key
 * @return none
 */
+ (void)removeUserDataForKey:(NSString *)key;

/**
 * 移除所有自定义数据
 * @return none
 */
+ (void)removeAllUserData;

/**
 * 手动发送Exception
 * @param exception
 * @return none
 */
+ (void)sendException:(NSException *)exception;

/**
 * 发送用户反馈
 * @param content - 反馈内容
 * @return none
 */
+ (void)sendFeedback:(NSString *)content;

/**
 * 设置问题提交之前的回调
 * @param callback - 回调的 block
 * @return none
 */
+ (void)setBeforeSendingCallback:(void (^)(void))callback;

/**
 * 设置问题提交成功后的回调
 * @param callback - 回调的 block
 * @return none
 */
+ (void)setAfterSendingCallback:(void (^)(void))callback;

/**
 * 设置是否仅在 WiFi 模式下才上传数据
 *
 * @param onlyViaWiFi - 默认 NO
 */
+ (void)setUploadDataOnlyViaWiFi:(BOOL)onlyViaWiFi;

/**
 * 手动调用截屏界面
 * @return none
 */
+ (void)invoke;

@end