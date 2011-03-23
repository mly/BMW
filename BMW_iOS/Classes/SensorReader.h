//
//  SensorReader.h
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 3/13/11.
//  Copyright 2011. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>
#import <CoreMotion/CMMotionManager.h>

@interface SensorReader : NSObject <CLLocationManagerDelegate>{
	CLLocationManager *locationManager;
	CMMotionManager *motionManager;
}
-(void)startReading;
-(void)stopReading;
@end
