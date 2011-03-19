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
