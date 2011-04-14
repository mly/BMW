//
//  StatsTracker.m
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 3/15/11.
//  Copyright 2011. All rights reserved.
//

#import "StatsTracker.h"
#import <CoreLocation/CoreLocation.h>
#import <CoreMotion/CMMotionManager.h>
#include "JSONSerializableSupport.h"

@implementation StatsTracker
@synthesize currentStats, stats;

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
        redStart = nil;
        redCount = 0;
	}
	return self;
}

-(void)signalRed
{
    if(redStart==nil)
    {
        redStart=[[NSDate date] retain];
        redCount++;
    }
}

-(double)getTime
{
    if(redStart!=nil)
    {
        double time = [[NSDate date] timeIntervalSinceDate:redStart];
        NSLog(@"time: %f",time);
        return time;
    }
    return -1;
}

-(int)getLightCount
{
    return redCount;
}

-(void)signalBlack
{
    if(redStart!=nil)
    {
        double time = [self getTime];
        //send to server!
        [redStart release];
        redStart = nil;
        
        NSMutableURLRequest *req = [[[NSMutableURLRequest alloc] init] autorelease];
		NSString *url = [NSString stringWithFormat:@"http://bunkermw.heroku.com/lights/new?seconds=%f&color=red",time];
		
		[req setURL:[NSURL URLWithString:url]];
		[req setHTTPMethod:@"GET"];
		[req setValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
		
		NSError *error;
		NSURLResponse *response;
		NSData *urlData=[NSURLConnection sendSynchronousRequest:req returningResponse:&response error:&error];
    }
}

-(void)queryServer
{
    
}

-(NSString *)getAggregateLightInfo
{
    return cloudLightInfo;
}

-(void)addStats:(NSMutableDictionary *)stat
{
	//do a server push at this point instead of NSLog
	if(currentStats)
	{
		NSMutableDictionary *miniStats = [[[NSMutableDictionary alloc] init] autorelease];
		[miniStats setObject:[NSNumber numberWithDouble:[[currentStats objectForKey:DATE] timeIntervalSince1970]] forKey:DATE];
		CLLocation *l = [currentStats objectForKey:LOCATION];
		[miniStats setObject:[NSNumber numberWithDouble:l.coordinate.latitude] forKey:@"Latitude"];
		[miniStats setObject:[NSNumber numberWithDouble:l.coordinate.longitude] forKey:@"Longitude"];
		[miniStats setObject:[[UIDevice currentDevice] uniqueIdentifier] forKey:UUID];
		
		NSMutableURLRequest *req = [[[NSURLRequest alloc] init] autorelease];
		NSString *post = [miniStats toJSON];
		NSData *postData = [post dataUsingEncoding:NSASCIIStringEncoding allowLossyConversion:NO];
		NSString *postLength = [NSString stringWithFormat:@"%d", [postData length]];
		
		[req setURL:[NSURL URLWithString:@"http://localhost:3000/driving_stat/post"]];
		[req setHTTPMethod:@"POST"];
		[req setValue:postLength forHTTPHeaderField:@"Content-Length"];
		[req setValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
		[req setHTTPBody:postData];
		
		NSError *error;
		NSURLResponse *response;
		NSData *urlData=[NSURLConnection sendSynchronousRequest:req returningResponse:&response error:&error];
		NSString *data=[[NSString alloc]initWithData:urlData encoding:NSUTF8StringEncoding];
		NSLog(data);
		
		//NSURLConnection *conn = [[NSURLConnection alloc] initWithRequest: delegate:self startImmediately:YES];
		NSLog(@"prev stats:%@",[miniStats toJSON]);
	}
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

#pragma mark -
#pragma mark Stats Processing

-(void)processStats
{
	if(currentStats == nil)
		return;
	[self maxSpeed];
	[self altitudeRange];
	[self averageSpeed];
	[self stopTime];
}

-(void)maxSpeed
{
	CLLocation *l = [currentStats objectForKey:LOCATION];
	double prev = 0;
	if(curIndex >= 1)
		prev = [[[stats objectAtIndex:curIndex-1] objectForKey:MAX_SPEED] doubleValue];
	[self addStat:MAX_SPEED withValue:[NSNumber numberWithDouble:l.speed>prev?l.speed:prev]];
}

-(void)altitudeRange
{
	CLLocation *l = [currentStats objectForKey:LOCATION];
	if(curIndex < 1)
	{
		[self addStat:MAX_ALTITUDE withValue:[NSNumber numberWithDouble:l.altitude]];
		[self addStat:MIN_ALTITUDE withValue:[NSNumber numberWithDouble:l.altitude]];
	}
	else
	{
		double max = [[[stats objectAtIndex:curIndex-1] objectForKey:MAX_ALTITUDE] doubleValue];
		double min = [[[stats objectAtIndex:curIndex-1] objectForKey:MIN_ALTITUDE] doubleValue];
		[self addStat:MAX_ALTITUDE withValue:[NSNumber numberWithDouble:l.altitude>max?l.altitude:max]];
		[self addStat:MIN_ALTITUDE withValue:[NSNumber numberWithDouble:l.altitude<min?l.altitude:min]];
	}
}

-(void)averageSpeed
{
	CLLocation *l = [currentStats objectForKey:LOCATION];
	double prev = 0;
	if(curIndex >= 1)
		prev = [[[stats objectAtIndex:curIndex-1] objectForKey:MAX_SPEED] doubleValue];
	double average = (l.speed+prev*([stats count]-1))/[stats count];
	[self addStat:AVERAGE_SPEED withValue:[NSNumber numberWithDouble:average]];
}

-(void)stopTime
{
	if(curIndex < 1)
	{
		[self addStat:CURRENT_STOP_TIME withValue:[NSNumber numberWithDouble:0]];
		[self addStat:LIFETIME_STOP_TIME withValue:[NSNumber numberWithDouble:0]];
		return;
	}
	CLLocation *l = [currentStats objectForKey:LOCATION];
	double lifetime = [[[stats objectAtIndex:curIndex-1] objectForKey:LIFETIME_STOP_TIME] doubleValue];
	if((double)l.speed != 0)
	{
		[self addStat:CURRENT_STOP_TIME withValue:[NSNumber numberWithDouble:0]];
		[self addStat:LIFETIME_STOP_TIME withValue:[NSNumber numberWithDouble:lifetime]];
		return;
	}
	NSDate *prevD = [[stats objectAtIndex:curIndex-1] objectForKey:DATE];
	NSDate *curD = [currentStats objectForKey:DATE];
	double curStopTime = [[[stats objectAtIndex:curIndex-1] objectForKey:CURRENT_STOP_TIME] doubleValue];
	double timeDiff = -[prevD timeIntervalSinceDate:curD];
	[self addStat:CURRENT_STOP_TIME withValue:[NSNumber numberWithDouble:curStopTime+timeDiff]];
	[self addStat:LIFETIME_STOP_TIME withValue:[NSNumber numberWithDouble:lifetime+timeDiff]];
}
@end
