//
//  BMW_iOSViewController.h
//  BMW_iOS
//
//  Created by Rob Balian on 2/21/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreMotion/CMMotionManager.h>
#import <QuartzCore/QuartzCore.h>
#import "GravityObject.h"
#include "CaptureSessionManager.h"
#import "DataOverlayViewController.h"

@interface BMW_iOSViewController : UIViewController <CLLocationManagerDelegate> {
	CaptureSessionManager *captureManager;
	DataOverlayViewController *dataOverlayVC;
	float v[3];
	NSMutableArray *motionDataArry;
		
	float totalDist, timeZero;
	double lastLocationUpdateTime;
	float Vgps, Vav;
}
-(void)signalStart;
-(void)signalStop;

@end

