//
//  SimpleWeatherViewController.m
//  SimpleWeather
//
//  Created by Paul Doersch on 1/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "SimpleWeatherViewController.h"
#import "SimpleWeatherAppDelegate.h"

@implementation SimpleWeatherViewController




-(void)bmwConenctionChanged:(NSNotification *)notification
{
	BOOL connected = [[[notification userInfo] objectForKey:@"connected"] boolValue];	
	[connectionStatusLabel setText: connected ? @"connected" : @"not connected"];
}


/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
	[[NSNotificationCenter defaultCenter] addObserver:self 
											 selector:@selector(bmwConenctionChanged:) 
												 name:BMWConnectedChanged 
											   object:nil];
    [super viewDidLoad];
	[connectionStatusLabel setText: @"not connected"];
}



/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

@end
