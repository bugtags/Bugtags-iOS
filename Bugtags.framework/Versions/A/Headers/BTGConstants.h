//
//  BTGConstants.h
//  Bugtags
//
//  Created by Stephen Zhang on 15/6/4.
//  Copyright (c) 2016 年 bugtags.com. All rights reserved.
//

#ifndef Bugtags_BTGConstants_h
#define Bugtags_BTGConstants_h

/**
 *  Bugtags呼出方式
 */
typedef enum BTGInvocationEvent {
    
    // 静默模式，收集Crash信息（如果允许）
    BTGInvocationEventNone,
    
    // 通过摇一摇呼出Bugtags
    BTGInvocationEventShake,
    
    // 通过悬浮小球呼出Bugtags
    BTGInvocationEventBubble,
    
} BTGInvocationEvent;

#endif