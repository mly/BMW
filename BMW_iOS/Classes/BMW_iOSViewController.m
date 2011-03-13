//
//  BMW_iOSViewController.m
//  BMW_iOS
//
//  Created by Rob Balian on 2/21/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import "BMW_iOSViewController.h"
#import "ObjectiveResource.h"
#import "VelocityEvent.h"

#define UPDATE_INTERVAL 1.0f/3.0f;
#define CONVERSION 2.23693629f/9.8f
#define METERS_SEC_MILES_HOUR_CONVERSION 2.2369

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

-(void) setProcessedImage:(CGImageRef)image
{
	processedImage = [UIImage imageWithCGImage:image];
	dirty = YES;
}

-(void) refreshDisplay
{
	if(dirty)
	{
		iv.image = processedImage;
		dirty=NO;
	}
	[self performSelector:@selector(refreshDisplay) withObject:nil afterDelay:0.1];
}

-(void)signalStart
{
	//[self getGravDataFile];
#if TARGET_OS_IPHONE &&!TARGET_IPHONE_SIMULATOR
	[captureManager startWriting];
#endif
}

-(void)signalStop
{
	//[self writeToGravDataFile];
#if TARGET_OS_IPHONE &&!TARGET_IPHONE_SIMULATOR
	[captureManager finishWriting];
#endif
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	
	totalDist = 0.0;
	lastLocationUpdateTime = timeZero = CACurrentMediaTime();
#if TARGET_OS_IPHONE &&!TARGET_IPHONE_SIMULATOR
	captureManager = [[CaptureSessionManager alloc] init];
	captureManager.delegate = self;
#if RENDER_PROCESSING
	dirty = NO;
	[self performSelector:@selector(refreshDisplay) withObject:nil afterDelay:0.1];
#endif
	
	
	// Configure capture session
	[captureManager addVideoInput];
	[captureManager addVideoOutput];
	
	// Set up video preview layer
	[captureManager addVideoPreviewLayer];
	CGRect layerRect = self.view.layer.bounds;
	captureManager.previewLayer.bounds = layerRect;
	captureManager.previewLayer.position = CGPointMake(CGRectGetMidX(layerRect), CGRectGetMidY(layerRect));
#if !RENDER_PROCESSING
	[self.view.layer addSublayer:captureManager.previewLayer];
#endif
#endif
	
	dataOverlayVC = [[DataOverlayViewController alloc] init];
	[dataOverlayVC.view setFrame:CGRectMake(-230, 200, 500, 100)];
	dataOverlayVC.view.transform = CGAffineTransformMakeRotation(M_PI/2);
	
	[self.view addSubview:dataOverlayVC.view];
	
#if TARGET_OS_IPHONE &&!TARGET_IPHONE_SIMULATOR
	[captureManager.captureSession startRunning];
#endif
	
	
	
	//Location
	//[self getGravDataFile];
	
	if (motionDataArry) {
		[motionDataArry release];
	}
	motionDataArry = [[NSMutableArray alloc] init];
	
	CLLocationManager *locationManager = [[CLLocationManager alloc] init];
	locationManager.delegate = self;
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
		 
		 //NSData *data = [[NSData alloc] initWithBytes:<#(const void *)bytes#> length:<#(NSUInteger)length#>
		 //[gravData addObject:[[GravityObject alloc] initWithX:gravity.x Y:gravity.y andZ:gravity.z]];
		 //NSData *motionData = [NSData dataWithBytes: length:sizeof(CMAcceleration)];
		 [motionDataArry addObject:motionData];
		 [dataOverlayVC populateLabelsWithAccel:userAcceleration Location:locationManager.location GPSVelocity:Vgps AverageVelocity:Vav andAccelerometerVelocity:&v ];
		 
		 
		 //-(id)initWithX:(float)x Y:(float)y andZ:(float)z;
		 
		 v[0] += userAcceleration.x*UPDATE_INTERVAL;
		 v[1] += userAcceleration.y*UPDATE_INTERVAL;
		 v[2] += userAcceleration.z*UPDATE_INTERVAL;
		 
#if CM_DEBUG
		 NSLog(@"gravity = [%f, %f, %f]", gravity.x, gravity.y, gravity.z);
		 NSLog(@"User Acceleration = [%f, %f, %f]", userAcceleration.x, userAcceleration.y, userAcceleration.z);
		 NSLog(@"Rotation = [%f, %f, %f]", rot.x, rot.y, rot.z);
		 NSLog(@"Attitude = [%f, %f, %f]", att.roll, att.pitch, att.yaw);
		 NSLog(@"Velocity (MPH) = [%f, %f, %f]", v[0]*CONVERSION,v[1]*CONVERSION,v[2]*CONVERSION);
#endif
#if CL_DEBUG
		 NSLog(@"Coordinate: [%f,%f]",locationManager.location.coordinate.longitude,locationManager.location.coordinate.latitude);
		 NSLog(@"Altitude: %f",locationManager.location.altitude);
#endif
	}];
}

-(void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation {
	double updateSeconds = CACurrentMediaTime() - lastLocationUpdateTime;
	lastLocationUpdateTime = CACurrentMediaTime();
	double distance = [newLocation distanceFromLocation:oldLocation];
	totalDist += distance;
	Vgps = (distance/updateSeconds)*METERS_SEC_MILES_HOUR_CONVERSION;
	Vav = (totalDist / (CACurrentMediaTime() - timeZero))*METERS_SEC_MILES_HOUR_CONVERSION;
	NSLog(@"Current gps speed: %f mph", Vgps);
	NSLog(@"Current average speed: %f mph", Vav);
	
	//Send velocity event object to server...not very interesting at the moment, but makes the JSON super easy
	VelocityEvent *ve = [[[VelocityEvent alloc]init]autorelease];
	ve.latitude = newLocation.coordinate.latitude;
	ve.longitude = newLocation.coordinate.longitude;
	ve.velocity = Vgps;
	[ve saveRemote];
	
}

-(void)writeToGravDataFile {
	
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	
	// the path to write file
	NSString *appFile = [documentsDirectory stringByAppendingPathComponent:@"test1"];
	
	double CurrentTime = CACurrentMediaTime();
	NSLog(@"Serializing and writing gravData with %d entries", [motionDataArry count]);

	[NSKeyedArchiver archiveRootObject:motionDataArry toFile:appFile];
	NSLog(@"Current Time: %f", CurrentTime);
	NSLog(@"Time to write: %f", (double)CACurrentMediaTime() - (double)CurrentTime);
}

-(void)getGravDataFile {
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	
	// the path to write file
	NSString *appFile = [documentsDirectory stringByAppendingPathComponent:@"test1"];
	
	NSData *retrievedData = [[NSData alloc] initWithContentsOfFile:appFile];
	if (retrievedData) {
		NSArray *gd = [NSKeyedUnarchiver unarchiveObjectWithData:retrievedData];
		NSLog(@"Retrieved gravData with %d entries", [gd count]);
		for (CMDeviceMotion *motion in gd) {
			CMAcceleration grav = motion.gravity;
			NSLog(@"gravity = [%f, %f, %f]", grav.x, grav.y, grav.z);	
		}
	} else NSLog(@"could not retrieve data");
}


// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


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
