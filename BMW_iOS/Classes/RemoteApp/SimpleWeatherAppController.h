//
//  SimpleWeatherAppController.h
//  SimpleWeather
//
//  Created by Paul Doersch on 1/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <iDrive/iDrive.h>
#import "SimpleWeatherApp.h"

@interface SimpleWeatherAppController : NSObject <IDApplicationDelegate> {
	ExternalAccessoryMonitor*	usbAccessoryMonitor;
	SimpleWeatherApp*				app;
}
@property (retain) SimpleWeatherApp* app;
@property (retain) ExternalAccessoryMonitor* usbAccessoryMonitor;

- (void)accessoryDidStart:(NSNotification*) notification; // call this with nil to fake a connection
- (void)accessoryDidStop:(NSNotification*) notification;
- (void)connectToUSB;
- (void)disconnectFromUSB;
- (void)willEnterForeground:(NSNotification*) notification;
- (void)didEnterBackground:(NSNotification*) notification;

@end
