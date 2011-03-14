//
//  StatsCollector.h
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 3/13/11.
//  Copyright 2011. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>
#import <CoreMotion/CMMotionManager.h>
#import "GravityObject.h"
#import "DataOverlayViewController.h"

@interface StatsCollector : NSObject <CLLocationManagerDelegate>{
	float v[3];
	NSMutableArray *motionDataArry;
	
	float totalDist, timeZero;
	double lastLocationUpdateTime;
	float Vgps, Vav;
}

@end
