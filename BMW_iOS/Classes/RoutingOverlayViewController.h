//
//  RoutingOverlayViewController.h
//  BMW_iOS
//
//  Created by Rob Balian on 3/16/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>


@interface Route : NSObject {
	NSMutableArray *waypoints;
	NSTimeInterval *startTime;
}
@end

@interface RoutingOverlayViewController : UIViewController {
	IBOutlet UIButton *routeButton;
	IBOutlet UILabel *tlLabel, *blLabel, *trLabel, *brLabel;
	Route *currentRoute;
	CLLocation *currentLocation;
	NSDate *lastUpdated;
}

-(IBAction)routeButtonPressed:(id)sender;

@end
