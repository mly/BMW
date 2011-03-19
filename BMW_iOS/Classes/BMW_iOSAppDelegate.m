//
//  BMW_iOSAppDelegate.m
//  BMW_iOS
//
//  Created by Rob Balian on 2/21/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import "BMW_iOSAppDelegate.h"
#import "BMW_iOSViewController.h"
#import "ImageProcessingViewController.h"


@implementation BMW_iOSAppDelegate

@synthesize window;
@synthesize viewController;


#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
    // Override point for customization after application launch.
	[UIApplication sharedApplication].statusBarHidden = YES;
	[UIApplication sharedApplication].idleTimerDisabled = YES;
    // Add the view controller's view to the window and display.
	ImageProcessingViewController *ctvc = [[ImageProcessingViewController alloc] init];
	[self.window addSubview:ctvc.view];
    //[self.window addSubview:viewController.view];
    [self.window makeKeyAndVisible];
	
	[ObjectiveResourceConfig setSite:@"http://localhost:3000/"];
	
	[[[SensorReader alloc] init] startReading];

    return YES;
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
	[viewController signalStop];
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
	//[viewController signalStop];
	//[viewController signalStart];
}


- (void)dealloc {
    [viewController release];
    [window release];
    [super dealloc];
}


@end
