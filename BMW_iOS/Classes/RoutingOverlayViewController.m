//
//  RoutingOverlayViewController.m
//  BMW_iOS
//
//  Created by Rob Balian on 3/16/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import "RoutingOverlayViewController.h"


@implementation Route
-(id)initWithStartLocation:(CLLocation *)loc {
	if (self) {
		NSDate *date = [NSDate date];
		NSDateFormatter *df = [[NSDateFormatter alloc] init];
		NSLog(@"%@", [df stringFromDate:date]);
		waypoints = [[NSMutableArray alloc] init];
		[self addWaypoint:loc];
	}
	return self;
}

-(void)addWaypoint:(CLLocation *)loc {
	[waypoints addObject:loc];
	NSLog(@"Added Waypoint, currently %d in route", [waypoints count]);
}

@end

@implementation RoutingOverlayViewController

-(id)init {
	if (self) {
		
	}
	return self;
}

-(void)startNewRoute {
	currentRoute = [[Route alloc] initWithStartLocation:currentLocation];
}

-(void)endCurrentRoute {
	[currentRoute addWaypoint:currentLocation];
	//save
	[currentRoute release];
	currentRoute = nil;
}

-(void)locationDidUpdate:(CLLocation *)newLoc {
	double timeDiff = [newLoc.timestamp timeIntervalSince1970] - [currentLocation.timestamp timeIntervalSince1970];
	NSLog(@"Received new location. Time diff: %f", timeDiff);
	
	double timeSinceUpdate = [newLoc.timestamp timeIntervalSince1970] - [lastUpdated timeIntervalSince1970];
	if (timeSinceUpdate > 5.0 && currentRoute != nil) {
		
		[currentRoute addWaypoint:newLoc];
		lastUpdated = newLoc.timestamp;
		[lastUpdated retain];
	}
	
	currentLocation = newLoc;
	[currentLocation retain];
}


// The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
/*
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization.
    }
    return self;
}
*/

-(IBAction)routeButtonPressed:(id)sender {
	if ([routeButton.titleLabel.text isEqual:@"Start New"]) {
		[routeButton setTitle:@"End Route" forState:UIControlStateNormal];
		[self startNewRoute];
	} else if ([routeButton.titleLabel.text isEqual:@"End Route"]) {
		[routeButton setTitle:@"Start New" forState:UIControlStateNormal];
	}
}


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
	[routeButton setTitle:@"Start New" forState:UIControlStateNormal];
    [super viewDidLoad];
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
