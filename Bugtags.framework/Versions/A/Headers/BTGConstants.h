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

#endif