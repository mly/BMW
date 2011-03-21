//
//  MapViewController.m
//  BMW_iOS
//
//  Created by Rob Balian on 3/21/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import "MapViewController.h"


@implementation MapViewController

// The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization.
    }
    return self;
}



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
	//mapView.showsUserLocation = YES;
	mapView.delegate = self;
	
	MKPolygon *dummyOverlay = [MKPolygon polygonWithPoints:nil count:0];
	[mapView addOverlay:dummyOverlay];
	
	    
	[super viewDidLoad];
}

- (IBAction)addPin:(id)sender {
	BMW_iOSAppDelegate *del = [[UIApplication sharedApplication] delegate];
	CLLocation *loc = [del currentLocation];
    //MKPlacemark *placemark = [[MKPlacemark alloc] initWithCoordinate:loc.coordinate addressDictionary:nil];
	//MKAnnotation *ano = [[MKAnnotation alloc] initWithCoordinate:loc.coordinate];
	//MKPinAnnotationView *ano = [[MKPinAnnotationView alloc] initWithAnnotation:placemark reuseIdentifier:@"pin"];
	//ano.draggable = YES;
	
	
	
	CurrentLocationAnnotation *annotation = [[[CurrentLocationAnnotation alloc] initWithCoordinate:loc.coordinate addressDictionary:nil] autorelease];
	annotation.title = @"Drag Me!";
	annotation.subtitle = @"Drag pin to get desired location..";
	// = [mapView.annotations count];
	
	[mapView addAnnotation:annotation];
	

	
	//CurrentLocationAnnotation *annotation = [[[CurrentLocationAnnotation alloc] initWithCoordinate:self.currentLocation.coordinate addressDictionary:nil] autorelease];
	//placemark.title = [[NSString alloc] initWithFormat:@"%d", [mvMapView.annotations count] + 1];
	//placemark.subtitle = @"Drag pin to set poisition.";
    
    //[mapView addAnnotation:ano];
    //[annotation release];
}

-(void)connectPoints {
	for (MKOverlayView *o in mapView.overlays) {
		//if ([o isKindOfClass:[MKPolyline class]]) {
		[mapView removeOverlay:o];
		//o=nil;
		//}
	}
	
	NSInteger arrayCount = [mapView.annotations count];
	CLLocationCoordinate2D coords[arrayCount];
    NSInteger i;
    for (i=0;i<arrayCount;i++) {
        MKPlacemark *placeMark = [mapView.annotations objectAtIndex:i];
        coords[i] = placeMark.coordinate;
        NSLog(@"%f, %f", coords[i].latitude, coords[i].longitude);
    }
	
	MKPolyline *polyLine = [MKPolyline polylineWithCoordinates:coords count:[mapView.annotations count]];
	[mapView addOverlay:polyLine];
	//[polyLine release];	
}


#pragma mark -
#pragma mark MapView
- (MKAnnotationView *)mapView:(MKMapView *)MapView viewForAnnotation:(id <MKAnnotation>)annotation
{
	static NSString * const kPinAnnotationIdentifier = @"PinIdentifier";
	MKAnnotationView *draggablePinView = [MapView dequeueReusableAnnotationViewWithIdentifier:kPinAnnotationIdentifier];
	
	if (draggablePinView) {
		draggablePinView.annotation = annotation;
	} else {		
		draggablePinView = [[[AnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:kPinAnnotationIdentifier] autorelease];
		if ([draggablePinView isKindOfClass:[AnnotationView class]]) {
			((AnnotationView *)draggablePinView).mapView = MapView;
		}
	}			
	return draggablePinView;
}

- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)annotationView didChangeDragState:(MKAnnotationViewDragState)newState fromOldState:(MKAnnotationViewDragState)oldState 
{
	if (oldState == MKAnnotationViewDragStateDragging) {
		CurrentLocationAnnotation *annotation = (CurrentLocationAnnotation *)annotationView.annotation;
		annotation.subtitle = [NSString stringWithFormat:@"%f %f", annotation.coordinate.latitude, annotation.coordinate.longitude];		
		[self connectPoints];
	}
}

- (MKOverlayView *) mapView: (MKMapView *) mapView viewForOverlay: (id <MKOverlay>) overlay
{
	if ([overlay isKindOfClass: [MKPolyline class]])
	{
		MKPolylineView *polyLineView = [[[MKPolylineView alloc] initWithOverlay:overlay] autorelease];
		polyLineView.strokeColor = [UIColor redColor];
		polyLineView.lineWidth = 5.0;
		return polyLineView;
	}
	else if ([overlay isKindOfClass: [MKPolygon class]])
	{
		// This is for a dummy overlay to work around a problem with overlays
		// not getting removed by the map view even though we asked for it to
		// be removed.
		MKOverlayView * dummyView = [[[MKOverlayView alloc] initWithOverlay: overlay] autorelease];
		dummyView.alpha = 0.0;
		return dummyView;
	}
	else
	{
		return nil;
	}
}

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations.
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}


@end
