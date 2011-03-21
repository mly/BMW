//
//  MapViewController.h
//  BMW_iOS
//
//  Created by Rob Balian on 3/21/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>
#import <CoreLocation/CoreLocation.h>
#import "BMW_iOSAppDelegate.h"
#import "AnnotationView.h"
#import "CurrentLocationAnnotation.h"

@interface MapViewController : UIViewController <MKMapViewDelegate> {
	IBOutlet MKMapView *mapView;
	
	
}
- (IBAction)addPin:(id)sender;


@end
