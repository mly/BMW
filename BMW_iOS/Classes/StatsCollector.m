//
//  StatsCollector.m
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 3/13/11.
//  Copyright 2011. All rights reserved.
//

#import "StatsCollector.h"

#define UPDATE_INTERVAL 1.0f/3.0f;
#define METERS_SEC_MILES_HOUR_CONVERSION 2.2369

@implementation StatsCollector

-(void)init
{
	
}

-(void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation {
	
}

@end
