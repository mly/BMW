/*
 *  IDApplicationWatchdog.h
 *  iDrive
 *
 *  Created by Brian Jensen on 04.10.2010.
 *  Copyright 2010 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDApplicationWatchdog.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>


@interface IDApplicationWatchdog : NSThread
{	
}

- (NSTimer*) startTimerWithTimeout:(NSTimeInterval)timeout withInfo:(NSDictionary*) infoDict;
- (void)invalidate:(NSTimer*)timer;

@end

