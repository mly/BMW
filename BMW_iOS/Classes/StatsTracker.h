//
//  StatsTracker.h
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 3/15/11.
//  Copyright 2011. All rights reserved.
//

#import <Foundation/Foundation.h>


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
