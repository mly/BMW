//
//  BMW_iOSViewController.m
//  BMW_iOS
//
//  Created by Rob Balian on 2/21/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import "BMW_iOSViewController.h"
#import <CoreMotion/CMMotionManager.h>

@implementation BMW_iOSViewController



/*
// The designated initializer. Override to perform setup that is required before the view is loaded.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}
*/

// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
	CMMotionManager *motionManager = [[CMMotionManager alloc] init];
	motionManager.gyroUpdateInterval = 1.0;
    [motionManager startGyroUpdatesToQueue:[NSOperationQueue currentQueue]
                               withHandler: ^(CMGyroData *gyroData, NSError *error)
	 {
		 CMRotationRate rotate = gyroData.rotationRate;
		 NSLog(@"rotation rate = [%f, %f, %f]", rotate.x, rotate.y, rotate.z);
	 }];
	
	motionManager.accelerometerUpdateInterval = 1.0;
    [motionManager startAccelerometerUpdatesToQueue:[NSOperationQueue currentQueue]
										withHandler: ^(CMAccelerometerData *accelData, NSError *error)
	 {
		 CMAcceleration a = accelData.acceleration;
		 NSLog(@"acceleration rate = [%f, %f, %f]", a.x, a.y, a.z);
	 }];
}


/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
*/


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
