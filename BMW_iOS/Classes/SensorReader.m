//
//  SensorReader.m
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 3/13/11.
//  Copyright 2011. All rights reserved.
//

#import "SensorReader.h"
#include "StatsTracker.h"

#define UPDATE_INTERVAL 5.0f/1.0f;
#define METERS_SEC_MILES_HOUR_CONVERSION 2.2369

@implementation SensorReader

-(id)init
{
	if (self) {
		locationManager = [[CLLocationManager alloc] init];
		locationManager.delegate = self;
		
		motionManager = [[CMMotionManager alloc] init];
		motionManager.deviceMotionUpdateInterval = UPDATE_INTERVAL;
	}
	return self;
	
}

-(void)startReading
{
	[locationManager startUpdatingHeading];
	[locationManager startUpdatingLocation];
	
	//Accelerometer and Gyro
	[motionManager startDeviceMotionUpdatesToQueue:[NSOperationQueue currentQueue]
									   withHandler: ^(CMDeviceMotion *motionData,	NSError *error)
	{
		if(locationManager.heading!=nil&&locationManager.location!=nil)
		{
			NSMutableDictionary *stats = [[NSMutableDictionary alloc] init];
			[stats setObject:motionData forKey:DEVICE_MOTION];
			[stats setObject:locationManager.location forKey:LOCATION];
			[stats setObject:locationManager.heading forKey:HEADING];
			[stats setObject:[NSDate date] forKey:DATE];
			//[[StatsTracker sharedTracker] addStats:stats];
			[[StatsTracker sharedTracker] processStats];
			[stats release];
		}
	}];
}

-(void)stopReading
{
	[motionManager stopDeviceMotionUpdates];
	[locationManager stopUpdatingLocation];
	[locationManager stopUpdatingHeading];
}

-(void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation {
	NSLog(@"%@",newLocation);
}

- (void)dealloc {
	[locationManager release];
	[motionManager release];
	
    [super dealloc];
}
@end
