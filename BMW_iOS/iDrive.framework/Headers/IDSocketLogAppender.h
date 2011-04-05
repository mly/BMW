/*
 *  IDSocketLogAppender.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 26.03.10.
 *  Copyright 2010 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDSocketLogAppender.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>

#import "IDLogger.h"

extern NSString* SocketLogAppenderErrorNotification;

@interface IDSocketLogAppender : IDLogAppender
{
    int              _socket;
    NSDateFormatter* _logDateFormatter;
}

- (BOOL)connectWithHostname:(NSString*)hostname;
- (void)disconnect;

@end
