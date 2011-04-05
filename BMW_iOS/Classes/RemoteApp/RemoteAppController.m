//
//  SimpleWeatherAppController.m
//  SimpleWeather
//
//  Created by Paul Doersch on 1/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "RemoteAppController.h"
#import "BMW_iOSAppDelegate.h"

@implementation RemoteAppController
@synthesize app;
@synthesize usbAccessoryMonitor;


-(id)init {
	if (self = [super init]) {
		//make sure we are notified of the USB connection status changes
		[[NSNotificationCenter defaultCenter] addObserver:self
												 selector:@selector(accessoryDidStart:)
													 name:ExternalAccessoryProxyDidStartNotification
												   object:nil];
		
		[[NSNotificationCenter defaultCenter] addObserver:self
												 selector:@selector(accessoryDidStop:)
													 name:ExternalAccessoryProxyWillStopNotification
												   object:nil];
		
		[[NSNotificationCenter defaultCenter] addObserver:self
												 selector:@selector(willEnterForeground:)
													 name:UIApplicationDidFinishLaunchingNotification
												   object:nil];
		
		[[NSNotificationCenter defaultCenter] addObserver:self
												 selector:@selector(willEnterForeground:)
													 name:UIApplicationWillEnterForegroundNotification
												   object:nil];
		
		[[NSNotificationCenter defaultCenter] addObserver:self
												 selector:@selector(didEnterBackground:)
													 name:UIApplicationDidEnterBackgroundNotification
												   object:nil];
		
		
		//Startup the USB connection monitor
		usbAccessoryMonitor = [[ExternalAccessoryMonitor alloc] initWithProxyPort:[IDConnection defaultPort]];
		
		// Call Start
		[usbAccessoryMonitor start];
	}
	return self;
}

-(void)dealloc {
	self.app = nil;
	self.usbAccessoryMonitor = nil;
	[super dealloc];
}


-(void)willEnterForeground:(NSNotification*) notification {
	[usbAccessoryMonitor start];
}

-(void)didEnterBackground:(NSNotification*) notification {
	[usbAccessoryMonitor stop];
}

/**
 * Callbacks from the NSNotificationCenter because we signed up for hearing from our
 * ExternalAccessoryMonitor* usbAccessoryMonitor
 */
-(void) accessoryDidStart:(NSNotification*) notification
{
	// Connect
	[self connectToUSB];
}

-(void) accessoryDidStop:(NSNotification*) notification
{
	// Disconnect
	[self disconnectFromUSB];
}


- (void)connectToUSB 
{	
	// Start Rhmi App
	self.app = [[[SimpleWeatherApp alloc] initWithHmiDescription:@"SimpleWeatherApp.xml" 
											 imageDatabaseAll:@"SimpleWeatherApp_ALL_Images.zip"
											 imageDatabaseBMW:nil
											imageDatabaseMINI:nil
											  textDatabaseAll:nil 
											  textDatabaseBMW:nil 
											 textDatabaseMINI:nil 
											  devCertificates:YES
													 delegate:self] autorelease];
	[app connectWithHostname: @"127.0.0.1"];
	// Waiting for	-idApplicationDidConnect: ...
	// or			-idApplication: connectionFailedWithError: ...
}	 

- (void)disconnectFromUSB 
{
	[app disconnect];
	// Waiting for	-idApplicationDidDisconnect: ...
	// or			-idApplication: connectionFailedWithError: ...
}



-(void)idApplicationDidConnect:(IDApplication*)appication
{
	[[NSNotificationCenter defaultCenter] postNotificationName:BMWConnectedChanged object:nil userInfo:[NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES] forKey:@"connected"]];
	NSLog(@"Connected");
}

-(void)idApplicationDidDisconnect:(IDApplication*)appication
{
	self.app = nil;
	[[NSNotificationCenter defaultCenter] postNotificationName:BMWConnectedChanged object:[NSNumber numberWithBool:NO]];
}

-(void)idApplication:(IDApplication*)appication connectionFailedWithError:(NSError*)error
{
	self.app = nil;
	[[NSNotificationCenter defaultCenter] postNotificationName:BMWConnectedChanged object:[NSNumber numberWithBool:NO]];
}


@end
