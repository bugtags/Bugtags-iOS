//
//  BTGConstants.h
//  Bugtags
//
//  Created by Stephen Zhang on 15/6/4.
//  Copyright (c) 2016 bugtags.com. All rights reserved.
//

#ifndef Bugtags_BTGConstants_h
#define Bugtags_BTGConstants_h

/**
 *  Bugtags 呼出方式
 *  所有方式都会自动收集 Crash 信息（如果允许）
 */
typedef enum BTGInvocationEvent {
    
    // 静默模式，只收集 Crash 信息（如果允许）
    BTGInvocationEventNone,
    
    // 通过摇一摇呼出 Bugtags
    BTGInvocationEventShake,
    
    // 通过悬浮小球呼出 Bugtags
    BTGInvocationEventBubble
    
} BTGInvocationEvent;

/**
 *  Bugtags 数据获取模式，目前只对远程配置及在线修复有效
 */
typedef enum BTGDataMode {
    
    // 获取生产环境的数据
    BTGDataModeProduction,

    // 获取测试环境的数据
    BTGDataModeTesting,
    
    // 获取本地的数据文件
    // 远程配置，自动读取本地 mainBundle 的 main.local.plist 文件
    // 在线修复，自动读取本地 mainBundle 的 main.local.js 文件
    BTGDataModeLocal
    
} BTGDataMode;

#endif
