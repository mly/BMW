//
//  StatsTracker.h
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 3/15/11.
//  Copyright 2011. All rights reserved.
//

#import <Foundation/Foundation.h>
#define DEVICE_MOTION @"Device Motion"
#define LOCATION @"Location"
#define HEADING @"Heading"
#define DATE @"Date"
#define MAX_SPEED @"Max Speed"
#define AVERAGE_SPEED @"Average Speed"
#define MAX_ALTITUDE @"Max Altitude"
#define MIN_ALTITUDE @"Min Altitude"
#define CURRENT_STOP_TIME @"Current Stop Time"
#define LIFETIME_STOP_TIME @"Lifetime Stop Time"

@interface StatsTracker : NSObject {
	NSMutableArray *stats;
	NSMutableDictionary *currentStats;
	int curIndex;
}
-(void)addStats:(NSMutableDictionary *)stat;
-(void)addStat:(id)stat withValue:(id)value;
+(StatsTracker *)sharedTracker;//for simplicity's sake - eventually we probably just want to pass this, not do it as a singleton

@property(readonly) NSDictionary *currentStats;

@end
