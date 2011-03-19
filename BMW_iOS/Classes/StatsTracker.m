//
//  StatsTracker.m
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 3/15/11.
//  Copyright 2011. All rights reserved.
//

#import "StatsTracker.h"


@implementation StatsTracker
@synthesize currentStats;

//for simplicity's sake - eventually we probably just want to pass this, not do it as a singleton
static StatsTracker *sharedTracker;
+(StatsTracker *)sharedTracker
{
	if(!sharedTracker)
		sharedTracker = [[StatsTracker alloc] init];
	return sharedTracker;
}

-(id)init
{
	if(self=[super init])
	{
		stats = [[NSMutableArray alloc] init];
		curIndex = -1;
	}
	return self;
}

-(void)addStats:(NSMutableDictionary *)stat
{
	[currentStats release];
	currentStats = stat;
	[currentStats retain];
	[stats addObject:currentStats];
	NSLog(@"%@",currentStats);
	curIndex++;
}

-(void)addStat:(id)stat withValue:(id)value
{
	[currentStats setObject:value forKey:stat];
}

-(void)dealloc
{
	[stats release];
	[currentStats release];
	
	[super dealloc];
}
@end
