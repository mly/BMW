//
//  SimpleWeatherAppDelegate.h
//  SimpleWeather
//
//  Created by Paul Doersch on 1/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SimpleWeatherAppController.h"

@class SimpleWeatherViewController;

extern NSString* BMWConnectedChanged;

@interface SimpleWeatherAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    SimpleWeatherViewController *viewController;
	SimpleWeatherAppController* bmwAppController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet SimpleWeatherViewController *viewController;
@property (nonatomic, retain) SimpleWeatherAppController *bmwAppController;

@end

