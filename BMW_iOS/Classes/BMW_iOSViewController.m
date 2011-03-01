//
//  BMW_iOSViewController.m
//  BMW_iOS
//
//  Created by Rob Balian on 2/21/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import "BMW_iOSViewController.h"

#define UPDATE_INTERVAL 1.0f/30.0f;
#define CONVERSION 2.23693629f/9.8f

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

-(void)signalStart
{
	[captureManager startWriting];
}

-(void)signalStop
{
	[captureManager finishWriting];
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	captureManager = [[CaptureSessionManager alloc] init];
	
	// Configure capture session
	[captureManager addVideoInput];
	[captureManager addVideoOutput];
	
	// Set up video preview layer
	[captureManager addVideoPreviewLayer];
	CGRect layerRect = self.view.layer.bounds;
	captureManager.previewLayer.bounds = layerRect;
	captureManager.previewLayer.position = CGPointMake(CGRectGetMidX(layerRect), CGRectGetMidY(layerRect));
	[self.view.layer addSublayer:captureManager.previewLayer];
	
	[captureManager.captureSession startRunning];
	
	//Location
	CLLocationManager *locationManager = [[CLLocationManager alloc] init];
	[locationManager startUpdatingLocation];
	
	v[0] = v[1] = v[2] = 0;
	
	//Accelerometer and Gyro
	CMMotionManager *motionManager = [[CMMotionManager alloc] init];
	motionManager.deviceMotionUpdateInterval = UPDATE_INTERVAL;
    [motionManager startDeviceMotionUpdatesToQueue:[NSOperationQueue currentQueue]
									   withHandler: ^(CMDeviceMotion *motionData, NSError *error)
	 {
		 CMAcceleration gravity = motionData.gravity;
		 CMAcceleration userAcceleration = motionData.userAcceleration;
		 CMRotationRate rot = motionData.rotationRate;
		 CMAttitude *att = motionData.attitude;
#if CM_DEBUG
		 NSLog(@"gravity = [%f, %f, %f]", gravity.x, gravity.y, gravity.z);
		 NSLog(@"User Acceleration = [%f, %f, %f]", userAcceleration.x, userAcceleration.y, userAcceleration.z);
		 NSLog(@"Rotation = [%f, %f, %f]", rot.x, rot.y, rot.z);
		 NSLog(@"Attitude = [%f, %f, %f]", att.roll, att.pitch, att.yaw);
		 v[0] += userAcceleration.x*UPDATE_INTERVAL;
		 v[1] += userAcceleration.y*UPDATE_INTERVAL;
		 v[2] += userAcceleration.z*UPDATE_INTERVAL;
		 NSLog(@"Velocity (MPH) = [%f, %f, %f]", v[0]*CONVERSION,v[1]*CONVERSION,v[2]*CONVERSION);
#endif
#if CL_DEBUG
		 NSLog(@"Coordinate: [%f,%f]",locationManager.location.coordinate.longitude,locationManager.location.coordinate.latitude);
		 NSLog(@"Altitude: %f",locationManager.location.altitude);
#endif
	 }];
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
