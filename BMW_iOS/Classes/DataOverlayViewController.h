//
//  DataOverlayViewController.h
//  BMW_iOS
//
//  Created by Rob Balian on 3/2/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreMotion/CMMotionManager.h>
#import <CoreLocation/CoreLocation.h>

@interface DataOverlayViewController : UIViewController {
	IBOutlet UILabel *accel, *vaccel, *vgps, *altitude, *latlong, *vaverage;
}

-(void)populateLabelsWithAccel:(CMAcceleration)a Location:(CLLocation *)l GPSVelocity:(float)vg AverageVelocity:(float)vav andAccelerometerVelocity:(float *)va;

@end
