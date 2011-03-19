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

@property(readonly) NSDictionary *currentStats;

@end
