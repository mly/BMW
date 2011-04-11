//
//  SimpleWeatherApp.m
//  SimpleWeather
//
//  Created by Paul Doersch on 1/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "RemoteApp.h"
#import "RemoteAppIDs.h"


@implementation RemoteApp
@synthesize mainVC;


- (NSString*)name { return @"SimpleWeather"; }
- (NSString*)vendor { return @"BMW Technology Office Palo Alto"; }
- (NSString*)version { return @"0.1"; }
- (NSString*)passphrase { return @"bmw0"; }



- (void)doInit
{
	self.mainVC = [[[MainVC alloc] initWithIdApplication: self 
												hmiState: HST_Main
											   gotoEvent: EVNT_Goto_Main
											  titleModel: -1] autorelease];
	[self addViewController:mainVC];
}

- (void)dealloc
{
	self.mainVC = nil;
	[super dealloc];
}


- (void)rhmiDidStart
{	
	[super rhmiDidStart];
}

- (void)lastUserMode:(NSArray*)componentPath 
{
	[mainVC show];
}


-(void) doDisconnect
{
	[super doDisconnect];
}

-(void)doShutdown {
	
}

@end
