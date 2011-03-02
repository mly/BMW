//
//  IDFlushProtocol.h
//  iDrive
//
//  Created by patyo-mbp-7 on 11/18/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>



/**
 *
 */
typedef enum IDFlushPriority {
	IDFlushPriorityHigh,
	IDFlushPriorityNormal
} IDFlushPriority;


/**
 *
 */
typedef enum IDFlushSpeed {
	IDFlushSpeedFast,
	IDFlushSpeedMedium,
	IDFlushSpeedFull
} IDFlushSpeed;



@protocol IDFlushProtocol

/**
 *
 */
-(IDFlushPriority)priority;


/**
 *
 */
-(void)flush:(IDFlushSpeed)speed;

/**
 * Tells the object
 * that its flush method needs 
 * to be called again.
 */
-(void)setNeedsFlush;

@end
