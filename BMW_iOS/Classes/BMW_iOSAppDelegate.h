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

@class BMW_iOSViewController;

@interface BMW_iOSAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    BMW_iOSViewController *viewController;
}

-(CLLocation *)currentLocation;

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet BMW_iOSViewController *viewController;



@end

