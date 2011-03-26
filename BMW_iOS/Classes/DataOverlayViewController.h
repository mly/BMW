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
#import "StatsTracker.h"

@interface DataOverlayViewController : UIViewController {
	IBOutlet UITextView *textView;
}

-(void)populateLabelsFromsStatsTracker;
@end
