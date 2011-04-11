//
//  BMW_iOSAppDelegate.h
//  BMW_iOS
//
//  Created by Rob Balian on 2/21/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ObjectiveResource.h"
#import <CoreLocation/CoreLocation.h>
#include "SensorReader.h"
#include "StatsTracker.h"
#import "MapViewController.h"
#import "RemoteAppController.h"

@class ImageProcessingViewController;

extern NSString* BMWConnectedChanged;

@interface BMW_iOSAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    ImageProcessingViewController *viewController;
	SensorReader *reader;
	
	RemoteAppController* bmwAppController;
}

-(CLLocation *)currentLocation;

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet ImageProcessingViewController *viewController;
@property (readonly) StatsTracker *tracker;
@property (nonatomic, retain) RemoteAppController *bmwAppController;




@end

